#!/usr/bin/env python3
"""RV32I assembler — Phase 5 SoC full-integration firmware (comprehensive).

Test coverage (section by section):
  Section 1  : SRAM0 L1 cache — cold miss, write hits, read hits,
               dirty eviction (WRITE_BACK), post-eviction cold-miss fill
  Section 1B : APB bridge slave 1 (0x1000_xxxx) — cold miss, cache hit,
               dirty eviction → WRITE_BACK through AXI-APB bridge,
               post-eviction fill back from APB register file
  Section 1C : APB bridge explicit round-trip — write unique sentinel to
               0x1000_0020 (cache set 2), force eviction to commit it to
               APB regs, read back via FILL from bridge → s0=0xC7
  Section 2  : First matmul (W = identity, a = [1,2,3,4]) via accel_top_v2.
               Activations written staggered to scratchpad (0x5001_xxxx).
               W_row at MMIO offsets 8..20, ACT_BASE=0, Y[0..3] at 0x100..0x10C.
               Expected: Y = [1,2,3,4].
  Section 3  : Second matmul (W = 2×identity, same activations).
               Expected: Y = [2,4,6,8]; a6=Y[0]=2, a7=Y[3]=8.
  Done       : Infinite-loop JAL

Register map at done time (checked by testbench):
  a0 = 0xAB  (SRAM0 cache hit from LW after write miss)
  a1 = 0xCD  (SRAM0 cache hit)
  a2 = 0xEF  (SRAM0 cache hit)
  a3 = 0x12  (SRAM0 cache hit)
  a4 = 0xA5  (APB slave 1 cache hit — proves crossbar+bridge fill)
  a5 = 0xA5  (APB slave 1 post-eviction read — proves WRITE_BACK+refill via bridge)
  s0 = 0xC7  (APB explicit round-trip: write→evict→FILL from APB regs[8])
  a6 = 2     (2nd matmul Y[0] = 2*a[0] = 2*1)
  a7 = 8     (2nd matmul Y[3] = 2*a[3] = 2*4)
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
s0=8

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
# SECTION 1C — APB bridge explicit round-trip (cache set 2)
# =============================================================================
# 0x1000_0020 → cache set = addr[9:4] = 0x020>>4 & 0x3F = 2
# 0x1000_0420 → cache set = 0x420>>4 & 0x3F = 2  (same set, different tag → alias)
# APB regs word index = paddr[10:2]:
#   0x1000_0020 → idx=8,  0x1000_0420 → idx=264
#
# Step 1: SW 0xC7 → 0x1000_0020 (write miss → FILL from APB, then write hit → dirty)
# Step 2: SW 0xD8 → 0x1000_0420 (evicts 0x1000_0020 → WRITE_BACK 0xC7 to APB regs[8])
# Step 3: LW s0  ← 0x1000_0020 (evicts 0x1000_0420 → WRITE_BACK; FILL from APB → s0=0xC7)

for w in li32(t3, 0x10000020): emit(w)  # t3 = 0x1000_0020
emit(addi(t2, x0, 0xC7))                # t2 = 0xC7 (APB test sentinel)
emit(sw  (t2, t3, 0))                   # cache write miss → FILL from APB, write 0xC7

for w in li32(t3, 0x10000420): emit(w)  # t3 = 0x1000_0420 (alias: same set 2)
emit(addi(t2, x0, 0xD8))                # different sentinel for alias line
emit(sw  (t2, t3, 0))                   # evicts 0x1000_0020 line → WRITE_BACK 0xC7 → APB

for w in li32(t3, 0x10000020): emit(w)  # t3 = 0x1000_0020 again
emit(lw  (s0, t3, 0))                   # evicts 0x1000_0420, FILLs 0x1000_0020 from APB → s0=0xC7

# =============================================================================
# SECTION 2 — First matmul: W = identity, a = [1,2,3,4]  (accel_top_v2, N=4)
# Register map: W_row[i] at MMIO+8+4i, ACT_BASE at MMIO+4, Y[i] at MMIO+0x100+4i
# Activations: staggered diagonal — a[r] in byte r of bank-0 word of scratchpad row r
#   row 0 @ 0x5001_0000: word = 0x00000001  (byte 0 = 1)
#   row 1 @ 0x5001_0008: word = 0x00000200  (byte 1 = 2)
#   row 2 @ 0x5001_0010: word = 0x00030000  (byte 2 = 3)
#   row 3 @ 0x5001_0018: word = 0x04000000  (byte 3 = 4)
# Expected: Y[0]=1, Y[1]=2, Y[2]=3, Y[3]=4
# =============================================================================
emit(lui(t0, 0x50000))           # t0 = 0x5000_0000 (MMIO base)

# W = identity: W_row[r][c]=1 if r==c else 0 (packed little-endian INT8 per row)
emit(addi(t1, x0,     1)); emit(sw(t1, t0,  8))  # W_row[0]=0x00000001
emit(addi(t1, x0, 0x100)); emit(sw(t1, t0, 12))  # W_row[1]=0x00000100
emit(lui (t1, 0x10));       emit(sw(t1, t0, 16))  # W_row[2]=0x00010000
emit(lui (t1, 0x1000));     emit(sw(t1, t0, 20))  # W_row[3]=0x01000000

# ACT_BASE = 0 (scratchpad row 0)
emit(sw(x0, t0, 4))

# Write activations to scratchpad (row stride = 8 bytes in AXI address space)
for w in li32(t2, 0x50010000): emit(w)           # t2 = 0x5001_0000
emit(addi(t1, x0,        1)); emit(sw(t1, t2,  0))  # row 0 byte 0 = 1
emit(addi(t1, x0,    0x200)); emit(sw(t1, t2,  8))  # row 1 byte 1 = 2
for w in li32(t1,  0x30000): emit(w)
emit(sw(t1, t2, 16))                                 # row 2 byte 2 = 3
for w in li32(t1, 0x4000000): emit(w)
emit(sw(t1, t2, 24))                                 # row 3 byte 3 = 4

# Start accelerator
emit(addi(t1, x0, 1)); emit(sw(t1, t0, 0))          # CTRL.start = 1

# Poll CTRL.done (bit 1) — exercises BEQ branch taken/not-taken + load-use hazard
poll1 = pc()
emit(lw  (t1, t0, 0))
emit(andi(t1, t1, 2))
emit(beq (t1, x0, poll1 - pc()))

# Read Y[0..3] via MMIO (triggers y_cap bus capture for 1st matmul results)
emit(lw(t1, t0, 0x100)); emit(lw(t1, t0, 0x104))
emit(lw(t1, t0, 0x108)); emit(lw(t1, t0, 0x10C))

# Clear ctrl_start so FSM exits DONE_ST → IDLE (required before restart)
emit(sw(x0, t0, 0))

# =============================================================================
# SECTION 3 — Second matmul: W = 2×identity, same activations (still in scratchpad)
# Expected: Y[0]=2, Y[1]=4, Y[2]=6, Y[3]=8
# a6 = Y[0] = 2, a7 = Y[3] = 8
# =============================================================================
# W = 2×I packed per row:
emit(addi(t1, x0,     2)); emit(sw(t1, t0,  8))  # W_row[0]=0x00000002
emit(addi(t1, x0, 0x200)); emit(sw(t1, t0, 12))  # W_row[1]=0x00000200
emit(lui (t1, 0x20));       emit(sw(t1, t0, 16))  # W_row[2]=0x00020000
emit(lui (t1, 0x2000));     emit(sw(t1, t0, 20))  # W_row[3]=0x02000000

# A unchanged — activations remain in scratchpad from Section 2
emit(addi(t1, x0, 1)); emit(sw(t1, t0, 0))          # CTRL.start = 1

# Poll CTRL.done again
poll2 = pc()
emit(lw  (t1, t0, 0))
emit(andi(t1, t1, 2))
emit(beq (t1, x0, poll2 - pc()))

# Read Y[0..3] — y_cap[] bus-capture array gets 2nd-matmul values
emit(lw(t1, t0, 0x100)); emit(lw(t1, t0, 0x104))
emit(lw(t1, t0, 0x108)); emit(lw(t1, t0, 0x10C))

# Read corner outputs into CPU registers for testbench register check
emit(lw(a6, t0, 0x100))          # a6 = Y[0] = 2
emit(lw(a7, t0, 0x10C))          # a7 = Y[3] = 8

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
