"""
Phase 13 ISA compliance — completion tests.
Covers: PMP fault detection, minstret accuracy, extended RVC value checks.
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer
from cocotb.clock import Clock

CLK_PERIOD = 10  # ns

# ── Instruction encoders ──────────────────────────────────────────────────────

def nop():            return 0x00000013
def addi(rd,rs1,imm): return ((imm&0xFFF)<<20)|(rs1<<15)|(rd<<7)|0x13
def lw(rd,rs1,off=0): return ((off&0xFFF)<<20)|(rs1<<15)|(2<<12)|(rd<<7)|0x03
def sw(rs2,rs1,off=0):
    i=(off&0xFFF); return ((i>>5)<<25)|(rs2<<20)|(rs1<<15)|(2<<12)|((i&0x1F)<<7)|0x23
def jal(rd,off):
    return (((off>>20)&1)<<31)|(((off>>12)&0xFF)<<12)|(((off>>11)&1)<<20)|\
           (((off>>1)&0x3FF)<<21)|(rd<<7)|0x6F
def csrrw(rd,csr,rs1):  return (csr<<20)|(rs1<<15)|(1<<12)|(rd<<7)|0x73
def csrrs(rd,csr,rs1):  return (csr<<20)|(rs1<<15)|(2<<12)|(rd<<7)|0x73
def csrrwi(rd,csr,u):   return (csr<<20)|((u&0x1F)<<15)|(5<<12)|(rd<<7)|0x73

def u32(v): return v & 0xFFFFFFFF
def s32(v): v=u32(v); return v if v<0x80000000 else v-0x100000000

# ── CSR addresses ─────────────────────────────────────────────────────────────
MTVEC   = 0x305
MCAUSE  = 0x342
MINSTRET = 0xB02   # minstret[31:0]
PMPCFG0  = 0x3A0
PMPADDR0 = 0x3B0

# ── Memory layout ─────────────────────────────────────────────────────────────
RES     = 0x400   # result store (byte addr)
HNDL    = 0x200   # trap handler (byte addr)
PMP_TGT = 0x600   # PMP test target (byte addr)

# ── Simulation helpers ────────────────────────────────────────────────────────

async def reset_core(dut, cycles=5):
    dut.rst.value=1; dut.imem_rdata_i.value=nop(); dut.dmem_rdata_i.value=0
    dut.dmem_stall_i.value=0; dut.m_ext_irq_i.value=0
    dut.m_timer_irq_i.value=0; dut.m_sw_irq_i.value=0
    for _ in range(cycles): await RisingEdge(dut.clk)
    dut.rst.value=0

async def run_prog(dut, prog, max_cyc=100, dmem_init=None):
    dmem = dict(dmem_init or {})
    stores = []
    for _ in range(max_cyc):
        await Timer(1, unit="ns")
        pc = int(dut.imem_addr_o.value)
        dut.imem_rdata_i.value = prog.get(pc>>2, nop())
        if int(dut.dmem_re_o.value):
            dut.dmem_rdata_i.value = dmem.get(int(dut.dmem_addr_o.value)>>2, 0)
        await Timer(1, unit="ns")
        if int(dut.dmem_we_o.value):
            ba=int(dut.dmem_addr_o.value); data=int(dut.dmem_wdata_o.value)
            be=int(dut.dmem_be_o.value)
            stores.append((ba, data, be))
            wa=ba>>2; nv=dmem.get(wa,0)
            if be&1: nv=(nv&0xFFFFFF00)|(data&0xFF)
            if be&2: nv=(nv&0xFFFF00FF)|(data&0xFF00)
            if be&4: nv=(nv&0xFF00FFFF)|(data&0xFF0000)
            if be&8: nv=(nv&0x00FFFFFF)|(data&0xFF000000)
            dmem[wa]=nv
        await RisingEdge(dut.clk)
    return stores, dmem

def find(stores, byte_addr):
    for ba, data, _ in reversed(stores):
        if (ba & ~3) == (byte_addr & ~3): return data & 0xFFFFFFFF
    return None

# ── RVC packing helper ────────────────────────────────────────────────────────

_c_nop = 0x0001   # C.NOP

def pack(lo16, hi16=None):
    """Pack two RVC half-words into one 32-bit word (lower half executed first)."""
    hi = hi16 if hi16 is not None else _c_nop
    return ((hi & 0xFFFF) << 16) | (lo16 & 0xFFFF)

# ── RVC encoders ──────────────────────────────────────────────────────────────

def c_mv(rd, rs2):
    """C.MV rd, rs2  (Q2: rd = rs2)."""
    return (0b1000 << 12) | (rd << 7) | (rs2 << 2) | 0b10

def c_add(rd, rs2):
    """C.ADD rd, rs2  (Q2: rd = rd + rs2)."""
    return (0b1001 << 12) | (rd << 7) | (rs2 << 2) | 0b10

def c_slli(rd, shamt):
    """C.SLLI rd, shamt  (Q2)."""
    return ((shamt >> 5) << 12) | (rd << 7) | ((shamt & 0x1F) << 2) | 0b10

def c_lwsp(rd, offset):
    """C.LWSP rd, offset  (Q2, offset multiple of 4, 0-252)."""
    imm5  = (offset >> 5) & 1
    imm42 = (offset >> 2) & 7
    imm76 = (offset >> 6) & 3
    return (0b010 << 13) | (imm5 << 12) | (rd << 7) | (imm42 << 4) | (imm76 << 2) | 0b10

def c_swsp(rs2, offset):
    """C.SWSP rs2, offset  (Q2, offset multiple of 4, 0-252)."""
    imm52 = (offset >> 2) & 0xF
    imm76 = (offset >> 6) & 3
    return (0b110 << 13) | (imm52 << 9) | (imm76 << 7) | (rs2 << 2) | 0b10

def c_lw(rd_p, rs1_p, offset):
    """C.LW rd', offset(rs1')  (Q0, rd'/rs1' in x8-x15, offset 0-124 mult of 4)."""
    imm53 = (offset >> 3) & 7
    imm2  = (offset >> 2) & 1
    imm6  = (offset >> 6) & 1
    return (0b010 << 13) | (imm53 << 10) | ((rs1_p-8) << 7) | (imm2 << 6) | (imm6 << 5) | ((rd_p-8) << 2) | 0b00

def c_sw(rs2_p, rs1_p, offset):
    """C.SW rs2', offset(rs1')  (Q0, rs2'/rs1' in x8-x15)."""
    imm53 = (offset >> 3) & 7
    imm2  = (offset >> 2) & 1
    imm6  = (offset >> 6) & 1
    return (0b110 << 13) | (imm53 << 10) | ((rs1_p-8) << 7) | (imm2 << 6) | (imm6 << 5) | ((rs2_p-8) << 2) | 0b00

def c_srli(rs1_p, shamt):
    """C.SRLI rs1', shamt  (Q1, rs1' in x8-x15)."""
    return (0b100 << 13) | ((shamt>>5) << 12) | (0b00 << 10) | ((rs1_p-8) << 7) | ((shamt&0x1F) << 2) | 0b01

def c_srai(rs1_p, shamt):
    """C.SRAI rs1', shamt  (Q1, rs1' in x8-x15)."""
    return (0b100 << 13) | ((shamt>>5) << 12) | (0b01 << 10) | ((rs1_p-8) << 7) | ((shamt&0x1F) << 2) | 0b01

def c_andi(rs1_p, imm):
    """C.ANDI rs1', imm  (Q1, rs1' in x8-x15, imm 6-bit signed)."""
    imm6 = imm & 0x3F
    return (0b100 << 13) | ((imm6>>5) << 12) | (0b10 << 10) | ((rs1_p-8) << 7) | ((imm6&0x1F) << 2) | 0b01

def c_sub(rd_p, rs2_p):
    """C.SUB rd', rs2'  (Q1, rd'/rs2' in x8-x15)."""
    return (0b100<<13)|(0<<12)|(0b11<<10)|((rd_p-8)<<7)|(0b00<<5)|((rs2_p-8)<<2)|0b01

def c_xor(rd_p, rs2_p):
    """C.XOR rd', rs2'  (Q1)."""
    return (0b100<<13)|(0<<12)|(0b11<<10)|((rd_p-8)<<7)|(0b01<<5)|((rs2_p-8)<<2)|0b01

def c_or(rd_p, rs2_p):
    """C.OR rd', rs2'  (Q1)."""
    return (0b100<<13)|(0<<12)|(0b11<<10)|((rd_p-8)<<7)|(0b10<<5)|((rs2_p-8)<<2)|0b01

def c_and(rd_p, rs2_p):
    """C.AND rd', rs2'  (Q1)."""
    return (0b100<<13)|(0<<12)|(0b11<<10)|((rd_p-8)<<7)|(0b11<<5)|((rs2_p-8)<<2)|0b01

def c_lui(rd, nzimm):
    """C.LUI rd, nzimm  (Q1, rd!=x0/x2, result = nzimm<<12)."""
    imm6 = nzimm & 0x3F
    return (0b011<<13)|((imm6>>5)<<12)|(rd<<7)|((imm6&0x1F)<<2)|0b01

def c_beqz(rs1_p, offset):
    """C.BEQZ rs1', offset  (Q1, branch if rs1'==0)."""
    o8  = (offset >> 8) & 1
    o43 = (offset >> 3) & 3   # {off[4], off[3]}
    o76 = (offset >> 6) & 3   # {off[7], off[6]}
    o21 = (offset >> 1) & 3   # {off[2], off[1]}
    o5  = (offset >> 5) & 1
    return (0b110<<13)|(o8<<12)|(o43<<10)|((rs1_p-8)<<7)|(o76<<5)|(o21<<3)|(o5<<2)|0b01

def c_bnez(rs1_p, offset):
    """C.BNEZ rs1', offset  (Q1, branch if rs1'!=0)."""
    o8  = (offset >> 8) & 1
    o43 = (offset >> 3) & 3
    o76 = (offset >> 6) & 3
    o21 = (offset >> 1) & 3
    o5  = (offset >> 5) & 1
    return (0b111<<13)|(o8<<12)|(o43<<10)|((rs1_p-8)<<7)|(o76<<5)|(o21<<3)|(o5<<2)|0b01

# ── PMP test helper ───────────────────────────────────────────────────────────

def pmp_setup_prog(pmpaddr_val, pmpcfg_byte):
    """Build instruction dict: configure PMP region 0 + trap handler at HNDL."""
    hw = HNDL >> 2
    p = {}
    p[0] = addi(10, 0, RES)           # x10 = RES (preserved across trap)
    p[1] = addi(1, 0, HNDL)
    p[2] = csrrw(0, MTVEC, 1)         # mtvec = HNDL
    p[3] = addi(1, 0, pmpaddr_val)
    p[4] = csrrw(0, PMPADDR0, 1)      # pmpaddr0 = pmpaddr_val
    p[5] = addi(1, 0, pmpcfg_byte)
    p[6] = csrrw(0, PMPCFG0, 1)       # pmpcfg0 byte[0] = pmpcfg_byte
    # Trap handler: read mcause → store to RES → loop
    p[hw]   = csrrs(4, MCAUSE, 0)
    p[hw+1] = sw(4, 10, 0)
    p[hw+2] = jal(0, 0)               # spin
    return p

# ── PMP tests ─────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_pmp_store_fault(dut):
    """PMP: store to locked R-only NA4 region raises mcause=7 (store/AMO access fault)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    # NA4 region over PMP_TGT=0x600: pmpaddr0=0x180, pmpcfg=0x91 (L=1,A=NA4,R=1,W=0,X=0)
    p = pmp_setup_prog(PMP_TGT >> 2, 0x91)
    p[7] = addi(11, 0, PMP_TGT)       # x11 = 0x600
    p[8] = addi(5, 0, 0x42)
    p[9] = sw(5, 11, 0)               # SW to 0x600 → store fault
    stores, _ = await run_prog(dut, p, 120)
    got = find(stores, RES)
    assert got == 7, f"PMP store fault: expected mcause=7, got {got}"


