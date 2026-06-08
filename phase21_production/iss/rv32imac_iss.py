"""RV32IMAC Instruction Set Simulator — golden reference model for Phase 21.

Implements RV32I + M-extension arithmetic faithfully, including:
  - 32 registers (x0 hardwired 0), PC
  - All branch/jump types with correct signed/unsigned comparisons
  - Byte-enable loads and stores
  - M-extension: MUL/MULH/MULHSU/MULHU/DIV/DIVU/REM/REMU with spec-correct
    division-by-zero and overflow semantics

Usage:
    from iss.rv32imac_iss import RV32IMISS

    iss = RV32IMISS()
    iss.load(instructions)          # list of 32-bit words starting at PC=0
    iss.mem.update(data_mem_init)   # optional pre-init data memory
    regs = iss.run_n(n)             # execute n steps, return u32 register list
"""


def _s32(x):
    x = x & 0xFFFFFFFF
    return x - (1 << 32) if x >= (1 << 31) else x


def _u32(x):
    return x & 0xFFFFFFFF


class RV32IMISS:
    def __init__(self):
        self.regs = [0] * 32  # u32
        self.pc   = 0          # byte address, u32
        self.mem  = {}         # word_addr (byte_addr>>2) -> u32

    # ── Register accessors ────────────────────────────────────────────────────

    def _rd(self, r):
        return self.regs[r]

    def _wr(self, r, v):
        if r:
            self.regs[r] = _u32(v)

    # ── Immediate decoders ────────────────────────────────────────────────────

    @staticmethod
    def _imm_i(w):
        x = (w >> 20) & 0xFFF
        return x - (1 << 12) if x >= (1 << 11) else x

    @staticmethod
    def _imm_s(w):
        x = ((w >> 25) & 0x7F) << 5 | ((w >> 7) & 0x1F)
        return x - (1 << 12) if x >= (1 << 11) else x

    @staticmethod
    def _imm_b(w):
        x = (((w >> 31) & 1) << 12 | ((w >> 7) & 1) << 11 |
             ((w >> 25) & 0x3F) << 5 | ((w >> 8) & 0xF) << 1)
        return x - (1 << 13) if x >= (1 << 12) else x

    @staticmethod
    def _imm_j(w):
        x = (((w >> 31) & 1) << 20 | ((w >> 12) & 0xFF) << 12 |
             ((w >> 20) & 1) << 11 | ((w >> 21) & 0x3FF) << 1)
        return x - (1 << 21) if x >= (1 << 20) else x

    # ── Memory helpers ────────────────────────────────────────────────────────

    def _mem_load(self, addr, f3):
        boff = addr & 3
        w    = self.mem.get(addr >> 2, 0)
        if f3 == 0:   # LB
            b = (w >> (8 * boff)) & 0xFF
            return b - 256 if b >= 128 else b
        elif f3 == 1:  # LH
            h = (w >> (8 * (boff & 2))) & 0xFFFF
            return h - 65536 if h >= 32768 else h
        elif f3 == 2:  # LW
            return w
        elif f3 == 4:  # LBU
            return (w >> (8 * boff)) & 0xFF
        elif f3 == 5:  # LHU
            return (w >> (8 * (boff & 2))) & 0xFFFF
        return 0

    def _mem_store(self, addr, data, f3):
        wi   = addr >> 2
        boff = addr & 3
        w    = self.mem.get(wi, 0)
        if f3 == 0:    # SB
            m = 0xFF << (8 * boff)
            w = (w & ~m) | ((data & 0xFF) << (8 * boff))
        elif f3 == 1:  # SH
            m = 0xFFFF << (8 * (boff & 2))
            w = (w & ~m) | ((data & 0xFFFF) << (8 * (boff & 2)))
        elif f3 == 2:  # SW
            w = data
        self.mem[wi] = w & 0xFFFFFFFF

    # ── Execution ─────────────────────────────────────────────────────────────

    def step(self):
        """Execute one instruction. Returns False when EBREAK encountered."""
        pc  = self.pc
        w   = self.mem.get(pc >> 2, 0)

        opc = w & 0x7F
        rd  = (w >> 7)  & 0x1F
        f3  = (w >> 12) & 0x7
        rs1 = (w >> 15) & 0x1F
        rs2 = (w >> 20) & 0x1F
        f7  = (w >> 25) & 0x7F

        a   = self._rd(rs1)  # u32
        b   = self._rd(rs2)  # u32
        ai  = _s32(a)
        bi  = _s32(b)
        ii  = self._imm_i(w)
        npc = _u32(pc + 4)

        if opc == 0x37:    # LUI
            self._wr(rd, w & 0xFFFFF000)

        elif opc == 0x17:  # AUIPC
            self._wr(rd, _u32(pc + (w & 0xFFFFF000)))

        elif opc == 0x6F:  # JAL
            self._wr(rd, npc)
            npc = _u32(pc + self._imm_j(w))

        elif opc == 0x67:  # JALR
            self._wr(rd, npc)
            npc = _u32(a + ii) & ~1

        elif opc == 0x63:  # Branch
            ib = self._imm_b(w)
            taken = {0: a == b, 1: a != b, 4: ai < bi,
                     5: ai >= bi, 6: a < b, 7: a >= b}.get(f3, False)
            if taken:
                npc = _u32(pc + ib)

        elif opc == 0x03:  # Load
            self._wr(rd, self._mem_load(_u32(a + ii), f3))

        elif opc == 0x23:  # Store
            self._mem_store(_u32(a + self._imm_s(w)), b, f3)

        elif opc == 0x13:  # OP-IMM
            shamt = ii & 0x1F
            v = {
                0: _s32(a) + ii,
                1: a << shamt,
                2: 1 if ai < ii else 0,
                3: 1 if a < _u32(ii) else 0,
                4: a ^ _u32(ii),
                5: ((_s32(a) >> shamt) if (ii >> 10) & 1 else (a >> shamt)),
                6: a | _u32(ii),
                7: a & _u32(ii),
            }.get(f3, 0)
            self._wr(rd, v)

        elif opc == 0x33:  # OP or M-ext
            if f7 == 0x01:  # M-extension
                if f3 == 0:   # MUL
                    v = (ai * bi) & 0xFFFFFFFF
                elif f3 == 1: # MULH (signed × signed, upper 32)
                    v = ((ai * bi) >> 32) & 0xFFFFFFFF
                elif f3 == 2: # MULHSU (signed × unsigned, upper 32)
                    v = ((ai * a) >> 32) & 0xFFFFFFFF
                elif f3 == 3: # MULHU (unsigned × unsigned, upper 32)
                    v = ((a * b) >> 32) & 0xFFFFFFFF
                elif f3 == 4: # DIV (signed, truncate-toward-zero)
                    if b == 0:
                        v = 0xFFFFFFFF
                    elif ai == -(1 << 31) and bi == -1:
                        v = -(1 << 31)
                    else:
                        v = int(ai / bi)
                elif f3 == 5: # DIVU
                    v = (a // b) if b else 0xFFFFFFFF
                elif f3 == 6: # REM (signed)
                    if b == 0:
                        v = ai
                    elif ai == -(1 << 31) and bi == -1:
                        v = 0
                    else:
                        q = int(ai / bi)
                        v = ai - q * bi
                elif f3 == 7: # REMU
                    v = (a % b) if b else a
                else:
                    v = 0
                self._wr(rd, v)
            else:            # RV32I R-type
                shamt = b & 0x1F
                v = {
                    (0, 0x00): ai + bi,
                    (0, 0x20): ai - bi,
                    (1, 0x00): a << shamt,
                    (2, 0x00): 1 if ai < bi else 0,
                    (3, 0x00): 1 if a < b else 0,
                    (4, 0x00): a ^ b,
                    (5, 0x00): a >> shamt,
                    (5, 0x20): ai >> shamt,
                    (6, 0x00): a | b,
                    (7, 0x00): a & b,
                }.get((f3, f7), 0)
                self._wr(rd, v)

        elif opc == 0x73:  # SYSTEM
            if w == 0x00100073:  # EBREAK
                return False
            # CSR/ECALL: not modelled; skip

        self.pc = npc
        return True

    # ── Bulk helpers ─────────────────────────────────────────────────────────

    def load(self, instrs, base_addr=0):
        """Load instruction list into memory starting at base_addr."""
        for i, instr in enumerate(instrs):
            self.mem[(base_addr >> 2) + i] = _u32(instr)

    def run_n(self, n):
        """Execute exactly n instructions, return register list (u32)."""
        for _ in range(n):
            if not self.step():
                break
        return list(self.regs)

    def run_until_ebreak(self, max_steps=100_000):
        """Run until EBREAK or max_steps reached."""
        for _ in range(max_steps):
            if not self.step():
                break
        return list(self.regs)
