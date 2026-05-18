#!/usr/bin/env python3
"""RV32I assembler for Phase 5 SoC full-integration firmware.
Exercises all four phases:
  Phase 1 — RV32I pipeline (LUI, ADDI, SW, LW, ANDI, BEQ, JAL)
  Phase 2 — L1 cache (cold miss, cache hit, dirty eviction, post-eviction read)
  Phase 3 — AXI4 crossbar (routes to SRAM slave 0 and accel slave 2)
  Phase 4 — systolic array (full 4×4 identity-weight matmul, all 16 Y reads)
"""

def lui(rd, imm20):
    assert 0 <= imm20 < (1 << 20)
    return (imm20 << 12) | (rd << 7) | 0x37

def addi(rd, rs1, imm12):
    if imm12 < 0: imm12 = imm12 & 0xFFF
    return (imm12 << 20) | (rs1 << 15) | (0 << 12) | (rd << 7) | 0x13

def sw(rs2, rs1, imm12):
    if imm12 < 0: imm12 = imm12 & 0xFFF
    return ((imm12 >> 5) << 25) | (rs2 << 20) | (rs1 << 15) | (2 << 12) | ((imm12 & 0x1F) << 7) | 0x23

def lw(rd, rs1, imm12):
    if imm12 < 0: imm12 = imm12 & 0xFFF
    return (imm12 << 20) | (rs1 << 15) | (2 << 12) | (rd << 7) | 0x03

def andi(rd, rs1, imm12):
    if imm12 < 0: imm12 = imm12 & 0xFFF
    return (imm12 << 20) | (rs1 << 15) | (7 << 12) | (rd << 7) | 0x13

def beq(rs1, rs2, offset):
    assert offset % 2 == 0
    if offset < 0: offset = offset & 0x1FFF
    return ((offset >> 12 & 1) << 31) | ((offset >> 5 & 0x3F) << 25) | \
           (rs2 << 20) | (rs1 << 15) | (0 << 12) | \
           ((offset >> 1 & 0xF) << 8) | ((offset >> 11 & 1) << 7) | 0x63

def bne(rs1, rs2, offset):
    assert offset % 2 == 0
    if offset < 0: offset = offset & 0x1FFF
    return ((offset >> 12 & 1) << 31) | ((offset >> 5 & 0x3F) << 25) | \
           (rs2 << 20) | (rs1 << 15) | (1 << 12) | \
           ((offset >> 1 & 0xF) << 8) | ((offset >> 11 & 1) << 7) | 0x63

def jal(rd, offset):
    assert offset % 2 == 0
    if offset < 0: offset = offset & 0x1FFFFF
    return ((offset >> 20 & 1) << 31) | ((offset >> 12 & 0xFF) << 12) | \
           ((offset >> 11 & 1) << 20) | ((offset >> 1 & 0x3FF) << 21) | \
           (rd << 7) | 0x6F

# ── Register aliases ───────────────────────────────────────────────────────────
x0=0; t0=5; t1=6; t2=7; t3=28; t4=29
a0=10; a1=11; a2=12; a3=13

def li32(rd, val):
    val = val & 0xFFFFFFFF
    lo = val & 0xFFF
    if lo >= 0x800:
        hi = ((val >> 12) + 1) & 0xFFFFF
        lo_signed = lo - 0x1000
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

def emit(*words):
    instrs.extend(words)

def pc():
    return len(instrs) * 4

# =============================================================================
# SECTION 1 — L1 cache exercise (Phase 2)
# =============================================================================
# Write 4 words to SRAM[0x0000..0x000C] (one 16-byte cache line).
# First SW: cold miss → FILL(4 words from SRAM=0) + RESPOND+write → dirty.
# Subsequent SWs to same line: cache hit.

# t0 = SRAM base = 0  (use x0 as base; t0 available for MMIO later)
# t2 = scratch value

