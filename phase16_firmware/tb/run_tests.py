"""
Phase 16 test runner.

Runs the XMODEM protocol tests (pure Python, no simulator required).
Usage:
    python run_tests.py          # from repo root or this directory
    python -m pytest test_xmodem.py -v   # alternative
"""

import sys
import os
import unittest

def main():
    loader  = unittest.TestLoader()
    tb_dir  = os.path.dirname(os.path.abspath(__file__))
    suite   = loader.discover(tb_dir, pattern="test_*.py")
    runner  = unittest.TextTestRunner(verbosity=2, stream=sys.stdout)
    result  = runner.run(suite)

    total  = result.testsRun
    failed = len(result.failures) + len(result.errors)
    passed = total - failed

    print(f"\n** TESTS={total} PASS={passed} FAIL={failed} SKIP={len(result.skipped)} **")
    sys.exit(0 if failed == 0 else 1)

if __name__ == "__main__":
    main()
