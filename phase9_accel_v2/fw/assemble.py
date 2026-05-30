#!/usr/bin/env python3
"""Phase 9 SoC end-to-end firmware: DMA + accel_top_v2 full pipeline test.

Pipeline exercised:
  1. CPU writes staggered activations a=[1,2,3,4] to SRAM[0x100..0x10C]
  2. CPU flushes the cache line containing 0x100 by writing to alias address
     0x500 (same cache set index=16, different tag) — forces WRITE_BACK
  3. CPU programs 4 × 4-byte DMA transfers (CH0 reused 4 times):
       SRAM[0x100] → Scratchpad row 0  (0x5001_0000)  a[0]=1 in byte 0
       SRAM[0x104] → Scratchpad row 1  (0x5001_0008)  a[1]=2 in byte 1
       SRAM[0x108] → Scratchpad row 2  (0x5001_0010)  a[2]=3 in byte 2
       SRAM[0x10C] → Scratchpad row 3  (0x5001_0018)  a[3]=4 in byte 3
  4. CPU configures accelerator: all weights=1, ACT_BASE=0, start
  5. CPU polls CTRL[1] (done); reads Y[0] = 1+2+3+4 = 10
  6. CPU writes GPIO: DATA = (Y[0]<<8) | 1  → GPIO[15:8]=0x0A, GPIO[0]=1

Testbench checks:
  [PASS] GPIO[0] = 1        — pipeline reached completion
  [PASS] GPIO[15:8] = 0x0A  — Y[0] = 10 (correct dot product)
"""

# ── Register aliases ──────────────────────────────────────────────────────────
x0=0; t0=5; t1=6; t2=7

# ── Instruction encoders ──────────────────────────────────────────────────────
def lui(rd, imm20):
    assert 0 <= imm20 < (1<<20), f"LUI imm20 {imm20:#x} out of range"
    return (imm20 << 12) | (rd << 7) | 0x37

def addi(rd, rs1, imm12):
    if imm12 < 0: imm12 = imm12 & 0xFFF
    return (imm12 << 20) | (rs1 << 15) | (0 << 12) | (rd << 7) | 0x13

def ori(rd, rs1, imm12):
    if imm12 < 0: imm12 = imm12 & 0xFFF
    return (imm12 << 20) | (rs1 << 15) | (6 << 12) | (rd << 7) | 0x13

def slli(rd, rs1, shamt):
    return (0 << 25) | (shamt << 20) | (rs1 << 15) | (1 << 12) | (rd << 7) | 0x13

def sw(rs2, rs1, imm12):
    if imm12 < 0: imm12 = imm12 & 0xFFF
    return ((imm12 >> 5) << 25) | (rs2 << 20) | (rs1 << 15) | \
           (2 << 12) | ((imm12 & 0x1F) << 7) | 0x23

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

# ── Peripheral addresses ──────────────────────────────────────────────────────
GPIO_BASE  = 0x10002000
DMA_BASE   = 0x10007000
ACCEL_BASE = 0x50000000
SP_BASE    = 0x50010000  # 0x5001_0000 (scratchpad write aperture)

# ═══════════════════════════════════════════════════════════════════════════════
# 1. Set GPIO direction register: all 16 bits as outputs
# ═══════════════════════════════════════════════════════════════════════════════
emit(*li32(t0, GPIO_BASE))
emit(addi(t1, x0, -1))        # t1 = 0xFFFF (12-bit -1 sign-extends to full 1s)
emit(sw(t1, t0, 4))            # GPIO DIR (+0x04) = all outputs

# ═══════════════════════════════════════════════════════════════════════════════
# 2. Store staggered activations in SRAM[0x100..0x10C]
#    Row r: a[r] occupies byte r of the 32-bit bank-0 word
#    accel FSM reads a_feed[r] = sp_accel_rdata[r*8+:8], so each row r
#    must place its activation in byte r of scratchpad row r, bank 0.
# ═══════════════════════════════════════════════════════════════════════════════
emit(*li32(t2, 0x100))         # t2 = SRAM base for activation data

emit(addi(t1, x0, 1))
emit(sw(t1, t2, 0))            # SRAM[0x100] = 0x00000001  (a[0]=1, byte 0)

emit(*li32(t1, 0x200))
emit(sw(t1, t2, 4))            # SRAM[0x104] = 0x00000200  (a[1]=2, byte 1)

emit(*li32(t1, 0x30000))
emit(sw(t1, t2, 8))            # SRAM[0x108] = 0x00030000  (a[2]=3, byte 2)