emit(addi(t2, x0,  0xAB))   # t2 = 0xAB (171)
emit(sw (t2, x0,    0))      # SRAM[0x00] = 0xAB  ← cold miss (FILL + write)
emit(addi(t2, x0,  0xCD))   # t2 = 0xCD
emit(sw (t2, x0,    4))      # SRAM[0x04] = 0xCD  ← write hit (same line)
emit(addi(t2, x0,  0xEF))   # t2 = 0xEF
emit(sw (t2, x0,    8))      # SRAM[0x08] = 0xEF  ← write hit
emit(addi(t2, x0,  0x12))   # t2 = 0x12
emit(sw (t2, x0,   12))      # SRAM[0x0C] = 0x12  ← write hit

# Read back — all four are cache hits (dirty line still in cache).
emit(lw(a0, x0,  0))         # a0 = 0xAB  ← hit
emit(lw(a1, x0,  4))         # a1 = 0xCD  ← hit
emit(lw(a2, x0,  8))         # a2 = 0xEF  ← hit
emit(lw(a3, x0, 12))         # a3 = 0x12  ← hit

# Force dirty eviction: write to 0x0000_0400 → same cache index (addr[9:4]=0)
# but different tag (addr[31:10]=1) → WRITE_BACK(0x0000_0000) → FILL(0x0000_0400)
emit(addi(t3, x0, 0x400))   # t3 = 0x400 (alias address for same set)
emit(addi(t2, x0, 0x55))    # eviction sentinel value
emit(sw(t2, t3, 0))          # SRAM[0x400] = 0x55 ← WRITE_BACK old line, FILL new

# Read 0x0000_0000 again — now a cold miss (evicted), fetches from SRAM.
# Cache wrote 0xAB to SRAM[0] during eviction, so this should return 0xAB.
emit(lw(t2, x0, 0))          # t2 = 0xAB from SRAM (post-eviction cold miss)

# Store t2 to SRAM[0x10] so testbench can verify it went through cache write path.
emit(sw(t2, x0, 0x10))       # SRAM[0x10] = 0xAB (write hit, new line at 0x00)

# =============================================================================
# SECTION 2 — AI accelerator via MMIO (Phase 4, crossbar Phase 3)
# =============================================================================
# W = 4×4 identity matrix; A = [[1..4],[5..8],[9..12],[13..16]]
# Expected: Y = W×A = A  →  Y[i][j] = A[i][j] = 4i + j + 1
#
# MMIO map (base 0x5000_0000):
#   +0x00: CTRL   +0x04: W_row0  +0x08: W_row1  +0x0C: W_row2  +0x10: W_row3
#   +0x14: A_row0  +0x18: A_row1  +0x1C: A_row2  +0x20: A_row3
#   +0x24: Y[0][0] .. +0x60: Y[3][3]  (16 words, row-major)

emit(lui(t0, 0x50000))       # t0 = 0x5000_0000 (MMIO base)

# W = identity: W_row0=0x01, W_row1=0x100, W_row2=0x10000, W_row3=0x1000000
emit(addi(t1, x0, 1))
emit(sw(t1, t0, 4))           # W_row0 = 0x00000001
emit(addi(t1, x0, 0x100))
emit(sw(t1, t0, 8))           # W_row1 = 0x00000100
emit(lui(t1, 0x10))
emit(sw(t1, t0, 12))          # W_row2 = 0x00010000
emit(lui(t1, 0x1000))
emit(sw(t1, t0, 16))          # W_row3 = 0x01000000

# A rows (packed INT8, little-endian)
for w in li32(t1, 0x04030201): emit(w)
emit(sw(t1, t0, 20))          # A_row0 = 0x04030201

for w in li32(t1, 0x08070605): emit(w)
emit(sw(t1, t0, 24))          # A_row1 = 0x08070605

for w in li32(t1, 0x0C0B0A09): emit(w)
emit(sw(t1, t0, 28))          # A_row2 = 0x0C0B0A09

