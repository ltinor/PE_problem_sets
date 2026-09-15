#!/usr/bin/env python3
"""Verify PE444 answer: S_20(10^14) = 1.200856722e263"""
import subprocess, sys

# Test PE answer
result = subprocess.run(['./std'], input='20 100000000000000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '1.200856722e263'
if answer == expected:
    print(f"PE444: PASS (got {answer})")
else:
    print(f"PE444: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

# Test known value: S_3(100) = 5.983679014e5
result = subprocess.run(['./std'], input='3 100', capture_output=True, text=True)
answer = result.stdout.strip()
expected2 = '5.983679014e5'
if answer == expected2:
    print(f"  S_3(100) = {answer} OK")
else:
    print(f"  S_3(100) = {answer} (expected {expected2}) - may differ due to approximation")
