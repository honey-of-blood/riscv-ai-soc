"""
Phase 13 — deep value-checking tests for RV32IMAC.
Every test verifies an actual register/memory value via store-monitoring.
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer
from cocotb.clock import Clock

CLK_PERIOD = 10  # ns

# ── Instruction encoders ──────────────────────────────────────────────────────

def nop():           return 0x00000013
def addi(rd,rs1,imm):return ((imm&0xFFF)<<20)|(rs1<<15)|(rd<<7)|0x13
def add(rd,rs1,rs2): return (rs2<<20)|(rs1<<15)|(rd<<7)|0x33
def lw(rd,rs1,off=0):return ((off&0xFFF)<<20)|(rs1<<15)|(2<<12)|(rd<<7)|0x03
def sw(rs2,rs1,off=0):
    i=(off&0xFFF); return ((i>>5)<<25)|(rs2<<20)|(rs1<<15)|(2<<12)|((i&0x1F)<<7)|0x23
def csrrw(rd,csr,rs1): return (csr<<20)|(rs1<<15)|(1<<12)|(rd<<7)|0x73
def csrrs(rd,csr,rs1): return (csr<<20)|(rs1<<15)|(2<<12)|(rd<<7)|0x73
def csrrc(rd,csr,rs1): return (csr<<20)|(rs1<<15)|(3<<12)|(rd<<7)|0x73
def csrrwi(rd,csr,u):  return (csr<<20)|((u&0x1F)<<15)|(5<<12)|(rd<<7)|0x73
def csrrsi(rd,csr,u):  return (csr<<20)|((u&0x1F)<<15)|(6<<12)|(rd<<7)|0x73
def csrrci(rd,csr,u):  return (csr<<20)|((u&0x1F)<<15)|(7<<12)|(rd<<7)|0x73
def ecall():  return 0x00000073
def ebreak(): return 0x00100073
def mret():   return 0x30200073
def jal(rd,off):
    return (((off>>20)&1)<<31)|(((off>>12)&0xFF)<<12)|(((off>>11)&1)<<20)|\
           (((off>>1)&0x3FF)<<21)|(rd<<7)|0x6F

def _amo(f5,rd,rs2,rs1):
    return (f5<<27)|(rs2<<20)|(rs1<<15)|(0b010<<12)|(rd<<7)|0b0101111
def lr_w(rd,rs1):          return (0b00010<<27)|(rs1<<15)|(0b010<<12)|(rd<<7)|0b0101111
def sc_w(rd,rs2,rs1):      return _amo(0b00011,rd,rs2,rs1)
def amoswap_w(rd,rs2,rs1): return _amo(0b00001,rd,rs2,rs1)
def amoadd_w(rd,rs2,rs1):  return _amo(0b00000,rd,rs2,rs1)
def amoand_w(rd,rs2,rs1):  return _amo(0b00111,rd,rs2,rs1)
def amoor_w(rd,rs2,rs1):   return _amo(0b00110,rd,rs2,rs1)
def amoxor_w(rd,rs2,rs1):  return _amo(0b00100,rd,rs2,rs1)
def amomin_w(rd,rs2,rs1):  return _amo(0b10000,rd,rs2,rs1)
def amomax_w(rd,rs2,rs1):  return _amo(0b10100,rd,rs2,rs1)
def amominu_w(rd,rs2,rs1): return _amo(0b11000,rd,rs2,rs1)
def amomaxu_w(rd,rs2,rs1): return _amo(0b11100,rd,rs2,rs1)

# ── CSR addresses ─────────────────────────────────────────────────────────────
MSTATUS=0x300; MISA_CSR=0x301; MIE_CSR=0x304; MTVEC=0x305
MSCRATCH=0x340; MEPC=0x341; MCAUSE=0x342; MCYCLE=0xB00; MHARTID=0xF14

# ── Memory layout ─────────────────────────────────────────────────────────────
# All addresses are byte-addresses. Values chosen to fit positive 12-bit immediates.
RES   = 0x400   # result store (1024)
AMO   = 0x600   # AMO target  (1536)
HNDL  = 0x200   # trap handler start (512)
RES2  = 0x404   # secondary result slot
RES3  = 0x408   # tertiary

# ── Simulation helpers ────────────────────────────────────────────────────────

async def reset_core(dut, cycles=5):
    dut.rst.value=1; dut.imem_rdata_i.value=nop(); dut.dmem_rdata_i.value=0
    dut.dmem_stall_i.value=0; dut.m_ext_irq_i.value=0
    dut.m_timer_irq_i.value=0; dut.m_sw_irq_i.value=0
    for _ in range(cycles): await RisingEdge(dut.clk)
    dut.rst.value=0

async def run_prog(dut, prog, max_cyc=80, dmem_init=None, irq_cycle=None):
    """Run prog dict {word_addr: instr}. Returns (stores, dmem)."""
    dmem = dict(dmem_init or {})
    stores = []
    for cyc in range(max_cyc):
        await Timer(1, unit="ns")
        if irq_cycle is not None:
            dut.m_ext_irq_i.value = 1 if cyc == irq_cycle else 0
        pc = int(dut.imem_addr_o.value)
        dut.imem_rdata_i.value = prog.get(pc>>2, nop())
        if int(dut.dmem_re_o.value):
            dut.dmem_rdata_i.value = dmem.get(int(dut.dmem_addr_o.value)>>2, 0)
        await Timer(1, unit="ns")   # let amo_wdata_m settle
        if int(dut.dmem_we_o.value):
            ba=int(dut.dmem_addr_o.value); data=int(dut.dmem_wdata_o.value); be=int(dut.dmem_be_o.value)
            stores.append((ba,data,be))
            wa=ba>>2; nv=dmem.get(wa,0)
            if be&1: nv=(nv&0xFFFFFF00)|(data&0xFF)
            if be&2: nv=(nv&0xFFFF00FF)|(data&0xFF00)
            if be&4: nv=(nv&0xFF00FFFF)|(data&0xFF0000)
            if be&8: nv=(nv&0x00FFFFFF)|(data&0xFF000000)
            dmem[wa]=nv
        await RisingEdge(dut.clk)
    return stores, dmem

def find(stores, byte_addr):
    """Most recent store to the word at byte_addr."""
    for ba,data,_ in reversed(stores):
        if (ba&~3)==(byte_addr&~3): return data&0xFFFFFFFF
    return None

def u32(v): return v&0xFFFFFFFF
def s32(v): v=u32(v); return v if v<0x80000000 else v-0x100000000

# ── CSR tests ─────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_csrrw_writes_and_reads(dut):
    """CSRRW: writes new value to CSR and returns old value in rd."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    # Write 0x55 to mscratch, read back
    p = {
        0: addi(10,0,RES),        # x10=RES
        1: addi(1,0,0x55),         # x1=0x55
        2: csrrw(0,MSCRATCH,1),   # mscratch=0x55
        3: csrrs(2,MSCRATCH,0),   # x2=mscratch
        4: nop(),
        5: sw(2,10,0),             # mem[RES]=x2
        6: nop(),7:nop(),8:nop(),
    }
    stores,_ = await run_prog(dut,p,60)
    got = find(stores,RES)
    assert got is not None, "No store to RES"
    assert got==0x55, f"CSRRW: expected 0x55, got {got:#x}"


