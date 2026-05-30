#!/usr/bin/env python3
"""Phase 8 demo firmware: UART "Hello, World!" + timer-driven GPIO blink.

Memory map (Phase 8 SoC):
  0x0000_0000  Instruction ROM (this firmware)
  0x1000_1000  UART  (sel=1 in APB demux)
  0x1000_2000  GPIO  (sel=2)
  0x1000_3000  Timer (sel=3) — mtime counter + ctrl
  0x1000_5000  CLINT (sel=5) — MSIP + mtime pass-through + mtimecmp proxy

Layout:
  PC=0x0000  Reset vector: JAL x0, +0x40  → jump to _start
  PC=0x0004  NOP (gap)
  PC=0x0008  Timer ISR  (mtvec = 0x0008, direct mode)
  PC=0x0040  _start

Timer ISR (clobbers t0/t1/t2 = x5/x6/x7):
  1. Read CLINT mtimecmp_lo, add TICK_PERIOD, write back  → re-arm
  2. Toggle GPIO bit 0 via XOR  → LED blink
  3. MRET

Main (_start):
  1. Set GPIO direction = all output
  2. Set mtvec = 0x0008
  3. Set s2 = UART_BASE (before enabling interrupts)
  4. Write CLINT mtimecmp_lo = TICK, mtimecmp_hi = 0  → first tick
  5. Enable timer: TIMER_CTRL = 3 (enable + irq_en)
  6. Enable interrupts: mie.MTIE, then mstatus.MIE
  7. Loop: print "Hello, World!\\r\\n" via UART (polling tx_full)
"""

# ── Peripheral base addresses ───────────────────────────────────────────────
UART_BASE  = 0x10001000
GPIO_BASE  = 0x10002000
TIMER_BASE = 0x10003000
CLINT_BASE = 0x10005000
TICK       = 1000   # clock cycles between timer interrupts (small for simulation)

# ── Instruction encoders ────────────────────────────────────────────────────
def lui(rd, imm20):
    assert 0 <= imm20 < (1 << 20), f"LUI imm {imm20} out of range"
    return (imm20 << 12) | (rd << 7) | 0x37

def addi(rd, rs1, imm12):
    if imm12 < 0: imm12 = imm12 & 0xFFF
    return (imm12 << 20) | (rs1 << 15) | (0 << 12) | (rd << 7) | 0x13

def add(rd, rs1, rs2):
    return (rs2 << 20) | (rs1 << 15) | (0 << 12) | (rd << 7) | 0x33

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

def xori(rd, rs1, imm12):
    if imm12 < 0: imm12 = imm12 & 0xFFF
    return (imm12 << 20) | (rs1 << 15) | (4 << 12) | (rd << 7) | 0x13

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

def csrrw(rd, csr, rs1):
    return ((csr & 0xFFF) << 20) | (rs1 << 15) | (1 << 12) | (rd << 7) | 0x73

NOP  = 0x00000013   # addi x0, x0, 0
MRET = 0x30200073

# ── Register aliases ────────────────────────────────────────────────────────
x0=0; t0=5; t1=6; t2=7; t3=28; t4=29
s2=18; s3=19   # s2=UART base (stable), s3=char to send (ISR-safe)

# CSR addresses
CSR_MSTATUS = 0x300
CSR_MIE     = 0x304
CSR_MTVEC   = 0x305

# ── Assembler state ─────────────────────────────────────────────────────────
instrs = []
def emit(*words): instrs.extend(words)
def pc():         return len(instrs) * 4

# ── PC=0x0000: reset vector ──────────────────────────────────────────────────
emit(jal(x0, 0x40))     # JAL x0, +0x40 → jump to _start at 0x0040

# ── PC=0x0004: gap ───────────────────────────────────────────────────────────
emit(NOP)

# ── PC=0x0008: Timer ISR ─────────────────────────────────────────────────────
# Register use: t0 (scratch base), t1 (scratch), t2 (tick period)
# Clobbers t0/t1/t2. Main loop uses s2/s3/t3/t4 which are untouched.
assert pc() == 0x0008, f"ISR must be at 0x0008, currently at {pc():#06x}"

emit(lui (t0, CLINT_BASE >> 12))    # t0 = 0x10005000
emit(lw  (t1, t0, 0x0C))           # t1 = mtimecmp_lo (CLINT+0x0C)
emit(addi(t2, x0,  TICK))          # t2 = TICK_PERIOD
emit(add (t1, t1,  t2))            # t1 = new mtimecmp_lo
emit(sw  (t1, t0, 0x0C))           # re-arm: write new mtimecmp_lo to CLINT
emit(lui (t0, GPIO_BASE >> 12))    # t0 = 0x10002000
emit(lw  (t1, t0, 0x00))           # t1 = GPIO output register
emit(xori(t1, t1, 1))              # toggle bit 0 (LED)
emit(sw  (t1, t0, 0x00))           # write back GPIO
emit(MRET)                         # return from interrupt

