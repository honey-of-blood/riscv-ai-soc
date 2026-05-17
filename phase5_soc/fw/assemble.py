#!/usr/bin/env python3
"""Minimal RV32I assembler for the Phase 5 SoC firmware.
Supports: lui, addi, sw, lw, andi, beq, jal (only what the firmware needs).
Outputs: firmware.hex (one 32-bit word per line, big-endian hex).
"""

def lui(rd, imm20):
    """LUI rd, imm20  — load upper 20 bits; imm20 is the raw 20-bit field."""
    assert 0 <= imm20 < (1 << 20), f"lui imm out of range: {imm20:#x}"
    return (imm20 << 12) | (rd << 7) | 0x37

def addi(rd, rs1, imm12):
    """ADDI rd, rs1, imm12  — imm12 is a signed 12-bit value."""
    if imm12 < 0:
        imm12 = imm12 & 0xFFF
    assert 0 <= imm12 < (1 << 12), f"addi imm out of range: {imm12}"
    return (imm12 << 20) | (rs1 << 15) | (0 << 12) | (rd << 7) | 0x13

def sw(rs2, rs1, imm12):
    """SW rs2, imm12(rs1)  — store word."""
    if imm12 < 0:
        imm12 = imm12 & 0xFFF
    imm_hi = (imm12 >> 5) & 0x7F
    imm_lo = imm12 & 0x1F
    return (imm_hi << 25) | (rs2 << 20) | (rs1 << 15) | (2 << 12) | (imm_lo << 7) | 0x23

def lw(rd, rs1, imm12):
    """LW rd, imm12(rs1)  — load word."""
    if imm12 < 0:
        imm12 = imm12 & 0xFFF
    return (imm12 << 20) | (rs1 << 15) | (2 << 12) | (rd << 7) | 0x03

def andi(rd, rs1, imm12):
    """ANDI rd, rs1, imm12."""
    if imm12 < 0:
        imm12 = imm12 & 0xFFF
    return (imm12 << 20) | (rs1 << 15) | (7 << 12) | (rd << 7) | 0x13

def beq(rs1, rs2, offset):
    """BEQ rs1, rs2, offset  — offset is signed byte offset, must be multiple of 2."""
    assert offset % 2 == 0
    if offset < 0:
        offset = offset & 0x1FFF  # 13-bit signed
    imm12  = (offset >> 12) & 1
    imm11  = (offset >> 11) & 1
    imm10_5 = (offset >> 5) & 0x3F
    imm4_1  = (offset >> 1) & 0xF
    return (imm12 << 31) | (imm10_5 << 25) | (rs2 << 20) | (rs1 << 15) | \
           (0 << 12) | (imm4_1 << 8) | (imm11 << 7) | 0x63

def jal(rd, offset):
    """JAL rd, offset  — offset is signed byte offset, multiple of 2."""
    assert offset % 2 == 0
    if offset < 0:
        offset = offset & 0x1FFFFF
    imm20    = (offset >> 20) & 1
    imm10_1  = (offset >> 1) & 0x3FF
    imm11    = (offset >> 11) & 1
    imm19_12 = (offset >> 12) & 0xFF
    return (imm20 << 31) | (imm19_12 << 12) | (imm11 << 20) | (imm10_1 << 21) | \
           (rd << 7) | 0x6F

# ── Register aliases ──────────────────────────────────────────────────────────
x0=0; t0=5; t1=6; t2=7; a0=10; a1=11

# ── Firmware: identity-weight 4×4 matmul via MMIO ────────────────────────────
#
# W = identity matrix packed as 4 words:
#   W[0] = {W[0][3..0]} = {0,0,0,1} = 0x00000001
#   W[1] = {0,0,1,0}   = 0x00000100
#   W[2] = {0,1,0,0}   = 0x00010000
#   W[3] = {1,0,0,0}   = 0x01000000
# A = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]
#   A[0] = 0x04030201, A[1] = 0x08070605
#   A[2] = 0x0C0B0A09, A[3] = 0x100F0E0D
# Expected: Y = A (since W = I)
#   Y[0][0]=1 (at 0x5000_0024), Y[3][3]=16 (at 0x5000_0060)
#
# MMIO map (base 0x5000_0000):
#   +0x00: CTRL  +0x04: W_row0  +0x08: W_row1  +0x0C: W_row2  +0x10: W_row3
#   +0x14: A_row0 +0x18: A_row1 +0x1C: A_row2  +0x20: A_row3
#   +0x24: Y[0][0] .. +0x60: Y[3][3]