@cocotb.test()
async def test_csrrw_rd_gets_old(dut):
    """CSRRW: rd receives the OLD CSR value before the write."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10,0,RES),
        1: addi(1,0,0xAA),
        2: csrrw(0,MSCRATCH,1),   # prime mscratch=0xAA
        3: addi(2,0,0xBB),
        4: csrrw(3,MSCRATCH,2),   # x3=old(0xAA), mscratch=0xBB
        5: nop(),
        6: sw(3,10,0),             # mem[RES]=0xAA
        7: nop(),8:nop(),
    }
    stores,_ = await run_prog(dut,p,60)
    got = find(stores,RES)
    assert got==0xAA, f"CSRRW old-value: expected 0xAA, got {got:#010x}"


@cocotb.test()
async def test_csrrs_sets_bits(dut):
    """CSRRS: ORs bits into CSR; rd=old value."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10,0,RES),
        1: addi(1,0,0x0F),
        2: csrrw(0,MSCRATCH,1),   # mscratch=0x0F
        3: addi(2,0,0x30),
        4: csrrs(3,MSCRATCH,2),   # x3=0x0F, mscratch=0x3F
        5: csrrs(4,MSCRATCH,0),   # x4=new mscratch=0x3F
        6: nop(),
        7: sw(3,10,0),             # store old(0x0F)
        8: sw(4,10,4),             # store new(0x3F)
        9: nop(),10:nop(),
    }
    stores,_ = await run_prog(dut,p,60)
    assert find(stores,RES)==0x0F,  f"CSRRS rd (old): {find(stores,RES):#x}"
    assert find(stores,RES2)==0x3F, f"CSRRS new: {find(stores,RES2):#x}"


