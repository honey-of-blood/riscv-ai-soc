"""test_priv.py — Phase 24 privilege & S-mode CSR tests (5 tests).

Tests:
  test_satp_rw               — CSRRW satp; read-back matches written value
  test_smode_csrs_rw         — sepc, scause, stval, stvec, sscratch R/W
  test_trap_delegation        — medeleg set → trap_enter delegates to S-mode
  test_sret_priv_restore      — SRET restores privilege from mstatus.SPP
  test_mret_priv_restore      — MRET restores privilege from mstatus.MPP

DUT: csr_file (Phase 24 version)
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer


# CSR addresses
CSR_MSTATUS  = 0x300
CSR_MEDELEG  = 0x302
CSR_MIDELEG  = 0x303
CSR_MIE      = 0x304
CSR_MTVEC    = 0x305
CSR_MSCRATCH = 0x340
CSR_MEPC     = 0x341
CSR_MCAUSE   = 0x342
CSR_SATP     = 0x180
CSR_SSTATUS  = 0x100
CSR_SIE      = 0x104
CSR_STVEC    = 0x105
CSR_SSCRATCH = 0x140
CSR_SEPC     = 0x141
CSR_SCAUSE   = 0x142
CSR_STVAL    = 0x143

OP_CSRRW = 0b01
OP_CSRRS = 0b10
OP_CSRRC = 0b11


async def reset_csr(dut):
    dut.rst.value           = 1
    dut.csr_en_i.value      = 0
    dut.csr_addr_i.value    = 0
    dut.csr_op_i.value      = 0
    dut.csr_wdata_i.value   = 0
    dut.instr_commit_i.value = 0
    dut.trap_enter_i.value  = 0
    dut.trap_cause_i.value  = 0
    dut.trap_epc_i.value    = 0
    dut.trap_tval_i.value   = 0
    dut.mret_i.value        = 0
    dut.sret_i.value        = 0
    dut.m_ext_irq_i.value   = 0
    dut.m_timer_irq_i.value = 0
    dut.m_sw_irq_i.value    = 0
    dut.tselect_rd_i.value  = 0
    dut.tdata1_rd_i.value   = 0
    dut.tdata2_rd_i.value   = 0
    await Timer(20, unit="ns")
    dut.rst.value = 0
    await Timer(10, unit="ns")


async def csr_write(dut, addr, data, op=OP_CSRRW):
    dut.csr_addr_i.value  = addr
    dut.csr_wdata_i.value = data
    dut.csr_op_i.value    = op
    dut.csr_en_i.value    = 1
    await RisingEdge(dut.clk)
    dut.csr_en_i.value = 0


async def csr_read(dut, addr):
    dut.csr_addr_i.value = addr
    dut.csr_op_i.value   = 0
    dut.csr_en_i.value   = 0   # just combinational read
    await Timer(1, unit="ns")
    return int(dut.csr_rdata_o.value)


# ── Tests ─────────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_satp_rw(dut):
    """CSRRW satp ← SV32 value (MODE=1, ASID=5, PPN=0x12345); read back."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_csr(dut)

    # satp: MODE[31]=1, ASID[30:22]=5, PPN[21:0]=0x12345
    satp_val = (1 << 31) | (5 << 22) | 0x12345
    await csr_write(dut, CSR_SATP, satp_val)

    val = await csr_read(dut, CSR_SATP)
    assert val == satp_val, f"satp: got 0x{val:08x} exp 0x{satp_val:08x}"

    # Check direct output port
    await Timer(1, unit="ns")
    assert int(dut.satp_o.value) == satp_val, "satp_o port mismatch"