def li32(rd, val):
    """Emit lui+addi pair to load an arbitrary 32-bit value into rd."""
    val = val & 0xFFFFFFFF
    lo = val & 0xFFF
    if lo >= 0x800:          # sign-extend compensation
        hi = ((val >> 12) + 1) & 0xFFFFF
        lo_signed = lo - 0x1000  # negative addi immediate
    else:
        hi = (val >> 12) & 0xFFFFF
        lo_signed = lo
    insns = []
    if hi:
        insns.append(lui(rd, hi))
        if lo_signed:
            insns.append(addi(rd, rd, lo_signed))
    else:
        insns.append(addi(rd, x0, lo_signed))
    return insns

instrs = []
labels = {}

def emit(*words):
    instrs.extend(words)

def label(name):
    labels[name] = len(instrs) * 4  # byte address

# ── PC = 0x000 ────────────────────────────────────────────────────────────────
# t0 = 0x50000000  (MMIO base)
emit(lui(t0, 0x50000))

# t1 = 1; store W_row0
emit(addi(t1, x0, 1))
emit(sw(t1, t0, 4))       # W_row0 = 0x00000001

# t1 = 0x100; store W_row1
emit(addi(t1, x0, 0x100))
emit(sw(t1, t0, 8))       # W_row1 = 0x00000100

# t1 = 0x10000 (lui t1, 0x10)
emit(lui(t1, 0x10))
emit(sw(t1, t0, 12))      # W_row2 = 0x00010000

# t1 = 0x01000000 (lui t1, 0x1000)
emit(lui(t1, 0x1000))
emit(sw(t1, t0, 16))      # W_row3 = 0x01000000

# A_row0 = 0x04030201
for w in li32(t1, 0x04030201): emit(w)
emit(sw(t1, t0, 20))

# A_row1 = 0x08070605
for w in li32(t1, 0x08070605): emit(w)
emit(sw(t1, t0, 24))

# A_row2 = 0x0C0B0A09
for w in li32(t1, 0x0C0B0A09): emit(w)
emit(sw(t1, t0, 28))

# A_row3 = 0x100F0E0D
for w in li32(t1, 0x100F0E0D): emit(w)
emit(sw(t1, t0, 32))

# CTRL = 1 (start)
emit(addi(t1, x0, 1))
emit(sw(t1, t0, 0))

# poll: lw t1, 0(t0); andi t1,t1,2; beq t1,x0,poll
label("poll")
emit(lw(t1, t0, 0))
emit(andi(t1, t1, 2))
poll_pc = labels["poll"]
emit(beq(t1, x0, poll_pc - (len(instrs)) * 4))

# Read Y[0][0] into a0 (offset 0x24 = 36)
emit(lw(a0, t0, 36))
# Read Y[3][3] into a1 (offset 0x60 = 96)
emit(lw(a1, t0, 96))

# Infinite loop (done sentinel)
label("done")
done_pc = labels["done"]
emit(jal(x0, done_pc - len(instrs) * 4))

# ── Emit hex file ─────────────────────────────────────────────────────────────
with open("firmware.hex", "w") as f:
    for w in instrs:
        f.write(f"{w:08x}\n")

with open("firmware.dump", "w") as f:
    for i, w in enumerate(instrs):
        f.write(f"0x{i*4:04x}: {w:08x}\n")

print(f"Firmware: {len(instrs)} words ({len(instrs)*4} bytes)")
print("Written: firmware.hex, firmware.dump")