@cocotb.test()
async def test_csrrc_clears_bits(dut):
    """CSRRC: ANDs ~rs1 into CSR — this was broken before the double-apply fix."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10,0,RES),
        1: addi(1,0,0xFF),
        2: csrrw(0,MSCRATCH,1),   # mscratch=0xFF
        3: addi(2,0,0x0F),
        4: csrrc(3,MSCRATCH,2),   # x3=0xFF, mscratch=0xFF&~0x0F=0xF0
        5: csrrs(4,MSCRATCH,0),   # x4=new=0xF0
        6: nop(),
        7: sw(3,10,0),
        8: sw(4,10,4),
        9: nop(),10:nop(),
    }
    stores,_ = await run_prog(dut,p,60)
    assert find(stores,RES)==0xFF,  f"CSRRC rd (old): {find(stores,RES):#x}"
    assert find(stores,RES2)==0xF0, f"CSRRC new (expected 0xF0): {find(stores,RES2):#x}"


@cocotb.test()
async def test_csrrwi_uses_uimm(dut):
    """CSRRWI: writes zero-extended 5-bit uimm, NOT rs1 register value."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10,0,RES),
        1: addi(1,0,0x7FF),        # x1=0x7FF (large — should NOT be used)
        2: csrrwi(0,MSCRATCH,7),   # mscratch=7 (uimm, NOT 0x7FF)
        3: csrrs(2,MSCRATCH,0),    # x2=7
        4: nop(),
        5: sw(2,10,0),
        6: nop(),7:nop(),
    }
    stores,_ = await run_prog(dut,p,60)
    got = find(stores,RES)
    assert got==7, f"CSRRWI uimm: expected 7, got {got:#x}"


@cocotb.test()
async def test_csrrci_clears_with_uimm(dut):
    """CSRRCI: clears bits using zero-extended uimm, not rs1."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10,0,RES),
        1: addi(1,0,0x1F),
        2: csrrw(0,MSCRATCH,1),    # mscratch=0x1F
        3: addi(5,0,0x7FF),        # x5=0x7FF (decoy — should NOT be used)
        4: csrrci(2,MSCRATCH,0x07),# x2=0x1F, mscratch=0x1F&~7=0x18
        5: csrrs(3,MSCRATCH,0),    # x3=new=0x18
        6: nop(),
        7: sw(2,10,0),
        8: sw(3,10,4),
        9: nop(),10:nop(),
    }
    stores,_ = await run_prog(dut,p,60)
    assert find(stores,RES)==0x1F,  f"CSRRCI rd: expected 0x1F, got {find(stores,RES):#x}"
    assert find(stores,RES2)==0x18, f"CSRRCI new: expected 0x18, got {find(stores,RES2):#x}"


@cocotb.test()
async def test_misa_value(dut):
    """misa reads RV32IMAC = 0x4014_1101."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10,0,RES),
        1: csrrs(1,MISA_CSR,0),   # x1=misa
        2: nop(),
        3: sw(1,10,0),
        4: nop(),5:nop(),6:nop(),
    }
    stores,_ = await run_prog(dut,p,40)
    got = find(stores,RES)
    assert got==0x40141101, f"misa: expected 0x40141101, got {got:#010x}"


