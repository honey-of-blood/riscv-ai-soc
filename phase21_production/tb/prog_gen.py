"""Random RV32IM program generator for ISS-vs-DUT comparison.

Program layout (word-addressed from 0):
  0..14   : addi x1..x15, x0, C   — prologue (16 regs init; 15 instructions)
  15      : lui x16, 1             — x16 = 0x1000 (DONE_ADDR)
  16..N+15: N random body instrs   — body
  N+16    : sw x1, 0(x16)          — done sentinel (byte addr 0x1000)
  N+17    : jal x0, 0              — infinite loop (program end)

Termination (DUT side): detect dmem_we_o && dmem_addr_o == 0x1000.
Termination (ISS side): run_n(N + 17) steps (through SW; JAL is optional).
"""

import random

# ── Instruction encoders (duplicated from test_riscv_core.py pattern) ────────

OP_R, OP_IMM, OP_LOAD, OP_STORE = 0x33, 0x13, 0x03, 0x23
OP_BRANCH, OP_JAL, OP_LUI, OP_MEXT = 0x63, 0x6F, 0x37, 0x33


def _r(f7, rs2, rs1, f3, rd):
    return (f7 << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | OP_R


def _i(imm, rs1, f3, rd, op):
    return ((imm & 0xFFF) << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | op


def _s(imm, rs2, rs1, f3):
    imm &= 0xFFF
    return (((imm >> 5) & 0x7F) << 25) | (rs2 << 20) | (rs1 << 15) | \
           (f3 << 12) | ((imm & 0x1F) << 7) | OP_STORE


def _b(imm, rs2, rs1, f3):
    imm &= 0x1FFF
    return (((imm >> 12) & 1) << 31) | (((imm >> 5) & 0x3F) << 25) | \
           (rs2 << 20) | (rs1 << 15) | (f3 << 12) | \
           (((imm >> 1) & 0xF) << 8) | (((imm >> 11) & 1) << 7) | OP_BRANCH


def _j(imm, rd):
    imm &= 0x1FFFFF
    return (((imm >> 20) & 1) << 31) | (((imm >> 1) & 0x3FF) << 21) | \
           (((imm >> 11) & 1) << 20) | (((imm >> 12) & 0xFF) << 12) | \
           (rd << 7) | OP_JAL


# Named encoders
NOP = _i(0, 0, 0, 0, OP_IMM)         # addi x0, x0, 0

def addi(rd, rs1, imm):  return _i(imm, rs1, 0, rd, OP_IMM)
def ori (rd, rs1, imm):  return _i(imm, rs1, 6, rd, OP_IMM)
def xori(rd, rs1, imm):  return _i(imm, rs1, 4, rd, OP_IMM)
def andi(rd, rs1, imm):  return _i(imm, rs1, 7, rd, OP_IMM)
def slti(rd, rs1, imm):  return _i(imm, rs1, 2, rd, OP_IMM)
def sltiu(rd, rs1, imm): return _i(imm, rs1, 3, rd, OP_IMM)
def slli(rd, rs1, sh):   return _i(sh & 0x1F, rs1, 1, rd, OP_IMM)
def srli(rd, rs1, sh):   return _i(sh & 0x1F, rs1, 5, rd, OP_IMM)
def srai(rd, rs1, sh):   return _i(0x400 | (sh & 0x1F), rs1, 5, rd, OP_IMM)

def add (rd, r1, r2): return _r(0x00, r2, r1, 0, rd)
def sub (rd, r1, r2): return _r(0x20, r2, r1, 0, rd)
def and_(rd, r1, r2): return _r(0x00, r2, r1, 7, rd)
def or_ (rd, r1, r2): return _r(0x00, r2, r1, 6, rd)
def xor_(rd, r1, r2): return _r(0x00, r2, r1, 4, rd)
def sll (rd, r1, r2): return _r(0x00, r2, r1, 1, rd)
def srl (rd, r1, r2): return _r(0x00, r2, r1, 5, rd)
def sra (rd, r1, r2): return _r(0x20, r2, r1, 5, rd)
def slt (rd, r1, r2): return _r(0x00, r2, r1, 2, rd)
def sltu(rd, r1, r2): return _r(0x00, r2, r1, 3, rd)

def mul  (rd, r1, r2): return _r(0x01, r2, r1, 0, rd)
def mulh (rd, r1, r2): return _r(0x01, r2, r1, 1, rd)
def mulhsu(rd,r1, r2): return _r(0x01, r2, r1, 2, rd)
def mulhu(rd, r1, r2): return _r(0x01, r2, r1, 3, rd)
def div_ (rd, r1, r2): return _r(0x01, r2, r1, 4, rd)
def divu (rd, r1, r2): return _r(0x01, r2, r1, 5, rd)
def rem_ (rd, r1, r2): return _r(0x01, r2, r1, 6, rd)
def remu (rd, r1, r2): return _r(0x01, r2, r1, 7, rd)

def lw  (rd, rs1, imm): return _i(imm, rs1, 2, rd, OP_LOAD)
def lh  (rd, rs1, imm): return _i(imm, rs1, 1, rd, OP_LOAD)
def lb  (rd, rs1, imm): return _i(imm, rs1, 0, rd, OP_LOAD)
def lhu (rd, rs1, imm): return _i(imm, rs1, 5, rd, OP_LOAD)
def lbu (rd, rs1, imm): return _i(imm, rs1, 4, rd, OP_LOAD)
def sw  (rs2, rs1, imm): return _s(imm, rs2, rs1, 2)

def lui(rd, imm_val):
    return (((imm_val >> 12) & 0xFFFFF) << 12) | (rd << 7) | OP_LUI

def jal(rd, imm): return _j(imm, rd)

# ── Constants ─────────────────────────────────────────────────────────────────

DONE_ADDR = 0x1000       # byte address: sw x1, 0(x16) → mem[0x400] = x1
WORK_REGS = list(range(1, 16))   # x1..x15 used in random body
DONE_REG  = 16                   # x16 holds DONE_ADDR
PROLOGUE_LEN = 16        # 15 addi + 1 lui
EPILOGUE_LEN = 2         # sw + jal


# ── Generator ─────────────────────────────────────────────────────────────────

def gen_program(n_body=20, seed=0, m_ext_frac=0.15, branch_frac=0.10):
    """Return (instrs, iss_steps, init_regs) for an RV32IM random program.

    instrs    : flat list of 32-bit instruction words
    iss_steps : number of ISS steps to run for register comparison
    init_regs : dict {reg -> s32 value} set by prologue (for verification docs)
    """
    rng = random.Random(seed)

    instrs = []
    init_regs = {}

    # ── Prologue ──────────────────────────────────────────────────────────────
    for r in WORK_REGS:
        v = rng.randint(-512, 511)  # small values to avoid overflow surprises
        instrs.append(addi(r, 0, v))
        init_regs[r] = v

    instrs.append(lui(DONE_REG, DONE_ADDR))  # x16 = 0x1000

    # ── Body ──────────────────────────────────────────────────────────────────
    body_start_word = len(instrs)   # for forward-branch offset calculation

    i = 0
    while i < n_body:
        rd  = rng.choice(WORK_REGS)
        rs1 = rng.choice(WORK_REGS)
        rs2 = rng.choice(WORK_REGS)
        imm = rng.randint(-128, 127)
        sh  = rng.randint(1, 31)
        r   = rng.random()

        if r < m_ext_frac:
            # M-extension (avoid div/rem by registers that might be 0)
            op = rng.choice([mul, mulh, mulhu, mulhsu])
            instrs.append(op(rd, rs1, rs2))
            i += 1
        elif r < m_ext_frac + branch_frac:
            # Forward branch: skip 1 or 2 instructions
            skip = rng.randint(1, min(2, n_body - i - 1)) if (n_body - i) > 2 else 1
            f3   = rng.choice([0, 1, 4, 5, 6, 7])   # BEQ BNE BLT BGE BLTU BGEU
            offset = (skip + 1) * 4   # branch jumps over 'skip' instructions + itself
            instrs.append(_b(offset, rs2, rs1, f3))
            for _ in range(skip):
                # These may or may not execute; pad with NOPs so ISS/DUT agree
                instrs.append(NOP)
            i += 1 + skip
        else:
            # ALU
            op = rng.choice([
                lambda: add (rd, rs1, rs2),
                lambda: sub (rd, rs1, rs2),
                lambda: and_(rd, rs1, rs2),
                lambda: or_ (rd, rs1, rs2),
                lambda: xor_(rd, rs1, rs2),
                lambda: sll (rd, rs1, rs2),
                lambda: srl (rd, rs1, rs2),
                lambda: sra (rd, rs1, rs2),
                lambda: slt (rd, rs1, rs2),
                lambda: sltu(rd, rs1, rs2),
                lambda: addi(rd, rs1, imm),
                lambda: andi(rd, rs1, imm),
                lambda: ori (rd, rs1, imm),
                lambda: xori(rd, rs1, imm),
                lambda: slli(rd, rs1, sh),
                lambda: srli(rd, rs1, sh),
                lambda: srai(rd, rs1, sh),
            ])
            instrs.append(op())
            i += 1

    # ── Epilogue ──────────────────────────────────────────────────────────────
    instrs.append(sw(1, DONE_REG, 0))    # sw x1, 0(x16) — done sentinel
    instrs.append(jal(0, 0))              # infinite loop

    iss_steps = PROLOGUE_LEN + len(instrs) - PROLOGUE_LEN - EPILOGUE_LEN + EPILOGUE_LEN
    # = total instructions (ISS runs them all including SW; JAL is a no-reg-change)
    iss_steps = len(instrs)

    return instrs, iss_steps, init_regs


def gen_load_store_program(n_body=20, seed=0):
    """Program with load/store operations.

    Data memory pre-initialized at byte addresses 0x2000..0x20FC (64 words).
    Uses x17 as base pointer (x17 = 0x2000 via lui).
    """
    rng = random.Random(seed)
    instrs = []

    # Prologue: init x1-x14
    init_regs = {}
    for r in range(1, 15):
        v = rng.randint(-128, 127)
        instrs.append(addi(r, 0, v))
        init_regs[r] = v

    # x15 = base: lui x15, 2 → x15 = 0x2000
    instrs.append(lui(15, 0x2000))
    # x16 = done addr
    instrs.append(lui(DONE_REG, DONE_ADDR))

    # Body: mix of sw/lw/arithmetic with x15 as base
    data_mem = {}
    # Pre-init 8 words of data mem (ISS and DUT share same init)
    for wi in range(8):
        val = rng.randint(0, 0xFFFF)
        data_mem[0x2000 // 4 + wi] = val

    for _ in range(n_body):
        off = rng.randint(0, 7) * 4      # aligned word offsets into data area
        rs  = rng.choice(range(1, 15))
        rd  = rng.choice(range(1, 15))
        r   = rng.random()
        if r < 0.4:
            instrs.append(sw(rs, 15, off))    # sw xrs, off(x15)
        elif r < 0.7:
            instrs.append(lw(rd, 15, off))    # lw xrd, off(x15)
        else:
            rs2 = rng.choice(range(1, 15))
            instrs.append(add(rd, rs, rs2))

    instrs.append(sw(1, DONE_REG, 0))
    instrs.append(jal(0, 0))

    iss_steps = len(instrs)
    return instrs, iss_steps, init_regs, data_mem