emit(*li32(t1, 0x4000000))
emit(sw(t1, t2, 12))           # SRAM[0x10C] = 0x04000000  (a[3]=4, byte 3)

# ═══════════════════════════════════════════════════════════════════════════════
# 3. Flush cache: force write-back of SRAM[0x100..0x10F] to backing store
#    L1 cache: 64 sets, 16-byte lines; index = addr[9:4]
#    0x100 → index 16, tag 0 ; 0x500 → index 16, tag 1 (alias, forces eviction)
# ═══════════════════════════════════════════════════════════════════════════════
emit(*li32(t2, 0x500))         # alias address: same set 16, different tag
emit(addi(t1, x0, 0x55))
emit(sw(t1, t2, 0))            # WRITE_BACK of 0x100 line → SRAM, CPU stalls until done

# ═══════════════════════════════════════════════════════════════════════════════
# 4. Four single-word DMA transfers: SRAM → Scratchpad
#    DMA now drives AW and W simultaneously (fixed FSM), which the scratchpad
#    requires.  Each transfer: CH0_SRC, CH0_DST, CH0_LEN=4, CH0_CTRL=start.
#    Poll CTRL[1] (done), then clear.
# ═══════════════════════════════════════════════════════════════════════════════
emit(*li32(t0, DMA_BASE))

dma_srcs = [0x100, 0x104, 0x108, 0x10C]
dma_dsts = [SP_BASE, SP_BASE+8, SP_BASE+16, SP_BASE+24]

for src, dst in zip(dma_srcs, dma_dsts):
    emit(*li32(t1, src))
    emit(sw(t1, t0, 0))        # CH0_SRC
    emit(*li32(t1, dst))
    emit(sw(t1, t0, 4))        # CH0_DST
    emit(addi(t1, x0, 4))
    emit(sw(t1, t0, 8))        # CH0_LEN = 4 bytes
    emit(addi(t1, x0, 1))
    emit(sw(t1, t0, 12))       # CH0_CTRL = 1 (start)
    poll = pc()
    emit(lw(t1, t0, 12))       # read CH0_CTRL
    emit(andi(t1, t1, 2))      # isolate done bit
    emit(beq(t1, x0, poll - pc()))  # loop until done
    emit(sw(x0, t0, 12))       # CH0_CTRL = 0 (clear)

# ═══════════════════════════════════════════════════════════════════════════════
# 5. Configure and fire accelerator
#    W[r][c]=1 for all r,c → w_row[r] = 0x01010101; ACT_BASE=0 (row 0)
# ═══════════════════════════════════════════════════════════════════════════════
emit(*li32(t0, ACCEL_BASE))

emit(*li32(t1, 0x01010101))
emit(sw(t1, t0,  8))           # W_row[0]
emit(sw(t1, t0, 12))           # W_row[1]
emit(sw(t1, t0, 16))           # W_row[2]
emit(sw(t1, t0, 20))           # W_row[3]
emit(sw(x0, t0,  4))           # ACT_BASE = 0
emit(addi(t1, x0, 1))
emit(sw(t1, t0,  0))           # CTRL = start

poll_accel = pc()
emit(lw(t1,  t0, 0))
emit(andi(t1, t1, 2))
emit(beq(t1, x0, poll_accel - pc()))

emit(lw(t1, t0, 0x100))       # t1 = Y[0] = 10

# ═══════════════════════════════════════════════════════════════════════════════
# 6. Signal done via GPIO
#    GPIO[15:8] = Y[0][7:0] = 0x0A, GPIO[0] = 1
# ═══════════════════════════════════════════════════════════════════════════════
emit(*li32(t0, GPIO_BASE))
emit(slli(t2, t1, 8))          # t2 = Y[0] << 8 = 0x0000_0A00
emit(ori(t2, t2, 1))            # t2 |= 1 = 0x0000_0A01
emit(sw(t2, t0, 0))             # GPIO DATA = t2

# ═══════════════════════════════════════════════════════════════════════════════
# 7. Infinite loop
# ═══════════════════════════════════════════════════════════════════════════════
done_pc = pc()
emit(jal(x0, done_pc - pc()))

# ── Emit files ────────────────────────────────────────────────────────────────
with open("firmware.hex", "w") as f:
    for w in instrs:
        f.write(f"{w:08x}\n")

with open("firmware.dump", "w") as f:
    for i, w in enumerate(instrs):
        f.write(f"0x{i*4:04x}: {w:08x}\n")

print(f"Firmware: {len(instrs)} words ({len(instrs)*4} bytes)")
print(f"Done sentinel PC: 0x{done_pc:04x}")
print("Written: firmware.hex, firmware.dump")
