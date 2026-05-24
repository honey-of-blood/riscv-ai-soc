#!/usr/bin/env python3
"""RV32I assembler — Phase 5 SoC full-integration firmware (comprehensive).

Test coverage (section by section):
  Section 1  : SRAM0 L1 cache — cold miss, write hits, read hits,
               dirty eviction (WRITE_BACK), post-eviction cold-miss fill
  Section 1B : SRAM1 (crossbar slave 1) — cold miss, cache hit, dirty
               eviction to SRAM1, post-eviction fill from SRAM1
  Section 2  : First matmul (W = identity, A = [[1..4],..[13..16]]),
               CTRL start, CTRL.done poll, all 16 Y reads → SRAM store
  Section 3  : Second matmul (W = 2×identity, same A),
               CTRL restart, poll, read Y[0][0] → a6, Y[3][3] → a7
  Done       : Infinite-loop JAL

Register map at done time (checked by testbench):
  a0 = 0xAB  (SRAM0 cache hit from LW after write miss)
  a1 = 0xCD  (SRAM0 cache hit)
  a2 = 0xEF  (SRAM0 cache hit)
  a3 = 0x12  (SRAM0 cache hit)
  a4 = 0xA5  (SRAM1 cache hit  — proves slave 1 routing + fill)
  a5 = 0xA5  (SRAM1 post-eviction read — proves WRITE_BACK to SRAM1 + refill)
  a6 = 2     (2nd matmul Y[0][0] = 2*A[0][0] = 2*1)
  a7 = 32    (2nd matmul Y[3][3] = 2*A[3][3] = 2*16)
"""

def lui(rd, imm20):
    assert 0 <= imm20 < (1 << 20)
    return (imm20 << 12) | (rd << 7) | 0x37

def addi(rd, rs1, imm12):
    if imm12 < 0: imm12 = imm12 & 0xFFF
    return (imm12 << 20) | (rs1 << 15) | (0 << 12) | (rd << 7) | 0x13

def sw(rs2, rs1, imm12):
    if imm12 < 0: imm12 = imm12 & 0xFFF
    return ((imm12 >> 5) << 25) | (rs2 << 20) | (rs1 << 15) | (2 << 12) | \
           ((imm12 & 0x1F) << 7) | 0x23

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

def jal(rd, offset):
    assert offset % 2 == 0
    if offset < 0: offset = offset & 0x1FFFFF
    return ((offset >> 20 & 1) << 31) | ((offset >> 12 & 0xFF) << 12) | \
           ((offset >> 11 & 1) << 20) | ((offset >> 1 & 0x3FF) << 21) | \
           (rd << 7) | 0x6F

# Register aliases
x0=0; t0=5; t1=6; t2=7; t3=28; t4=29
a0=10; a1=11; a2=12; a3=13; a4=14; a5=15; a6=16; a7=17

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
def emit(*words): instrs.extend(words)
def pc(): return len(instrs) * 4

# =============================================================================
# SECTION 1 — SRAM0 / L1 cache test (Phase 1 + Phase 2)
# =============================================================================
# Write 4 words to 0x0000_0000..0x000C (one cache line).
# First SW triggers: IDLE→TAG_CHECK→FILL(SRAM0)→RESPOND+write  (write miss)
# Subsequent SWs to same line: TAG_CHECK→HIT (write hit)
emit(addi(t2, x0,  0xAB))     # t2 = 0xAB
emit(sw  (t2, x0,   0   ))    # SRAM0[0x00]=0xAB  ← cold write miss → fill + write
emit(addi(t2, x0,  0xCD))
emit(sw  (t2, x0,   4   ))    # SRAM0[0x04]=0xCD  ← write hit (same line)
emit(addi(t2, x0,  0xEF))
emit(sw  (t2, x0,   8   ))    # SRAM0[0x08]=0xEF  ← write hit
emit(addi(t2, x0,  0x12))
emit(sw  (t2, x0,  12   ))    # SRAM0[0x0C]=0x12  ← write hit

# Read back — all four are cache hits (dirty line still live).
emit(lw(a0, x0,  0))           # a0=0xAB  ← read hit  (Ph1 forwarding exercised)
emit(lw(a1, x0,  4))           # a1=0xCD  ← read hit
emit(lw(a2, x0,  8))           # a2=0xEF  ← read hit
emit(lw(a3, x0, 12))           # a3=0x12  ← read hit

# Dirty eviction: write to 0x0000_0400 → same cache index 0, different tag.
# Cache: TAG_CHECK→dirty→WRITE_BACK{0xAB,0xCD,0xEF,0x12}→FILL{0x0400}→RESPOND
emit(addi(t3, x0, 0x400))      # t3 = 0x0000_0400 (alias address)
emit(addi(t2, x0,  0x55))      # eviction sentinel
emit(sw  (t2, t3,   0  ))      # WRITE_BACK 0x0000 → SRAM0; FILL 0x0400

