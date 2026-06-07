"""Phase 19 — PMP configuration SW tests (pure Python, no cocotb).

Validates the pmp_config.c logic model:
  - NAPOT encoding formula
  - Permission bitmask values
  - Address range coverage
  - Default-deny catch-all region
"""
import unittest


# ── Python model of pmp_config.c ─────────────────────────────────────────

PMP_R     = 0x01
PMP_W     = 0x02
PMP_X     = 0x04
PMP_NAPOT = 0x18
PMP_TOR   = 0x08


def pmp_napot(base: int, size: int) -> int:
    """NAPOT pmpaddr encoding: (base >> 2) | ((size/2 - 1) >> 2)."""
    return (base >> 2) | ((size // 2 - 1) >> 2)


def napot_range(pmpaddr: int):
    """Decode a NAPOT pmpaddr → (base, size) pair."""
    # Find the lowest clear bit in pmpaddr (after masking out the mode bits)
    # NAPOT encodes size as the trailing string of 1s + 1
    trailing = pmpaddr & (~pmpaddr + 1)  # lowest set bit = 2^k
    # Actually: find trailing ones in pmpaddr
    # pmpaddr = base/4 | (size/8 - 1) → trailing 1-bits encode size
    # Easier: size = 2 * (trailing_ones_value + 1) * 4
    tmp = pmpaddr
    k = 0
    while tmp & 1:
        k += 1; tmp >>= 1
    size = (1 << k) * 8  # 2^(k+2) bytes
    base = (pmpaddr & ~((1 << k) - 1)) << 2
    return base, size


def setup_isolation():
    """Model of pmp_setup_isolation() — returns (pmpaddr[0..3], pmpcfg0)."""
    pmpaddr = [0] * 4
    pmpaddr[0] = pmp_napot(0x00000000, 0x10000000)   # ROM 256 MiB
    pmpaddr[1] = pmp_napot(0x20000000, 0x00040000)   # SRAM 256 KiB
    pmpaddr[2] = pmp_napot(0x40000000, 0x10000000)   # MMIO 256 MiB
    pmpaddr[3] = 0xFFFFFFFF                            # catch-all TOR

    pmpcfg0 = (
        (PMP_TOR                      << 24) |   # region 3: catch-all no perms
        ((PMP_R | PMP_W | PMP_NAPOT)  << 16) |   # region 2: MMIO RW
        ((PMP_R | PMP_W | PMP_X | PMP_NAPOT) << 8) | # region 1: SRAM RWX
        ((PMP_R | PMP_X | PMP_NAPOT)  <<  0)     # region 0: ROM RX
    )
    return pmpaddr, pmpcfg0


class TestPmpConfig(unittest.TestCase):

    def setUp(self):
        self.pmpaddr, self.pmpcfg0 = setup_isolation()

    # ── NAPOT encoding ────────────────────────────────────────────────────

    def test_napot_rom_encoding(self):
        """ROM NAPOT: base=0, size=256MiB → pmpaddr = 0x1FFFFFF."""
        expected = pmp_napot(0x00000000, 0x10000000)
        self.assertEqual(self.pmpaddr[0], expected)
        self.assertEqual(expected, 0x1FFFFFF)

    def test_napot_sram_encoding(self):
        """SRAM NAPOT: base=0x20000000, size=256KiB."""
        expected = pmp_napot(0x20000000, 0x00040000)
        self.assertEqual(self.pmpaddr[1], expected)

    def test_napot_mmio_encoding(self):
        """MMIO NAPOT: base=0x40000000, size=256MiB."""
        expected = pmp_napot(0x40000000, 0x10000000)
        self.assertEqual(self.pmpaddr[2], expected)

    def test_catchall_tor(self):
        """Catch-all TOR region: pmpaddr3 = 0xFFFFFFFF."""
        self.assertEqual(self.pmpaddr[3], 0xFFFFFFFF)

    # ── Permission bits ───────────────────────────────────────────────────

    def test_rom_permissions(self):
        """ROM region: R=1, W=0, X=1, mode=NAPOT."""
        cfg0 = self.pmpcfg0 & 0xFF
        self.assertTrue(cfg0 & PMP_R,   "ROM: R must be set")
        self.assertFalse(cfg0 & PMP_W,  "ROM: W must be clear")
        self.assertTrue(cfg0 & PMP_X,   "ROM: X must be set")
        self.assertEqual(cfg0 & PMP_NAPOT, PMP_NAPOT, "ROM: mode must be NAPOT")

    def test_sram_permissions(self):
        """SRAM region: R=1, W=1, X=1, mode=NAPOT."""
        cfg1 = (self.pmpcfg0 >> 8) & 0xFF
        self.assertTrue(cfg1 & PMP_R)
        self.assertTrue(cfg1 & PMP_W)
        self.assertTrue(cfg1 & PMP_X)
        self.assertEqual(cfg1 & PMP_NAPOT, PMP_NAPOT)

    def test_mmio_permissions(self):
        """MMIO region: R=1, W=1, X=0, mode=NAPOT."""
        cfg2 = (self.pmpcfg0 >> 16) & 0xFF
        self.assertTrue(cfg2 & PMP_R)
        self.assertTrue(cfg2 & PMP_W)
        self.assertFalse(cfg2 & PMP_X, "MMIO: X must be clear (no execute)")
        self.assertEqual(cfg2 & PMP_NAPOT, PMP_NAPOT)

    def test_catchall_permissions(self):
        """Catch-all region: R=0, W=0, X=0 → default deny."""
        cfg3 = (self.pmpcfg0 >> 24) & 0xFF
        self.assertFalse(cfg3 & PMP_R, "catch-all: R must be 0")
        self.assertFalse(cfg3 & PMP_W, "catch-all: W must be 0")
        self.assertFalse(cfg3 & PMP_X, "catch-all: X must be 0")
        self.assertEqual(cfg3 & 0x18, PMP_TOR, "catch-all: mode must be TOR")

    # ── Address range coverage ────────────────────────────────────────────

    def test_rom_covers_0x0000_0000(self):
        """ROM region must cover address 0x0000_0000."""
        base, size = napot_range(self.pmpaddr[0])
        self.assertLessEqual(base, 0x00000000)
        self.assertGreater(base + size, 0x00000000)

    def test_sram_covers_0x2000_0000(self):
        """SRAM region must cover 0x2000_0000."""
        base, size = napot_range(self.pmpaddr[1])
        self.assertLessEqual(base, 0x20000000)
        self.assertGreater(base + size, 0x20000000)

    def test_mmio_covers_0x4000_0000(self):
        """MMIO region must cover 0x4000_0000."""
        base, size = napot_range(self.pmpaddr[2])
        self.assertLessEqual(base, 0x40000000)
        self.assertGreater(base + size, 0x40000000)

    def test_rom_does_not_cover_mmio(self):
        """ROM region must not extend into MMIO space."""
        base, size = napot_range(self.pmpaddr[0])
        self.assertLess(base + size, 0x40000000,
                        "ROM NAPOT must not spill into MMIO region")

    def test_napot_size_power_of_two(self):
        """NAPOT-encoded sizes must be powers of two."""
        for i in range(3):
            _, size = napot_range(self.pmpaddr[i])
            self.assertTrue((size & (size - 1)) == 0,
                            f"region {i}: size {size:#x} is not a power of two")


if __name__ == "__main__":
    unittest.main(verbosity=2)