@cocotb.test()
async def test_mhartid_zero(dut):
    """mhartid reads 0 (single-hart core)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10,0,RES),
        1: csrrs(1,MHARTID,0),
        2: nop(),
        3: sw(1,10,0),
        4: nop(),5:nop(),
    }
    stores,_ = await run_prog(dut,p,40)
    assert find(stores,RES)==0, f"mhartid: expected 0, got {find(stores,RES):#x}"


@cocotb.test()
async def test_mcycle_increments(dut):
    """mcycle increases between two reads."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10,0,RES),
        1: csrrs(1,MCYCLE,0),     # x1=mcycle snapshot 1
        2: nop(),3:nop(),4:nop(),5:nop(),
        6: csrrs(2,MCYCLE,0),     # x2=mcycle snapshot 2
        7: nop(),
        8: sw(1,10,0),
        9: sw(2,10,4),
        10:nop(),11:nop(),
    }
    stores,_ = await run_prog(dut,p,50)
    c1 = find(stores,RES); c2 = find(stores,RES2)
    assert c1 is not None and c2 is not None
    assert c2 > c1, f"mcycle did not increment: c1={c1}, c2={c2}"

# ── Exception tests ───────────────────────────────────────────────────────────

def _trap_prog(trigger, pre=(), post_handler=()):
    """
    Build a program dict.
    Words 0-7: setup (x10=RES, set mtvec to HNDL)
    Word 8+:   pre instructions then trigger
    Word HNDL>>2+: trap handler (reads mcause/mepc, stores them, loops)
    """
    p = {}
    p[0] = addi(10,0,RES)
    p[1] = addi(1,0,HNDL)
    p[2] = csrrw(0,MTVEC,1)     # mtvec=HNDL
    for i,instr in enumerate(pre):
        p[3+i] = instr
    p[3+len(pre)] = trigger
    # pipeline flush nops after trap site
    for i in range(5):
        p[4+len(pre)+i] = nop()
    # trap handler
    hw = HNDL>>2
    for i,instr in enumerate(post_handler):
        p[hw+i] = instr
    for i in range(6):
        p[hw+len(post_handler)+i] = nop()
    return p, 3+len(pre)   # also return trap site word addr


@cocotb.test()
async def test_ecall_mcause(dut):
    """ECALL sets mcause = 11 (M-mode environment call)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    handler = [
        csrrs(1,MCAUSE,0),   # x1=mcause
        sw(1,10,0),           # mem[RES]=mcause
    ]
    p,_ = _trap_prog(ecall(), post_handler=handler)
    stores,_ = await run_prog(dut,p,80)
    got = find(stores,RES)
    assert got==11, f"ECALL mcause: expected 11, got {got}"


@cocotb.test()
async def test_ecall_mepc(dut):
    """ECALL saves PC of the ecall instruction in mepc."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    handler = [
        csrrs(1,MEPC,0),     # x1=mepc
        sw(1,10,0),
    ]
    p, trap_word = _trap_prog(ecall(), post_handler=handler)
    expected_mepc = trap_word * 4   # byte addr of ecall
    stores,_ = await run_prog(dut,p,80)
    got = find(stores,RES)
    assert got==expected_mepc, f"ECALL mepc: expected {expected_mepc:#x}, got {got:#x}"


@cocotb.test()
async def test_ebreak_mcause(dut):
    """EBREAK sets mcause = 3."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    handler = [csrrs(1,MCAUSE,0), sw(1,10,0)]
    p,_ = _trap_prog(ebreak(), post_handler=handler)
    stores,_ = await run_prog(dut,p,80)
    got = find(stores,RES)
    assert got==3, f"EBREAK mcause: expected 3, got {got}"


@cocotb.test()
async def test_illegal_mcause(dut):
    """Undefined encoding → mcause = 2."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    handler = [csrrs(1,MCAUSE,0), sw(1,10,0)]
    p,_ = _trap_prog(0xFFFFFFFF, post_handler=handler)
    stores,_ = await run_prog(dut,p,80)
    got = find(stores,RES)
    assert got==2, f"Illegal mcause: expected 2, got {got}"