# Post-eviction read: 0x0000 now a cold miss → FILL from SRAM0 (has 0xAB)
# But first the 0x0400 dirty line (0x55) must be evicted again.
# TAG_CHECK→dirty(0x55)→WRITE_BACK{0x55}→FILL{0x0000}→RESPOND → t2=0xAB
emit(lw(t2, x0, 0))             # t2=0xAB from SRAM0 post-eviction fill

# Store back to SRAM[0x10] — write miss on set 1; proves fill path delivers right data.
emit(sw(t2, x0, 0x10))          # SRAM0[0x10]=0xAB (dirty in cache, evict later)

# =============================================================================
# SECTION 1B — SRAM1 (crossbar slave 1) full round-trip test (Phase 3)
# =============================================================================
# Proves the crossbar correctly routes 0x1000_xxxx to slave 1 in all directions:
#   cold miss FILL    : AR transactions reach SRAM1
#   write hit         : data stays in cache
#   WRITE_BACK        : AW/W transactions commit to SRAM1
#   post-eviction fill: reading evicted address fetches from SRAM1

emit(lui (t4, 0x10000))         # t4 = 0x1000_0000 (SRAM1 base)
emit(addi(t2, x0, 0xA5))        # t2 = test value 0xA5
emit(sw  (t2, t4,  0  ))        # SRAM1[0x1000_0000]=0xA5 ← cold write miss → FILL SRAM1
emit(lw  (a4, t4,  0  ))        # a4=0xA5 ← cache hit (proves FILL from slave 1 worked)

# Evict to SRAM1: write to alias (same cache set 0, different tag)
emit(addi(t3, t4, 0x400))       # t3 = 0x1000_0400
emit(addi(t2, x0, 0xB6))        # new value
emit(sw  (t2, t3,  0  ))        # WRITE_BACK{0xA5}→SRAM1[0x1000_0000]; FILL{0x1000_0400}

# Post-eviction read from SRAM1: proves data round-tripped correctly.
# 0x1000_0400 is now dirty(0xB6) → evict it first → WRITE_BACK to SRAM1[0x1000_0400]
# Then FILL 0x1000_0000 from SRAM1 (which now holds 0xA5) → a5=0xA5
emit(lw(a5, t4, 0))              # a5=0xA5 ← post-eviction fill from SRAM1

# =============================================================================
# SECTION 2 — First matmul: W = identity, A = [[1..4],[5..8],[9..12],[13..16]]
# Expected: Y = W×A = A → Y[m][n] = 4m + n + 1
# =============================================================================
emit(lui(t0, 0x50000))           # t0 = 0x5000_0000 (MMIO base)

# W = identity matrix (packed INT8 per row, little-endian):
# W_row0={0,0,0,1}=0x00000001  W_row1={0,0,1,0}=0x00000100
# W_row2={0,1,0,0}=0x00010000  W_row3={1,0,0,0}=0x01000000
emit(addi(t1, x0, 1));       emit(sw(t1, t0,  4))  # W_row0
emit(addi(t1, x0, 0x100));   emit(sw(t1, t0,  8))  # W_row1
emit(lui (t1, 0x10));         emit(sw(t1, t0, 12))  # W_row2
emit(lui (t1, 0x1000));       emit(sw(t1, t0, 16))  # W_row3

# A rows
for w in li32(t1, 0x04030201): emit(w)
emit(sw(t1, t0, 20))                                 # A_row0
for w in li32(t1, 0x08070605): emit(w)
emit(sw(t1, t0, 24))                                 # A_row1
for w in li32(t1, 0x0C0B0A09): emit(w)
emit(sw(t1, t0, 28))                                 # A_row2
for w in li32(t1, 0x100F0E0D): emit(w)
emit(sw(t1, t0, 32))                                 # A_row3

# Start accelerator
emit(addi(t1, x0, 1)); emit(sw(t1, t0, 0))          # CTRL.start = 1

# Poll CTRL.done (bit 1) — exercises BEQ branch taken/not-taken + load-use hazard
poll1 = pc()
emit(lw  (t1, t0, 0))
emit(andi(t1, t1, 2))
emit(beq (t1, x0, poll1 - pc()))