@cocotb.test()
async def test_pmp_load_fault(dut):
    """PMP: load from locked execute-only NA4 region raises mcause=5 (load access fault)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    # pmpcfg=0x94: L=1, NA4, X=1, W=0, R=0 — execute-only locked region
    p = pmp_setup_prog(PMP_TGT >> 2, 0x94)
    p[7] = addi(11, 0, PMP_TGT)       # x11 = 0x600
    p[8] = lw(5, 11, 0)               # LW from 0x600 → load fault
    stores, _ = await run_prog(dut, p, 120)
    got = find(stores, RES)
    assert got == 5, f"PMP load fault: expected mcause=5, got {got}"


@cocotb.test()
async def test_pmp_fetch_fault(dut):
    """PMP: executing from a locked no-execute NA4 region raises mcause=1 (instr access fault)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    # Block byte addr 0x50 (word_addr 0x14): pmpcfg=0x93 (L=1,NA4,R=1,W=1,X=0)
    hw = HNDL >> 2
    p = {}
    p[0] = addi(10, 0, RES)
    p[1] = addi(1, 0, HNDL)
    p[2] = csrrw(0, MTVEC, 1)
    p[3] = addi(1, 0, 0x14)           # pmpaddr0 = 0x14 → NA4 covers byte addr 0x50-0x53
    p[4] = csrrw(0, PMPADDR0, 1)
    p[5] = addi(1, 0, 0x93)           # L=1, NA4, R=1, W=1, X=0
    p[6] = csrrw(0, PMPCFG0, 1)
    # word_addrs 7..0x13 are NOPs by default; 0x14 (byte 0x50) triggers fetch fault in EX
    p[hw]   = csrrs(4, MCAUSE, 0)
    p[hw+1] = sw(4, 10, 0)
    p[hw+2] = jal(0, 0)
    stores, _ = await run_prog(dut, p, 140)
    got = find(stores, RES)
    assert got == 1, f"PMP fetch fault: expected mcause=1, got {got}"