@cocotb.test()
async def test_mret_jumps_to_mepc(dut):
    """MRET jumps to mepc; confirmed by a store that only executes at that target."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    TARGET = 0x300  # byte addr (768 < 2047)
    MARKER = 0x7E   # must be < 2048 positive (12-bit addi positive range)
    p = {}
    p[0]  = addi(10,0,RES)
    p[1]  = addi(1,0,TARGET)
    p[2]  = csrrw(0,MEPC,1)      # mepc=TARGET
    p[3]  = mret()
    p[4]  = nop(); p[5]=nop()
    # TARGET code: store marker
    tw = TARGET>>2
    p[tw]   = addi(2,0,MARKER)
    p[tw+1] = sw(2,10,0)
    for i in range(5): p[tw+2+i]=nop()
    stores,_ = await run_prog(dut,p,60)
    got = find(stores,RES)
    assert got==MARKER, f"MRET target not reached or wrong store: {got:#x}"


@cocotb.test()
async def test_mret_restores_mie(dut):
    """MRET restores mstatus.MIE from MPIE (bit 3 is set after MRET)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    # 1. Enable MIE in mstatus
    # 2. Trigger ECALL → mstatus.MPIE=1, MIE=0
    # 3. In handler: MRET → mstatus.MIE=MPIE=1
    # 4. After MRET target: read mstatus, check bit 3
    TARGET = 0x300
    p = {}
    p[0]=addi(10,0,RES); p[1]=addi(1,0,HNDL); p[2]=csrrw(0,MTVEC,1)
    p[3]=addi(2,0,8); p[4]=csrrw(0,MSTATUS,2)  # mstatus.MIE=1
    p[5]=ecall()
    p[6]=nop(); p[7]=nop()
    # handler at HNDL: set mepc=TARGET, mret
    hw=HNDL>>2
    p[hw+0]=addi(3,0,TARGET)
    p[hw+1]=csrrw(0,MEPC,3)     # mepc=TARGET
    p[hw+2]=mret()
    p[hw+3]=nop()
    # TARGET: read mstatus, store bit 3
    tw=TARGET>>2
    p[tw+0]=csrrs(4,MSTATUS,0)  # x4=mstatus
    p[tw+1]=sw(4,10,0)
    for i in range(5): p[tw+2+i]=nop()
    stores,_ = await run_prog(dut,p,100)
    got = find(stores,RES)
    assert got is not None, "MRET: no store found"
    assert got&0x8, f"MRET did not restore MIE: mstatus={got:#010x}"

# ── LR/SC tests ───────────────────────────────────────────────────────────────

@cocotb.test()
async def test_lr_returns_mem_value(dut):
    """LR.W: rd gets the current memory value."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    OLD = 0xCAFEBABE
    p = {
        0: addi(10,0,RES),
        1: addi(11,0,AMO),
        2: lr_w(1,11),            # x1=mem[AMO]
        3: nop(),                  # load-use stall gap
        4: sw(1,10,0),
        5: nop(),6:nop(),7:nop(),
    }
    stores,_ = await run_prog(dut,p,50, dmem_init={AMO>>2: OLD})
    got = find(stores,RES)
    assert got==u32(OLD), f"LR.W: expected {OLD:#010x}, got {got:#010x}"


@cocotb.test()
async def test_sc_success_result_zero(dut):
    """SC.W success (after LR.W to same addr): rd = 0."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10,0,RES),
        1: addi(11,0,AMO),
        2: lr_w(1,11),            # set reservation
        3: addi(2,0,0x42),
        4: sc_w(3,2,11),          # SC → x3=0 (success)
        5: nop(),
        6: sw(3,10,0),
        7: nop(),8:nop(),
    }
    stores,_ = await run_prog(dut,p,60, dmem_init={AMO>>2: 0xDEAD})
    got = find(stores,RES)
    assert got==0, f"SC.W success result: expected 0, got {got}"