# Read all 16 Y outputs via MMIO (bypass path) and store to SRAM[0x20..0x5C].
# Y[0..15] at offsets 0x24, 0x28, ..., 0x60.
emit(lw(t1,t0,0x24)); emit(sw(t1,x0,0x20))   # Y[0][0]=1
emit(lw(t1,t0,0x28)); emit(sw(t1,x0,0x24))   # Y[0][1]=2
emit(lw(t1,t0,0x2C)); emit(sw(t1,x0,0x28))   # Y[0][2]=3
emit(lw(t1,t0,0x30)); emit(sw(t1,x0,0x2C))   # Y[0][3]=4
emit(lw(t1,t0,0x34)); emit(sw(t1,x0,0x30))   # Y[1][0]=5
emit(lw(t1,t0,0x38)); emit(sw(t1,x0,0x34))   # Y[1][1]=6
emit(lw(t1,t0,0x3C)); emit(sw(t1,x0,0x38))   # Y[1][2]=7
emit(lw(t1,t0,0x40)); emit(sw(t1,x0,0x3C))   # Y[1][3]=8
emit(lw(t1,t0,0x44)); emit(sw(t1,x0,0x40))   # Y[2][0]=9
emit(lw(t1,t0,0x48)); emit(sw(t1,x0,0x44))   # Y[2][1]=10
emit(lw(t1,t0,0x4C)); emit(sw(t1,x0,0x48))   # Y[2][2]=11
emit(lw(t1,t0,0x50)); emit(sw(t1,x0,0x4C))   # Y[2][3]=12
emit(lw(t1,t0,0x54)); emit(sw(t1,x0,0x50))   # Y[3][0]=13
emit(lw(t1,t0,0x58)); emit(sw(t1,x0,0x54))   # Y[3][1]=14
emit(lw(t1,t0,0x5C)); emit(sw(t1,x0,0x58))   # Y[3][2]=15
emit(lw(t1,t0,0x60)); emit(sw(t1,x0,0x5C))   # Y[3][3]=16

# =============================================================================
# SECTION 3 — Second matmul: W = 2×identity, same A
# Expected: Y = 2A → Y[m][n] = 2*(4m + n + 1)
# Y[0][0]=2, Y[3][3]=32  (stored in a6, a7 for testbench)
# =============================================================================
# W = 2×I packed per row:
# W_row0={0,0,0,2}=0x02  W_row1={0,0,2,0}=0x200
# W_row2={0,2,0,0}=0x20000  W_row3={2,0,0,0}=0x2000000
emit(addi(t1, x0,  2));       emit(sw(t1, t0,  4))  # W_row0=0x02
emit(addi(t1, x0,  0x200));   emit(sw(t1, t0,  8))  # W_row1=0x200
emit(lui (t1, 0x20));          emit(sw(t1, t0, 12))  # W_row2=0x20000
emit(lui (t1, 0x2000));        emit(sw(t1, t0, 16))  # W_row3=0x2000000

# A unchanged — no need to re-write.
emit(addi(t1, x0, 1)); emit(sw(t1, t0, 0))           # CTRL.start = 1 (clears done, restarts)

# Poll CTRL.done again
poll2 = pc()
emit(lw  (t1, t0, 0))
emit(andi(t1, t1, 2))
emit(beq (t1, x0, poll2 - pc()))

# Read all 16 Y outputs so y_cap[] bus-capture array gets 2nd-matmul values.
emit(lw(t1,t0,0x24)); emit(lw(t1,t0,0x28)); emit(lw(t1,t0,0x2C)); emit(lw(t1,t0,0x30))
emit(lw(t1,t0,0x34)); emit(lw(t1,t0,0x38)); emit(lw(t1,t0,0x3C)); emit(lw(t1,t0,0x40))
emit(lw(t1,t0,0x44)); emit(lw(t1,t0,0x48)); emit(lw(t1,t0,0x4C)); emit(lw(t1,t0,0x50))
emit(lw(t1,t0,0x54)); emit(lw(t1,t0,0x58)); emit(lw(t1,t0,0x5C)); emit(lw(t1,t0,0x60))

# Read corner outputs into CPU registers for testbench register check.
emit(lw(a6, t0, 0x24))          # a6 = Y[0][0] = 2
emit(lw(a7, t0, 0x60))          # a7 = Y[3][3] = 32

# =============================================================================
# Done sentinel — infinite loop
# =============================================================================
done_pc = pc()
emit(jal(x0, done_pc - pc()))   # JAL x0, 0 (self-loop)

# ── Emit files ─────────────────────────────────────────────────────────────────
with open("firmware.hex", "w") as f:
    for w in instrs:
        f.write(f"{w:08x}\n")

with open("firmware.dump", "w") as f:
    for i, w in enumerate(instrs):
        f.write(f"0x{i*4:04x}: {w:08x}\n")

print(f"Firmware: {len(instrs)} words ({len(instrs)*4} bytes)")
print(f"Done sentinel PC: 0x{done_pc:04x}")
print("Written: firmware.hex, firmware.dump")