@cocotb.test()
async def test_smode_csrs_rw(dut):
    """Write and read back all S-mode CSRs: sepc, scause, stval, stvec, sscratch."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_csr(dut)

    cases = [
        (CSR_SEPC,     0xDEAD_BEF0, "sepc"),
        (CSR_SCAUSE,   0x0000_000B, "scause"),
        (CSR_STVAL,    0xCAFE_0004, "stval"),
        (CSR_STVEC,    0x0000_1000, "stvec"),
        (CSR_SSCRATCH, 0x1234_5678, "sscratch"),
        (CSR_SIE,      0x0000_0222, "sie"),
    ]
    for addr, val, name in cases:
        await csr_write(dut, addr, val)
        got = await csr_read(dut, addr)
        assert got == val, f"{name}: got 0x{got:08x} exp 0x{val:08x}"


@cocotb.test()
async def test_trap_delegation(dut):
    """medeleg[8]=1 (U-mode ECALL) + trap_enter with cause=8 → S-mode trap.
    sepc/scause must hold trap values; priv_mode_o must be S (2'b01)."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_csr(dut)

    # Set medeleg to delegate exception 8 (ECALL from U-mode)
    await csr_write(dut, CSR_MEDELEG, 1 << 8)

    # Simulate mstatus: need priv_mode to be in S or U mode for delegation to fire.
    # Force to S-mode by writing mstatus.MPP=01(S), then MRET.
    # Simpler: write mstatus directly (bit 12:11=01 for MPP=S, bit 7=1 for MPIE).
    await csr_write(dut, CSR_MSTATUS, 0x0000_0880)  # MPP=01(S), MPIE=1
    dut.mret_i.value = 1
    await RisingEdge(dut.clk)
    dut.mret_i.value = 0
    await Timer(1, unit="ns")
    # priv_mode_o should now be S-mode (MPP=01)
    assert int(dut.priv_mode_o.value) == 0b01, \
        f"priv after MRET: got {int(dut.priv_mode_o.value):02b}"

    # Inject trap with cause=8 while in S-mode
    EPC  = 0x0000_4000
    TVAL = 0xABAB_ABAB
    dut.trap_enter_i.value = 1
    dut.trap_cause_i.value = 8       # cause code 8 = U-mode ECALL (but we're in S here;
    dut.trap_epc_i.value   = EPC     # delegation still fires since medeleg[8]=1 and priv<M)
    dut.trap_tval_i.value  = TVAL
    await RisingEdge(dut.clk)
    dut.trap_enter_i.value = 0
    await Timer(1, unit="ns")

    # Privilege should be S-mode (trap was delegated to S)
    priv = int(dut.priv_mode_o.value)
    assert priv == 0b01, f"after S-delegation trap: priv={priv:02b}, expected S=01"

    # sepc and scause should hold the trap info
    sepc   = await csr_read(dut, CSR_SEPC)
    scause = await csr_read(dut, CSR_SCAUSE)
    assert sepc   == EPC, f"sepc: got 0x{sepc:08x} exp 0x{EPC:08x}"
    assert scause == 8,   f"scause: got {scause} exp 8"


@cocotb.test()
async def test_sret_priv_restore(dut):
    """SRET: privilege restored from mstatus.SPP.
    SPP=0 → U-mode; SPP=1 → S-mode."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_csr(dut)

    # Case 1: SPP=0 → SRET restores to U-mode
    # mstatus.SPP is bit 8; write 0 there
    await csr_write(dut, CSR_MSTATUS, 0x0000_0000)  # SPP=0
    dut.sret_i.value = 1
    await RisingEdge(dut.clk)
    dut.sret_i.value = 0
    await Timer(1, unit="ns")
    priv = int(dut.priv_mode_o.value)
    assert priv == 0b00, f"SRET SPP=0: expected U(00), got {priv:02b}"

    # Case 2: SPP=1 → SRET restores to S-mode
    await csr_write(dut, CSR_MSTATUS, 0x0000_0100)  # SPP=1 (bit 8)
    dut.sret_i.value = 1
    await RisingEdge(dut.clk)
    dut.sret_i.value = 0
    await Timer(1, unit="ns")
    priv = int(dut.priv_mode_o.value)
    assert priv == 0b01, f"SRET SPP=1: expected S(01), got {priv:02b}"


@cocotb.test()
async def test_mret_priv_restore(dut):
    """MRET: privilege restored from mstatus.MPP (bits 12:11)."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_csr(dut)

    # MPP=00 (U-mode) → MRET → U
    await csr_write(dut, CSR_MSTATUS, 0x0000_0080)  # MPP=00, MPIE=1
    dut.mret_i.value = 1
    await RisingEdge(dut.clk)
    dut.mret_i.value = 0
    await Timer(1, unit="ns")
    assert int(dut.priv_mode_o.value) == 0b00, "MRET MPP=00: expected U"

    # MPP=01 (S-mode) → MRET → S
    await csr_write(dut, CSR_MSTATUS, 0x0000_0880)  # MPP=01, MPIE=1
    dut.mret_i.value = 1
    await RisingEdge(dut.clk)
    dut.mret_i.value = 0
    await Timer(1, unit="ns")
    assert int(dut.priv_mode_o.value) == 0b01, "MRET MPP=01: expected S"

    # MPP=11 (M-mode) → MRET → M
    await csr_write(dut, CSR_MSTATUS, 0x0000_1880)  # MPP=11, MPIE=1
    dut.mret_i.value = 1
    await RisingEdge(dut.clk)
    dut.mret_i.value = 0
    await Timer(1, unit="ns")
    assert int(dut.priv_mode_o.value) == 0b11, "MRET MPP=11: expected M"