@cocotb.test()
async def test_sc_fail_result_one(dut):
    """SC.W without prior LR.W: rd = 1."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    p = {
        0: addi(10,0,RES),
        1: addi(11,0,AMO),
        2: addi(2,0,0x99),
        3: sc_w(3,2,11),          # no LR → x3=1
        4: nop(),
        5: sw(3,10,0),
        6: nop(),7:nop(),
    }
    stores,_ = await run_prog(dut,p,50)
    got = find(stores,RES)
    assert got==1, f"SC.W fail result: expected 1, got {got}"


@cocotb.test()
async def test_sc_success_writes_memory(dut):
    """SC.W success actually updates memory; LW after SC reads new value."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    OLD=5; NEW=9   # small values: no 12-bit truncation, unambiguous
    p = {
        0: addi(10,0,RES),
        1: addi(11,0,AMO),
        2: lr_w(1,11),
        3: addi(2,0,NEW),
        4: sc_w(3,2,11),          # success → mem[AMO]=NEW
        5: nop(),6:nop(),7:nop(),
        8: lw(4,11,0),            # x4=mem[AMO]=NEW
        9: nop(),
        10:sw(4,10,0),
        11:nop(),12:nop(),
    }
    stores,_ = await run_prog(dut,p,80, dmem_init={AMO>>2: OLD})
    got = find(stores,RES)
    assert got==NEW, f"SC.W mem write: expected {NEW:#x}, got {got:#x}"


@cocotb.test()
async def test_sc_fail_no_write(dut):
    """SC.W failure does NOT modify memory."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    OLD=0xBEEF; NEW=0xDEAD
    p = {
        0: addi(10,0,RES),
        1: addi(11,0,AMO),
        2: addi(2,0,NEW),
        3: sc_w(3,2,11),          # no LR → fail → no write
        4: nop(),5:nop(),
        6: lw(4,11,0),
        7: nop(),
        8: sw(4,10,0),
        9: nop(),10:nop(),
    }
    stores,_ = await run_prog(dut,p,60, dmem_init={AMO>>2: OLD})
    got = find(stores,RES)
    assert got==OLD, f"SC.W fail must not write: expected {OLD:#x}, got {got:#x}"

# ── AMO tests ─────────────────────────────────────────────────────────────────

def _amo_prog(amo_instr, old_mem, rs2_val):
    """Standard AMO test program. Returns (prog, dmem_init)."""
    p = {
        0: addi(10,0,RES),
        1: addi(11,0,AMO),
        2: addi(2,0,rs2_val&0x7FF),  # rs2_val must fit 11-bit signed for this helper
        3: amo_instr,                  # rd=x1, rs2=x2, rs1=x11
        4: nop(),                      # stall gap (load-use)
        5: sw(1,10,0),                 # store rd (=old mem)
        6: lw(3,11,0),                 # x3=new mem
        7: nop(),
        8: sw(3,10,4),                 # store new mem
        9: nop(),10:nop(),11:nop(),
    }
    return p, {AMO>>2: old_mem&0xFFFFFFFF}


@cocotb.test()
async def test_amoswap_rd_and_mem(dut):
    """AMOSWAP.W: rd=old, new_mem=rs2."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    OLD=0x10; RS2=0x20  # small values: fit cleanly in 12-bit addi (no truncation)
    p,di = _amo_prog(amoswap_w(1,2,11), OLD, RS2)
    stores,_ = await run_prog(dut,p,70, dmem_init=di)
    assert find(stores,RES)==OLD,  f"AMOSWAP rd:     exp {OLD:#x} got {find(stores,RES):#x}"
    assert find(stores,RES2)==RS2, f"AMOSWAP new mem: exp {RS2:#x} got {find(stores,RES2):#x}"


