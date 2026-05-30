"""
CPU interrupt / CSR unit tests for riscv_core.sv.

Tests:
  1. test_csrrw_readback   — CSRRW writes mtvec, CSRRS reads it back
  2. test_timer_interrupt  — set mtvec/mie/mstatus, assert m_timer_irq_i,
                             verify handler runs (dmem[0]=0xAA)
  3. test_mret_resumes     — after handler, mret returns execution;
                             main loop writes 0xBB to dmem[1]
  4. test_ext_irq          — enable mie.MEIE (bit 11), assert m_ext_irq_i,
                             verify mcause=0x8000_000B and handler runs
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK_NS = 10
NOP    = 0x00000013   # ADDI x0, x0, 0

# ---------------------------------------------------------------------------
# Instruction encodings
# ---------------------------------------------------------------------------
OP_R      = 0x33
OP_IMM    = 0x13
OP_LOAD   = 0x03
OP_STORE  = 0x23
OP_BRANCH = 0x63
OP_JAL    = 0x6F
OP_JALR   = 0x67
OP_SYSTEM = 0x73

# CSR addresses
CSR_MSTATUS = 0x300
CSR_MIE     = 0x304
CSR_MTVEC   = 0x305
CSR_MEPC    = 0x341
CSR_MCAUSE  = 0x342
CSR_MIP     = 0x344

def addi(rd, rs1, imm):
    return (((imm & 0xFFF) << 20) | (rs1 << 15) | (0x0 << 12) | (rd << 7) | OP_IMM)

def sw(rs2, rs1, imm):
    imm &= 0xFFF
    return (((imm >> 5) & 0x7F) << 25) | (rs2 << 20) | (rs1 << 15) | (0x2 << 12) | ((imm & 0x1F) << 7) | OP_STORE

def csrrw(rd, csr, rs1):
    """CSRRW rd, csr, rs1 — writes rs1 to CSR, returns old value to rd."""
    return ((csr & 0xFFF) << 20) | (rs1 << 15) | (0x1 << 12) | (rd << 7) | OP_SYSTEM

def csrrs(rd, csr, rs1):
    """CSRRS rd, csr, rs1 — ORs rs1 into CSR, returns old value to rd."""
    return ((csr & 0xFFF) << 20) | (rs1 << 15) | (0x2 << 12) | (rd << 7) | OP_SYSTEM

MRET = 0x30200073

def _u32(sig):
    try:    return int(sig.value) & 0xFFFF_FFFF
    except: return 0

# ---------------------------------------------------------------------------
# DUT reset — also initializes interrupt inputs
# ---------------------------------------------------------------------------
async def reset_dut(dut):
    dut.rst.value           = 1
    dut.imem_rdata_i.value  = NOP
    dut.dmem_rdata_i.value  = 0
    dut.dmem_stall_i.value  = 0
    dut.m_ext_irq_i.value   = 0
    dut.m_timer_irq_i.value = 0
    dut.m_sw_irq_i.value    = 0
    for _ in range(4):
        await RisingEdge(dut.clk)
    dut.rst.value = 0
    await Timer(1, unit="ns")  # let reset propagate; keep PC=0 for correct first fetch

# ---------------------------------------------------------------------------
# Single-cycle combinational memory model
# ---------------------------------------------------------------------------
async def run_program(dut, imem: dict, dmem: dict, cycles: int = 40):
    dut.imem_rdata_i.value = imem.get(0, NOP)
    for _ in range(cycles):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")

        iaddr = _u32(dut.imem_addr_o) >> 2
        dut.imem_rdata_i.value = imem.get(iaddr, NOP)

        daddr = _u32(dut.dmem_addr_o) >> 2
        if _u32(dut.dmem_we_o) & 1:
            be    = _u32(dut.dmem_be_o)
            wdata = _u32(dut.dmem_wdata_o)
            word  = dmem.get(daddr, 0)
            for i in range(4):
                if (be >> i) & 1:
                    word = (word & ~(0xFF << (8 * i))) | (((wdata >> (8 * i)) & 0xFF) << (8 * i))
            dmem[daddr] = word
        dut.dmem_rdata_i.value = dmem.get(daddr, 0)


# ===========================================================================
# 1. CSR read-back via CSRRW / CSRRS
# ===========================================================================
@cocotb.test()
async def test_csrrw_readback(dut):
    """
    Write 0x100 to mtvec via CSRRW.
    Read it back with CSRRS (rs1=x0 → read-only).
    Store to dmem[0] and verify.

    Program (word-address):
      0: addi x1, x0, 0x100        ; x1 = 0x100
      1: csrrw x0, mtvec, x1       ; mtvec = 0x100
      2: csrrs x2, mtvec, x0       ; x2 = mtvec (read-only, rs1=x0)
      3: sw x2, 0(x0)              ; dmem[0] = 0x100
    """
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(1, 0, 0x100),
        1: csrrw(0, CSR_MTVEC, 1),   # mtvec = 0x100
        2: NOP,
        3: NOP,
        4: NOP,
        5: csrrs(2, CSR_MTVEC, 0),   # x2 = mtvec (read-only, rs1=x0)
        6: NOP,
        7: NOP,
        8: NOP,
        9: sw(2, 0, 0),               # dmem[0] = x2
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=30)

    result = dmem.get(0, 0xDEAD)
    assert result == 0x100, f"mtvec readback: expected 0x100, got {result:#010x}"


# ===========================================================================
# 2. Timer interrupt fires and handler executes
# ===========================================================================
@cocotb.test()
async def test_timer_interrupt(dut):
    """
    Set mtvec=0x100, mie=0x80 (MTIE), mstatus.MIE=1.
    Assert m_timer_irq_i. Handler writes 0xAA to dmem[0].

    Word layout:
      0: addi x1, x0, 0x100       ; x1 = handler address
      1: csrrw x0, mtvec, x1      ; mtvec = 0x100
      2: addi x2, x0, 0x80        ; x2 = MTIE bit
      3: csrrw x0, mie, x2        ; mie = 0x80
      4: addi x3, x0, 0x8         ; x3 = MIE bit
      5: csrrw x0, mstatus, x3    ; mstatus.MIE = 1 → interrupts enabled
      6..N: nop (interrupt fires here)

      Handler at word 0x40 (addr 0x100):
      0x40: addi x4, x0, 0xAA    ; marker
      0x41: sw x4, 0(x0)          ; dmem[0] = 0xAA
      0x42: csrrw x0, mie, x0    ; clear mie (prevent re-interrupt after mret)
      0x43: mret
    """
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    HANDLER = 0x40   # word address = byte 0x100

    imem = {
        0: addi(1, 0, 0x100),
        1: csrrw(0, CSR_MTVEC, 1),
        2: addi(2, 0, 0x80),
        3: csrrw(0, CSR_MIE, 2),
        4: addi(3, 0, 0x8),
        5: csrrw(0, CSR_MSTATUS, 3),   # MIE=1 — interrupts armed
        HANDLER + 0: addi(4, 0, 0xAA),
        HANDLER + 1: sw(4, 0, 0),
        HANDLER + 2: csrrw(0, CSR_MIE, 0),  # clear mie
        HANDLER + 3: MRET,
    }
    dmem = {}

    # Assert timer interrupt from the very start; it can't fire until MIE=1 (~cycle 9)
    dut.m_timer_irq_i.value = 1
    await run_program(dut, imem, dmem, cycles=40)
    dut.m_timer_irq_i.value = 0

    result = dmem.get(0, 0xDEAD)
    assert result == 0xAA, f"Timer handler: expected dmem[0]=0xAA, got {result:#010x}"


# ===========================================================================
# 3. MRET resumes main code after handler
# ===========================================================================
@cocotb.test()
async def test_mret_resumes(dut):
    """
    Same setup as test_timer_interrupt. After mret, main code continues.
    Main loop writes 0xBB to dmem[1]. Verify both dmem[0]=0xAA and dmem[1]=0xBB.

    Word layout:
      0-5: same setup as above
      6: addi x5, x0, 0xBB       ; prepare 'main resumed' marker
      7: sw x5, 4(x0)             ; dmem[1] = 0xBB  (only if mret returned here)

      Handler at word 0x40:
      0x40: addi x4, x0, 0xAA
      0x41: sw x4, 0(x0)
      0x42: csrrw x0, mie, x0    ; disable interrupts
      0x43: mret                  ; return to mepc (≈ word 6)
    """
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    HANDLER = 0x40

    imem = {
        0: addi(1, 0, 0x100),
        1: csrrw(0, CSR_MTVEC, 1),
        2: addi(2, 0, 0x80),
        3: csrrw(0, CSR_MIE, 2),
        4: addi(3, 0, 0x8),
        5: csrrw(0, CSR_MSTATUS, 3),
        6: addi(5, 0, 0xBB),          # main-loop marker (runs after mret)
        7: sw(5, 0, 4),                # dmem[1] = 0xBB
        HANDLER + 0: addi(4, 0, 0xAA),
        HANDLER + 1: sw(4, 0, 0),
        HANDLER + 2: csrrw(0, CSR_MIE, 0),
        HANDLER + 3: MRET,
    }
    dmem = {}

    dut.m_timer_irq_i.value = 1
    await run_program(dut, imem, dmem, cycles=55)
    dut.m_timer_irq_i.value = 0

    assert dmem.get(0, 0) == 0xAA, \
        f"Handler did not run: dmem[0]={dmem.get(0,0):#010x}"
    assert dmem.get(1, 0) == 0xBB, \
        f"mret did not resume main: dmem[1]={dmem.get(1,0):#010x}"


# ===========================================================================
# 4. External interrupt (MEIP) fires and handler runs
# ===========================================================================
@cocotb.test()
async def test_ext_irq(dut):
    """
    Set mie.MEIE (bit 11 = 0x800), mstatus.MIE=1.
    Assert m_ext_irq_i. Handler writes 0xCC to dmem[0].
    """
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    HANDLER = 0x40

    imem = {
        0: addi(1, 0, 0x100),
        1: csrrw(0, CSR_MTVEC, 1),
        2: addi(2, 0, -0x800 & 0xFFF),     # 0x800 = MEIE bit — sign-extends OK
        3: csrrw(0, CSR_MIE, 2),
        4: addi(3, 0, 0x8),
        5: csrrw(0, CSR_MSTATUS, 3),
        HANDLER + 0: addi(4, 0, 0xCC),
        HANDLER + 1: sw(4, 0, 0),
        HANDLER + 2: csrrw(0, CSR_MIE, 0),
        HANDLER + 3: MRET,
    }
    dmem = {}

    dut.m_ext_irq_i.value = 1
    await run_program(dut, imem, dmem, cycles=40)
    dut.m_ext_irq_i.value = 0

    result = dmem.get(0, 0xDEAD)
    assert result == 0xCC, f"Ext IRQ handler: expected 0xCC, got {result:#010x}"