# ── minstret test ─────────────────────────────────────────────────────────────

@cocotb.test()
async def test_minstret_counts_instructions(dut):
    """minstret increments for each retired reg-writing instruction, not every cycle."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    # Reset minstret (csrrwi rd=0 → no commit itself), run 5 ADDIs, drain 4 NOPs,
    # then read minstret — should be exactly 5.
    p = {
        0:  csrrwi(0, MINSTRET, 0),   # reset minstret; rd=0, no commit
        1:  addi(1, 0, 1),
        2:  addi(1, 0, 2),
        3:  addi(1, 0, 3),
        4:  addi(1, 0, 4),
        5:  addi(1, 0, 5),
        6:  nop(), 7: nop(), 8: nop(), 9: nop(),   # drain pipeline
        10: csrrs(2, MINSTRET, 0),    # x2 = minstret (read before this instr commits)
        11: addi(10, 0, RES),
        12: nop(),
        13: sw(2, 10, 0),
    }
    stores, _ = await run_prog(dut, p, 80)
    got = find(stores, RES)
    assert got is not None, "No store to RES"
    assert got == 5, f"minstret: expected 5, got {got}"


# ── RVC value tests ───────────────────────────────────────────────────────────

@cocotb.test()
async def test_rvc_c_mv(dut):
    """C.MV x3, x1: x3 gets x1's value."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10, 0, RES),
        1: addi(1, 0, 0x55),
        2: pack(c_mv(3, 1)),           # C.MV x3, x1 → x3 = 0x55
        3: nop(),
        4: sw(3, 10, 0),
        5: nop(), 6: nop(), 7: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    assert find(stores, RES) == 0x55, f"C.MV: expected 0x55, got {find(stores,RES):#x}"