for w in li32(t1, 0x100F0E0D): emit(w)
emit(sw(t1, t0, 32))          # A_row3 = 0x100F0E0D

# Start accelerator
emit(addi(t1, x0, 1))
emit(sw(t1, t0, 0))           # CTRL[0] = 1 (start)

# Poll CTRL until done bit (bit 1) is set
poll_pc = pc()
emit(lw(t1, t0, 0))
emit(andi(t1, t1, 2))
emit(beq(t1, x0, poll_pc - pc()))

# =============================================================================
# SECTION 3 — Read all 16 Y values via MMIO and store to SRAM[0x20..0x5C]
# Testbench verifies SRAM contents after the done sentinel.
# Y offsets: 0x24, 0x28, ..., 0x60  (16 words)
# Store to SRAM offsets: 0x20, 0x24, ..., 0x5C
# =============================================================================

# Y row 0 (expected: 1,2,3,4)
emit(lw(t1, t0, 0x24)); emit(sw(t1, x0, 0x20))   # Y[0][0]=1 → SRAM[0x20]
emit(lw(t1, t0, 0x28)); emit(sw(t1, x0, 0x24))   # Y[0][1]=2 → SRAM[0x24]
emit(lw(t1, t0, 0x2C)); emit(sw(t1, x0, 0x28))   # Y[0][2]=3 → SRAM[0x28]
emit(lw(t1, t0, 0x30)); emit(sw(t1, x0, 0x2C))   # Y[0][3]=4 → SRAM[0x2C]

# Y row 1 (expected: 5,6,7,8)
emit(lw(t1, t0, 0x34)); emit(sw(t1, x0, 0x30))   # Y[1][0]=5 → SRAM[0x30]
emit(lw(t1, t0, 0x38)); emit(sw(t1, x0, 0x34))   # Y[1][1]=6 → SRAM[0x34]
emit(lw(t1, t0, 0x3C)); emit(sw(t1, x0, 0x38))   # Y[1][2]=7 → SRAM[0x38]
emit(lw(t1, t0, 0x40)); emit(sw(t1, x0, 0x3C))   # Y[1][3]=8 → SRAM[0x3C]

# Y row 2 (expected: 9,10,11,12)
emit(lw(t1, t0, 0x44)); emit(sw(t1, x0, 0x40))   # Y[2][0]=9
emit(lw(t1, t0, 0x48)); emit(sw(t1, x0, 0x44))   # Y[2][1]=10
emit(lw(t1, t0, 0x4C)); emit(sw(t1, x0, 0x48))   # Y[2][2]=11
emit(lw(t1, t0, 0x50)); emit(sw(t1, x0, 0x4C))   # Y[2][3]=12

# Y row 3 (expected: 13,14,15,16)
emit(lw(t1, t0, 0x54)); emit(sw(t1, x0, 0x50))   # Y[3][0]=13
emit(lw(t1, t0, 0x58)); emit(sw(t1, x0, 0x54))   # Y[3][1]=14
emit(lw(t1, t0, 0x5C)); emit(sw(t1, x0, 0x58))   # Y[3][2]=15
emit(lw(t1, t0, 0x60)); emit(sw(t1, x0, 0x5C))   # Y[3][3]=16

# =============================================================================
# Done sentinel — infinite loop
# Testbench detects this PC and then reads SRAM[0x20..0x5C] for verification.
# =============================================================================
done_pc = pc()
emit(jal(x0, done_pc - pc()))   # infinite loop

# ── Emit files ─────────────────────────────────────────────────────────────────
with open("firmware.hex", "w") as f:
    for w in instrs:
        f.write(f"{w:08x}\n")

with open("firmware.dump", "w") as f:
    for i, w in enumerate(instrs):
        f.write(f"0x{i*4:04x}: {w:08x}\n")

print(f"Firmware: {len(instrs)} words ({len(instrs)*4} bytes)")
print("Written: firmware.hex, firmware.dump")
