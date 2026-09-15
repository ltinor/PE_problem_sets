#!/usr/bin/env python3
"""Verify PE446 answer: F(10^7) mod 1e9+7 = 907803852"""
import subprocess, sys

# Test PE answer
result = subprocess.run(['./std'], input='10000000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '907803852'
if answer == expected:
    print(f"PE446: PASS (got {answer})")
else:
    print(f"PE446: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

# Test given value: F(1024) = 77532377300600
result = subprocess.run(['./std'], input='1024', capture_output=True, text=True)
answer = result.stdout.strip()
expected2 = '77532377300600'
if answer == expected2:
    print(f"  F(1024) = {answer} OK")
else:
    print(f"  F(1024) = {answer} (expected {expected2}) FAIL")
    sys.exit(1)
