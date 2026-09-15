#!/usr/bin/env python3
"""Verify PE442 answer: E(10^18) = 1295552661530920149"""
import subprocess, sys

# Test PE answer
result = subprocess.run(['./std'], input='1000000000000000000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '1295552661530920149'
if answer == expected:
    print(f"PE442: PASS (got {answer})")
else:
    print(f"PE442: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

# Test known values
for n, expected_val in [(3, '3'), (200, '213'), (500000, '531563')]:
    result = subprocess.run(['./std'], input=str(n), capture_output=True, text=True)
    answer = result.stdout.strip()
    if answer == expected_val:
        print(f"  E({n}) = {answer} OK")
    else:
        print(f"  E({n}) = {answer} (expected {expected_val}) FAIL")
        sys.exit(1)