@cocotb.test()
async def test_rvc_c_add(dut):
    """C.ADD x1, x2: x1 = x1 + x2."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10, 0, RES),
        1: addi(1, 0, 10),
        2: addi(2, 0, 7),
        3: pack(c_add(1, 2)),          # C.ADD x1, x2 → x1 = 17
        4: nop(),
        5: sw(1, 10, 0),
        6: nop(), 7: nop(), 8: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    assert find(stores, RES) == 17, f"C.ADD: expected 17, got {find(stores,RES)}"


@cocotb.test()
async def test_rvc_c_slli(dut):
    """C.SLLI x1, 3: x1 = x1 << 3."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10, 0, RES),
        1: addi(1, 0, 5),
        2: pack(c_slli(1, 3)),         # C.SLLI x1, 3 → x1 = 40
        3: nop(),
        4: sw(1, 10, 0),
        5: nop(), 6: nop(), 7: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    assert find(stores, RES) == 40, f"C.SLLI: expected 40, got {find(stores,RES)}"


@cocotb.test()
async def test_rvc_c_srli(dut):
    """C.SRLI x8, 2: x8 >>= 2 (logical)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10, 0, RES),
        1: addi(8, 0, 0x40),
        2: pack(c_srli(8, 2)),         # C.SRLI x8, 2 → x8 = 0x10
        3: nop(),
        4: sw(8, 10, 0),
        5: nop(), 6: nop(), 7: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    assert find(stores, RES) == 0x10, f"C.SRLI: expected 0x10, got {find(stores,RES):#x}"


@cocotb.test()
async def test_rvc_c_srai(dut):
    """C.SRAI x8, 2: arithmetic right shift preserves sign bit."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    # Load -8 into x8, SRAI by 2 → -2 (0xFFFFFFFE)
    p = {
        0: addi(10, 0, RES),
        1: addi(8, 0, -8),             # x8 = -8 (12-bit sign-extended)
        2: pack(c_srai(8, 2)),         # C.SRAI x8, 2 → x8 = -2
        3: nop(),
        4: sw(8, 10, 0),
        5: nop(), 6: nop(), 7: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    assert find(stores, RES) == u32(-2), \
        f"C.SRAI: expected {u32(-2):#010x}, got {find(stores,RES):#010x}"


@cocotb.test()
async def test_rvc_c_andi(dut):
    """C.ANDI x8, 0xF: x8 = x8 & 15."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10, 0, RES),
        1: addi(8, 0, 0x5F),
        2: pack(c_andi(8, 0xF)),       # C.ANDI x8, 0xF → x8 = 0x0F
        3: nop(),
        4: sw(8, 10, 0),
        5: nop(), 6: nop(), 7: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    assert find(stores, RES) == 0x0F, f"C.ANDI: expected 0x0F, got {find(stores,RES):#x}"


@cocotb.test()
async def test_rvc_c_sub(dut):
    """C.SUB x8, x9: x8 = x8 - x9."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10, 0, RES),
        1: addi(8, 0, 20),
        2: addi(9, 0, 7),
        3: pack(c_sub(8, 9)),          # C.SUB x8, x9 → x8 = 13
        4: nop(),
        5: sw(8, 10, 0),
        6: nop(), 7: nop(), 8: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    assert find(stores, RES) == 13, f"C.SUB: expected 13, got {find(stores,RES)}"


@cocotb.test()
async def test_rvc_c_xor(dut):
    """C.XOR x8, x9: x8 = x8 ^ x9."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10, 0, RES),
        1: addi(8, 0, 0b1010),
        2: addi(9, 0, 0b1100),
        3: pack(c_xor(8, 9)),          # C.XOR x8, x9 → 0b0110 = 6
        4: nop(),
        5: sw(8, 10, 0),
        6: nop(), 7: nop(), 8: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    assert find(stores, RES) == 6, f"C.XOR: expected 6, got {find(stores,RES)}"


@cocotb.test()
async def test_rvc_c_or(dut):
    """C.OR x8, x9: x8 = x8 | x9."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10, 0, RES),
        1: addi(8, 0, 0b0011),
        2: addi(9, 0, 0b1100),
        3: pack(c_or(8, 9)),           # C.OR x8, x9 → 0b1111 = 15
        4: nop(),
        5: sw(8, 10, 0),
        6: nop(), 7: nop(), 8: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    assert find(stores, RES) == 15, f"C.OR: expected 15, got {find(stores,RES)}"


@cocotb.test()
async def test_rvc_c_and(dut):
    """C.AND x8, x9: x8 = x8 & x9."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10, 0, RES),
        1: addi(8, 0, 0xFF),
        2: addi(9, 0, 0x0F),
        3: pack(c_and(8, 9)),          # C.AND x8, x9 → 0x0F
        4: nop(),
        5: sw(8, 10, 0),
        6: nop(), 7: nop(), 8: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    assert find(stores, RES) == 0x0F, f"C.AND: expected 0x0F, got {find(stores,RES):#x}"


@cocotb.test()
async def test_rvc_c_lui(dut):
    """C.LUI x3, 2: x3 = 2 << 12 = 0x2000."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10, 0, RES),
        1: pack(c_lui(3, 2)),          # C.LUI x3, 2 → x3 = 0x2000
        2: nop(),
        3: sw(3, 10, 0),
        4: nop(), 5: nop(), 6: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    assert find(stores, RES) == 0x2000, f"C.LUI: expected 0x2000, got {find(stores,RES):#x}"


@cocotb.test()
async def test_rvc_c_lw(dut):
    """C.LW x9, 4(x8): load word from x8+4."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    base = RES
    p = {
        0: addi(8, 0, base),           # x8 = RES
        1: pack(c_lw(9, 8, 4)),        # C.LW x9, 4(x8) → x9 = mem[RES+4]
        2: nop(),
        3: addi(10, 0, RES),
        4: sw(9, 10, 0),               # store result to RES
        5: nop(), 6: nop(), 7: nop(),
    }
    stores, _ = await run_prog(dut, p, 60, dmem_init={(base+4)>>2: 0xAB})
    assert find(stores, RES) == 0xAB, f"C.LW: expected 0xAB, got {find(stores,RES):#x}"


@cocotb.test()
async def test_rvc_c_sw(dut):
    """C.SW x9, 8(x8): store word to x8+8."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    base = RES
    p = {
        0: addi(8, 0, base),           # x8 = RES
        1: addi(9, 0, 0x99),           # x9 = 0x99
        2: pack(c_sw(9, 8, 8)),        # C.SW x9, 8(x8) → mem[RES+8] = 0x99
        3: nop(), 4: nop(), 5: nop(), 6: nop(), 7: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    got = find(stores, base + 8)
    assert got == 0x99, f"C.SW: expected 0x99, got {got:#x}"


@cocotb.test()
async def test_rvc_c_lwsp(dut):
    """C.LWSP x1, 0: load from stack pointer (x2)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(2, 0, RES),            # x2 (sp) = RES
        1: pack(c_lwsp(1, 0)),         # C.LWSP x1, 0 → x1 = mem[RES]
        2: nop(),
        3: addi(10, 0, RES + 4),
        4: sw(1, 10, 0),               # store result to RES+4
        5: nop(), 6: nop(), 7: nop(),
    }
    stores, _ = await run_prog(dut, p, 60, dmem_init={RES >> 2: 0x77})
    assert find(stores, RES + 4) == 0x77, \
        f"C.LWSP: expected 0x77, got {find(stores, RES+4):#x}"


@cocotb.test()
async def test_rvc_c_swsp(dut):
    """C.SWSP x1, 0: store to stack pointer (x2)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(2, 0, RES),            # sp = RES
        1: addi(1, 0, 0x66),           # x1 = 0x66
        2: pack(c_swsp(1, 0)),         # C.SWSP x1, 0 → mem[sp] = 0x66
        3: nop(), 4: nop(), 5: nop(), 6: nop(), 7: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    assert find(stores, RES) == 0x66, f"C.SWSP: expected 0x66, got {find(stores,RES):#x}"


@cocotb.test()
async def test_rvc_c_beqz_taken(dut):
    """C.BEQZ x8, +8: branch taken (x8==0), skips the addi x1,0,1."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    # Layout: byte 0x00 (WA 0): addi x10
    #         byte 0x04 (WA 1): addi x8,0,0  → x8=0
    #         byte 0x08 (WA 2, lower half): C.BEQZ x8,+8 → if taken, PC=0x10
    #         byte 0x0A (upper half): C.NOP (buffered)
    #         byte 0x0C (WA 3): addi x1,0,1  ← skipped if branch taken
    #         byte 0x10 (WA 4): sw x1, x10, 0
    # If taken: x1 stays 0 (reset value) → store 0
    p = {
        0: addi(10, 0, RES),
        1: addi(8, 0, 0),              # x8 = 0
        2: pack(c_beqz(8, 8)),         # C.BEQZ x8, +8 → branch if x8==0
        3: addi(1, 0, 1),              # byte 0x0C — skipped
        4: sw(1, 10, 0),               # byte 0x10
        5: nop(), 6: nop(), 7: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    got = find(stores, RES)
    assert got == 0, f"C.BEQZ taken: expected 0 (x1 unmodified), got {got}"


@cocotb.test()
async def test_rvc_c_bnez_not_taken(dut):
    """C.BNEZ x8, +8: not taken when x8==0; instruction after branch executes."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10, 0, RES),
        1: addi(8, 0, 0),              # x8 = 0 → C.BNEZ not taken
        2: pack(c_bnez(8, 8)),         # C.BNEZ x8, +8 (not taken)
        3: addi(1, 0, 42),             # byte 0x0C — executed
        4: sw(1, 10, 0),               # byte 0x10
        5: nop(), 6: nop(), 7: nop(),
    }
    stores, _ = await run_prog(dut, p, 60)
    got = find(stores, RES)
    assert got == 42, f"C.BNEZ not taken: expected 42, got {got}"
