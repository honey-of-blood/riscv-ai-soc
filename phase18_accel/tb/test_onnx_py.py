#!/usr/bin/env python3
"""Pure-Python tests for onnx_to_c.py helper functions.

Tests the quantisation and packing helpers without requiring a real ONNX
model (the ONNX-loading path is not exercised here).  Runs with plain Python.
"""
import sys
import os
import unittest

# Add tools directory to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "tools"))
from onnx_to_c import clamp_int4, pack_row4, quantise_to_int4, pack_weight_tile


class TestClampInt4(unittest.TestCase):
    def test_in_range(self):
        for v in range(-8, 8):
            self.assertEqual(clamp_int4(v), v)

    def test_clip_high(self):
        self.assertEqual(clamp_int4(8),  7)
        self.assertEqual(clamp_int4(100), 7)

    def test_clip_low(self):
        self.assertEqual(clamp_int4(-9),   -8)
        self.assertEqual(clamp_int4(-100), -8)


class TestPackRow4(unittest.TestCase):
    def test_positive_values(self):
        # w0=1, w1=2, w2=3, w3=4
        result = pack_row4(1, 2, 3, 4)
        self.assertEqual(result & 0xF,        1)  # bits[3:0]
        self.assertEqual((result >> 4) & 0xF, 2)  # bits[7:4]
        self.assertEqual((result >> 8) & 0xF, 3)  # bits[11:8]
        self.assertEqual((result >> 12) & 0xF, 4) # bits[15:12]

    def test_negative_two_complement(self):
        # -1 = 0xF in 4-bit 2's complement
        result = pack_row4(-1, -1, -1, -1)
        self.assertEqual(result, 0xFFFF)

    def test_mixed(self):
        result = pack_row4(1, 0, 0, 0)
        self.assertEqual(result, 0x0001)
        result = pack_row4(0, 1, 0, 0)
        self.assertEqual(result, 0x0010)


class TestQuantiseInt4(unittest.TestCase):
    def _make_arr(self, data):
        """Create a simple object with flatten() method."""
        class Arr:
            def __init__(self, d):
                self._d = d
            def flatten(self):
                return self._d
        return Arr(data)

    def test_identity_scale(self):
        arr = self._make_arr([1.0, 2.0, 3.0, -3.0])
        result = quantise_to_int4(arr, scale=1.0)
        self.assertEqual(result, [1, 2, 3, -3])

    def test_half_scale(self):
        arr = self._make_arr([2.0, 4.0, -4.0])
        result = quantise_to_int4(arr, scale=2.0)
        self.assertEqual(result, [1, 2, -2])

    def test_clamps_to_range(self):
        arr = self._make_arr([100.0, -100.0])
        result = quantise_to_int4(arr, scale=1.0)
        self.assertEqual(result[0], 7)
        self.assertEqual(result[1], -8)


class TestPackWeightTile(unittest.TestCase):
    def test_identity_tile(self):
        """4×1 tile: identity weights → packed rows."""
        # OC=4, patch_elems=1
        # W[0][0]=1, W[1][0]=0, W[2][0]=0, W[3][0]=0
        weights_int4 = [1, 0, 0, 0]  # [OC=4][patch=1]
        packed = pack_weight_tile(weights_int4, OC=4, patch_elems=1, tile_n=4)
        # One tile, one patch element → one word
        self.assertEqual(len(packed), 1)
        # Word: pack_row4(1, 0, 0, 0) = 0x0001
        self.assertEqual(packed[0], 0x0001)

    def test_multiple_tiles(self):
        """OC=8, tile_n=4 → 2 tiles."""
        weights_int4 = [1]*8   # all ones
        packed = pack_weight_tile(weights_int4, OC=8, patch_elems=1, tile_n=4)
        self.assertEqual(len(packed), 2)


if __name__ == "__main__":
    unittest.main(verbosity=2)
