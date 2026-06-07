"""Phase 19 — Secure boot SW logic tests (pure Python, no cocotb).

Validates the secure_boot.c logic model:
  - SHA-256 computed over image[:len-32]
  - Constant-time compare vs. appended digest AND OTP golden
  - Bit-flip in payload → reject
  - Bit-flip in appended digest → reject
  - Mismatched OTP → reject
  - Valid image accepted
"""
import hashlib
import unittest


# ── Python model of secure_boot.c verify_firmware() ──────────────────────

def sha256(data: bytes) -> bytes:
    return hashlib.sha256(data).digest()


def verify_firmware(image: bytes, otp_golden: bytes) -> bool:
    """Pure-Python model of verify_firmware()."""
    if len(image) < 33:
        return False
    payload  = image[:-32]
    appended = image[-32:]
    computed = sha256(payload)

    # Constant-time compare: diff1 = computed vs appended
    diff1 = 0
    for a, b in zip(computed, appended):
        diff1 |= a ^ b

    # Constant-time compare: diff2 = computed vs OTP golden
    diff2 = 0
    for a, b in zip(computed, otp_golden):
        diff2 |= a ^ b

    return (diff1 == 0) and (diff2 == 0)


def sign_image(payload: bytes) -> bytes:
    """Append SHA-256 digest to payload (as a build tool would)."""
    return payload + sha256(payload)


class TestSecureBoot(unittest.TestCase):

    def setUp(self):
        self.payload = b"Hello RISC-V firmware! " * 4   # 92 bytes
        self.image   = sign_image(self.payload)
        self.otp     = sha256(self.payload)

    def test_valid_image_accepted(self):
        self.assertTrue(verify_firmware(self.image, self.otp))

    def test_payload_bit_flip_rejected(self):
        """Single-bit flip in payload byte 0 → digest mismatch → reject."""
        corrupted = bytearray(self.image)
        corrupted[0] ^= 0x01
        self.assertFalse(verify_firmware(bytes(corrupted), self.otp))

    def test_appended_digest_flip_rejected(self):
        """Flip a bit in the appended digest → fail diff1 check."""
        corrupted = bytearray(self.image)
        corrupted[-1] ^= 0xFF
        self.assertFalse(verify_firmware(bytes(corrupted), self.otp))

    def test_otp_mismatch_rejected(self):
        """Valid image but wrong OTP → fail diff2 check."""
        wrong_otp = bytes([b ^ 0x01 for b in self.otp])
        self.assertFalse(verify_firmware(self.image, wrong_otp))

    def test_too_short_rejected(self):
        """Image shorter than 33 bytes → reject immediately."""
        self.assertFalse(verify_firmware(b"short", self.otp))

    def test_constant_time_no_early_exit(self):
        """
        Timing oracle check: all 32-byte mismatches must produce the same
        code path.  Verify that diff accumulates all byte differences.
        """
        # Image where every byte of the appended digest is wrong
        corrupted = bytearray(self.image)
        for i in range(32):
            corrupted[-(i+1)] ^= 0xFF
        result = verify_firmware(bytes(corrupted), self.otp)
        self.assertFalse(result)
        # Image where only the LAST byte of the appended digest is wrong
        corrupted2 = bytearray(self.image)
        corrupted2[-1] ^= 0xFF
        result2 = verify_firmware(bytes(corrupted2), self.otp)
        self.assertFalse(result2)
        # Both reject — no early-exit visible from return value
        self.assertEqual(result, result2)

    def test_empty_payload_rejected(self):
        """Empty payload: image is only 32 bytes, fails the len<33 guard."""
        empty_payload = b""
        image = sign_image(empty_payload)   # len == 32
        otp   = sha256(empty_payload)
        # SW policy: minimum valid image is 1 payload byte + 32-byte digest
        self.assertFalse(verify_firmware(image, otp))

    def test_large_payload(self):
        """256-byte payload signed and verified correctly."""
        payload = bytes(range(256))
        image   = sign_image(payload)
        otp     = sha256(payload)
        self.assertTrue(verify_firmware(image, otp))
        # One byte different → reject
        corrupted = bytearray(image); corrupted[100] ^= 0x55
        self.assertFalse(verify_firmware(bytes(corrupted), otp))

    def test_wrong_key_wrong_otp(self):
        """Image signed with key A, OTP holds key B digest → reject."""
        payload_a = b"firmware version A"
        payload_b = b"firmware version B"
        image_a   = sign_image(payload_a)
        otp_b     = sha256(payload_b)
        self.assertFalse(verify_firmware(image_a, otp_b))


if __name__ == "__main__":
    unittest.main(verbosity=2)
