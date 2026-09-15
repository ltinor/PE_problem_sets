#!/usr/bin/env python3
"""Verify PE448 answer: S(99999999019) mod 999999017 = 106467648"""
import subprocess, sys

# Test PE answer
result = subprocess.run(['./std'], input='99999999019', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '106467648'
if answer == expected:
    print(f"PE448: PASS (got {answer})")
else:
    print(f"PE448: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

# Test given value: S(100) = 122726
result = subprocess.run(['./std'], input='100', capture_output=True, text=True)
answer = result.stdout.strip()
expected2 = '122726'
if answer == expected2:
    print(f"  S(100) = {answer} OK")
else:
    print(f"  S(100) = {answer} (expected {expected2}) FAIL")
    sys.exit(1)