@cocotb.test()
async def test_amoadd_rd_and_mem(dut):
    """AMOADD.W: rd=old, new_mem=old+rs2."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    OLD=100; RS2=25
    p,di = _amo_prog(amoadd_w(1,2,11), OLD, RS2)
    stores,_ = await run_prog(dut,p,70, dmem_init=di)
    assert find(stores,RES)==OLD,     f"AMOADD rd:     exp {OLD} got {find(stores,RES)}"
    assert find(stores,RES2)==OLD+RS2,f"AMOADD new mem: exp {OLD+RS2} got {find(stores,RES2)}"


@cocotb.test()
async def test_amoand_mem(dut):
    """AMOAND.W: new_mem = old & rs2."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    OLD=0xFF; RS2=0x0F
    p,di = _amo_prog(amoand_w(1,2,11), OLD, RS2)
    stores,_ = await run_prog(dut,p,70, dmem_init=di)
    assert find(stores,RES2)==(OLD&RS2), f"AMOAND mem: exp {OLD&RS2:#x} got {find(stores,RES2):#x}"


@cocotb.test()
async def test_amoor_mem(dut):
    """AMOOR.W: new_mem = old | rs2."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    OLD=0x0F; RS2=0xF0
    p,di = _amo_prog(amoor_w(1,2,11), OLD, RS2)
    stores,_ = await run_prog(dut,p,70, dmem_init=di)
    assert find(stores,RES2)==(OLD|RS2), f"AMOOR mem: exp {OLD|RS2:#x} got {find(stores,RES2):#x}"


@cocotb.test()
async def test_amoxor_mem(dut):
    """AMOXOR.W: new_mem = old ^ rs2."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    OLD=0x5A; RS2=0x3C
    p,di = _amo_prog(amoxor_w(1,2,11), OLD, RS2)
    stores,_ = await run_prog(dut,p,70, dmem_init=di)
    assert find(stores,RES2)==(OLD^RS2), f"AMOXOR mem: exp {OLD^RS2:#x} got {find(stores,RES2):#x}"


@cocotb.test()
async def test_amomin_signed(dut):
    """AMOMIN.W: new_mem = min(old, rs2) using signed comparison."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    # old=5, rs2=3 → min=3 written to mem
    OLD=5; RS2=3
    p,di = _amo_prog(amomin_w(1,2,11), OLD, RS2)
    stores,_ = await run_prog(dut,p,70, dmem_init=di)
    assert find(stores,RES2)==RS2, f"AMOMIN: exp {RS2} got {find(stores,RES2)}"


@cocotb.test()
async def test_amomax_signed(dut):
    """AMOMAX.W: new_mem = max(old, rs2) signed."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    OLD=3; RS2=7
    p,di = _amo_prog(amomax_w(1,2,11), OLD, RS2)
    stores,_ = await run_prog(dut,p,70, dmem_init=di)
    assert find(stores,RES2)==RS2, f"AMOMAX: exp {RS2} got {find(stores,RES2)}"


@cocotb.test()
async def test_amominu_unsigned(dut):
    """AMOMINU.W: unsigned minimum."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    OLD=0x10; RS2=0x5
    p,di = _amo_prog(amominu_w(1,2,11), OLD, RS2)
    stores,_ = await run_prog(dut,p,70, dmem_init=di)
    assert find(stores,RES2)==RS2, f"AMOMINU: exp {RS2} got {find(stores,RES2)}"


@cocotb.test()
async def test_amomaxu_unsigned(dut):
    """AMOMAXU.W: unsigned maximum."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    OLD=0x5; RS2=0x10
    p,di = _amo_prog(amomaxu_w(1,2,11), OLD, RS2)
    stores,_ = await run_prog(dut,p,70, dmem_init=di)
    assert find(stores,RES2)==RS2, f"AMOMAXU: exp {RS2} got {find(stores,RES2)}"

