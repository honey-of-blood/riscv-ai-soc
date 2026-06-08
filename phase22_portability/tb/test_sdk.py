"""test_sdk.py — Phase 22: SDK example and BSP content checks."""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SDK  = ROOT / "phase22_portability" / "sdk"


def test_soc_h_base_addresses():
    """soc.h defines all required peripheral base addresses."""
    text = (SDK / "bsp" / "include" / "soc.h").read_text()
    required = {
        "UART_BASE":   "0x10001000",
        "GPIO_BASE":   "0x10002000",
        "TIMER_BASE":  "0x10003000",
        "SPI_BASE":    "0x10004000",
        "CLINT_BASE":  "0x10005000",
        "PLIC_BASE":   "0x10006000",
        "I2C_BASE":    "0x10007000",
        "ACCEL_BASE":  "0x50000000",
        "AES_BASE":    "0x50001000",
        "SHA256_BASE": "0x50002000",
    }
    for sym, addr in required.items():
        assert sym in text,  f"soc.h missing: {sym}"
        assert addr.lower().replace("0x", "") in text.lower(), \
            f"soc.h: {sym} does not contain address {addr}"


def test_bsp_register_macros():
    """soc.h defines REG32 read/write macros."""
    text = (SDK / "bsp" / "include" / "soc.h").read_text()
    assert "REG32_RD" in text,   "soc.h missing REG32_RD macro"
    assert "REG32_WR" in text,   "soc.h missing REG32_WR macro"
    assert "volatile" in text,   "soc.h REG32 macro not using volatile"
    assert "CSR_READ" in text,   "soc.h missing CSR_READ helper"
    assert "CSR_WRITE" in text,  "soc.h missing CSR_WRITE helper"


def test_hello_world_main():
    """hello_world/main.c calls uart_init, uses printf, returns 0."""
    text = (SDK / "examples" / "hello_world" / "main.c").read_text()
    assert "uart_init" in text,  "hello_world missing uart_init call"
    assert "printf" in text,     "hello_world missing printf"
    assert "return 0" in text,   "hello_world missing return 0"


def test_secure_ota_reject_path():
    """secure_ota/main.c has dual-digest comparison and reject path."""
    text = (SDK / "examples" / "secure_ota" / "main.c").read_text()
    assert "REJECT" in text,         "secure_ota missing REJECT output"
    assert "sha256_verify" in text,  "secure_ota missing sha256_verify call"
    assert "otp_golden_hash" in text,"secure_ota missing OTP golden hash"
    # Must have both match checks
    assert "match_rcvd" in text,     "secure_ota missing rcvd digest check"
    assert "match_otp" in text,      "secure_ota missing OTP check"


def test_mnist_uses_accelerator():
    """mnist_inference/main.c uses accel_matmul_int4 and reads cycle counter."""
    text = (SDK / "examples" / "mnist_inference" / "main.c").read_text()
    assert "accel_matmul_int4" in text, "mnist missing accel_matmul_int4"
    assert "mcycle" in text,            "mnist missing cycle counter"
    assert "predicted" in text,         "mnist missing argmax / predicted class"
