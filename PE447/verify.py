#!/usr/bin/env python3
"""Verify PE447 answer: F(10^14) mod 1e9+7 = 530553372"""
import subprocess, sys

# Test PE answer
result = subprocess.run(['./std'], input='100000000000000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '530553372'
if answer == expected:
    print(f"PE447: PASS (got {answer})")
else:
    print(f"PE447: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

# Test given value: F(10^7) ≡ 638042271 (mod 1e9+7)
result = subprocess.run(['./std'], input='10000000', capture_output=True, text=True)
answer = result.stdout.strip()
expected2 = '638042271'
if answer == expected2:
    print(f"  F(10^7) mod 1e9+7 = {answer} OK")
else:
    print(f"  F(10^7) = {answer} (expected {expected2}) FAIL")
    sys.exit(1)
