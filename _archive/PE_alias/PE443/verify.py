#!/usr/bin/env python3
"""Verify PE443 answer: g(10^15) = 2744233049300770"""
import subprocess, sys

# Test PE answer
result = subprocess.run(['./std'], input='1000000000000000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '2744233049300770'
if answer == expected:
    print(f"PE443: PASS (got {answer})")
else:
    print(f"PE443: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

# Test known values
for n, expected_val in [(20, '60'), (1000, '2524'), (1000000, '2624152')]:
    result = subprocess.run(['./std'], input=str(n), capture_output=True, text=True)
    answer = result.stdout.strip()
    if answer == expected_val:
        print(f"  g({n}) = {answer} OK")
    else:
        print(f"  g({n}) = {answer} (expected {expected_val}) FAIL")
        sys.exit(1)