# ── PC=0x0040: _start ────────────────────────────────────────────────────────
while pc() < 0x0040:
    emit(NOP)
assert pc() == 0x0040, f"_start must be at 0x0040, currently at {pc():#06x}"

# Configure GPIO: all outputs, initial output = 0
emit(lui (t0, GPIO_BASE >> 12))    # t0 = GPIO_BASE
emit(addi(t1, x0, -1))            # t1 = 0xFFFF... lower 16 bits = all-output
emit(sw  (t1, t0, 0x04))          # GPIO_DIR = 0xFFFF
emit(addi(t1, x0, 0))
emit(sw  (t1, t0, 0x00))          # GPIO_OUT = 0 (LED off)

# Set mtvec = 0x0008 (direct mode — all traps go to 0x0008)
emit(addi(t1, x0, 0x08))
emit(csrrw(x0, CSR_MTVEC, t1))

# Cache UART base in s2 before enabling interrupts
emit(lui(s2, UART_BASE >> 12))     # s2 = 0x10001000 (stable across ISR calls)

# Arm first timer tick via CLINT: mtimecmp = {0, TICK}
# Write HI first (safe: timer fires when mtime >= mtimecmp; setting hi=0 then lo=TICK
# would cause a spurious interrupt since {0,0} <= mtime=0. Avoid by writing lo first
# then hi, with mtimecmp_wr only on writes to these regs.
# CLINT triggers mtimecmp_wr_o on every write to 0x0C or 0x10.
# To avoid a spurious fire: set lo = TICK first, then hi = 0 (lo is already > 0).
emit(lui (t0, CLINT_BASE >> 12))
emit(addi(t1, x0, TICK))
emit(sw  (t1, t0, 0x0C))          # CLINT_MTIMECMP_LO = TICK
emit(addi(t1, x0, 0))
emit(sw  (t1, t0, 0x10))          # CLINT_MTIMECMP_HI = 0

# Enable timer counter (TIMER_BASE + 0x10 = CTRL: [0]=enable [1]=irq_en)
emit(lui (t0, TIMER_BASE >> 12))   # t0 = TIMER_BASE
emit(addi(t1, x0, 3))             # enable + irq_en
emit(sw  (t1, t0, 0x10))          # TIMER_CTRL = 3

# Enable M-mode timer interrupt then globally enable interrupts
# (order: mie before mstatus.MIE to avoid spurious trap with unset handler)
emit(addi(t1, x0, 0x80))          # mie.MTIE = bit 7
emit(csrrw(x0, CSR_MIE, t1))
emit(addi(t1, x0, 0x8))           # mstatus.MIE = bit 3
emit(csrrw(x0, CSR_MSTATUS, t1))  # ← interrupts live from here

# ── Main loop: print "Hello, World!\r\n" forever ─────────────────────────────
# Registers: s2=UART_BASE (ISR-safe), s3=char (ISR-safe), t3/t4=poll scratch
HELLO = b"Hello, World!\r\n"
main_loop = pc()

for byte in HELLO:
    # Poll UART STATUS[2] (tx_full): spin while full
    wait_pc = pc()
    emit(lw  (t3, s2, 0x08))              # t3 = UART_STATUS
    emit(andi(t3, t3, 4))                 # isolate tx_full bit
    emit(bne (t3, x0, wait_pc - pc()))    # branch back if full
    emit(addi(s3, x0, byte))              # s3 = character (ISR-safe register)
    emit(sw  (s3, s2, 0x00))             # write TXDATA → start TX

emit(jal(x0, main_loop - pc()))           # loop forever

# ── Emit files ───────────────────────────────────────────────────────────────
import os
out_dir = os.path.dirname(os.path.abspath(__file__))

with open(os.path.join(out_dir, "firmware.hex"), "w") as f:
    for w in instrs:
        f.write(f"{w:08x}\n")

with open(os.path.join(out_dir, "firmware.dump"), "w") as f:
    for i, w in enumerate(instrs):
        f.write(f"0x{i*4:04x}: {w:08x}\n")

print(f"Firmware : {len(instrs)} words  ({len(instrs)*4} bytes)")
print(f"ISR      : 0x0008")
print(f"_start   : 0x0040")
print(f"main_loop: 0x{main_loop:04x}")
print(f"Output   : {out_dir}/firmware.hex")