# ── RVC test ──────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_rvc_caddi_value(dut):
    """C.ADDI x1, +7: starting from x1=5, result must be 12."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    # C.ADDI x1, 7: Q1 funct3=000, rd=x1, imm[5]=0, imm[4:0]=00111
    c_addi = (0b000<<13)|(0<<12)|(1<<7)|(0b00111<<2)|0b01
    c_nop  = 0x0001
    packed = (c_nop<<16)|c_addi   # lower=C.ADDI, upper=C.NOP
    p = {
        0: addi(10,0,RES),
        1: addi(1,0,5),     # x1=5
        2: packed,           # C.ADDI x1,x1,7 → x1=12; C.NOP
        3: nop(),
        4: sw(1,10,0),
        5: nop(),6:nop(),7:nop(),
    }
    stores,_ = await run_prog(dut,p,60)
    got = find(stores,RES)
    assert got==12, f"C.ADDI: expected 12, got {got}"


@cocotb.test()
async def test_rvc_cli_value(dut):
    """C.LI x2, 15: loads 15 into x2."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    # C.LI x2, 15: Q1 funct3=010, imm[5]=0, rd=2, imm[4:0]=01111
    c_li = (0b010<<13)|(0<<12)|(2<<7)|(0b01111<<2)|0b01
    c_nop= 0x0001
    packed = (c_nop<<16)|c_li
    p = {
        0: addi(10,0,RES),
        1: packed,           # C.LI x2, 15
        2: nop(),
        3: sw(2,10,0),
        4: nop(),5:nop(),6:nop(),
    }
    stores,_ = await run_prog(dut,p,50)
    got = find(stores,RES)
    assert got==15, f"C.LI: expected 15, got {got}"

# ── Interrupt test ────────────────────────────────────────────────────────────

@cocotb.test()
async def test_external_interrupt_mcause(dut):
    """External interrupt fires when MIE+MEIE enabled; mcause=0x8000_000B."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    # mie bit 11 = 0x800 → addi gives -2048 = 0xFFFFF800, only bits 11,7,3 writable → sets MEIE
    p = {}
    p[0]=addi(10,0,RES)
    p[1]=addi(1,0,HNDL);  p[2]=csrrw(0,MTVEC,1)      # mtvec=HNDL
    p[3]=addi(2,0,0x800&0xFFF); p[4]=csrrw(0,MIE_CSR,2)  # mie=0x800 (MEIE)
    p[5]=addi(3,0,8);      p[6]=csrrw(0,MSTATUS,3)    # mstatus.MIE=1
    p[7]=nop(); p[8]=nop(); p[9]=nop(); p[10]=nop()
    # trap handler: read mcause, store, spin
    hw=HNDL>>2
    p[hw+0]=csrrs(4,MCAUSE,0); p[hw+1]=sw(4,10,0)
    # spin to avoid re-interrupt
    p[hw+2]=jal(0,0)   # J +0 (tight loop)
    for i in range(10): p[hw+3+i]=nop()
    # assert irq at cycle 20 (after setup committed)
    stores,_ = await run_prog(dut,p,80, irq_cycle=20)
    got = find(stores,RES)
    assert got is not None, "No interrupt handler store found"
    assert got==0x8000000B, f"IRQ mcause: expected 0x8000000B, got {got:#010x}"


@cocotb.test()
async def test_interrupt_redirects_to_mtvec(dut):
    """External interrupt redirects PC to mtvec (confirmed by handler store)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, unit="ns").start())
    await reset_core(dut)
    MARKER = 0xAC  # must be < 2048 positive (12-bit addi positive range)
    p = {}
    p[0]=addi(10,0,RES)
    p[1]=addi(1,0,HNDL);  p[2]=csrrw(0,MTVEC,1)
    p[3]=addi(2,0,0x800&0xFFF); p[4]=csrrw(0,MIE_CSR,2)
    p[5]=addi(3,0,8);      p[6]=csrrw(0,MSTATUS,3)
    for i in range(10): p[7+i]=nop()
    hw=HNDL>>2
    p[hw+0]=addi(5,0,MARKER); p[hw+1]=sw(5,10,0)
    p[hw+2]=jal(0,0)
    for i in range(8): p[hw+3+i]=nop()
    stores,_ = await run_prog(dut,p,80, irq_cycle=20)
    got = find(stores,RES)
    assert got==MARKER, f"IRQ did not reach handler: {got:#x}"
