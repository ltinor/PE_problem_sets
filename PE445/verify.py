#!/usr/bin/env python3
"""Verify PE445 answer: sum R(C(10^7, k)) mod 1e9+7 = 659104042"""
import subprocess, sys

# Test PE answer
result = subprocess.run(['./std'], input='PE', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '659104042'
if answer == expected:
    print(f"PE445: PASS (got {answer})")
else:
    print(f"PE445: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

# Test R(n) for known values
test_cases = [
    ('2', '1'),
    ('6', '6'),
    ('12', '8'),
    ('30', '42'),
]
for n, expected_val in test_cases:
    result = subprocess.run(['./std'], input=n, capture_output=True, text=True)
    answer = result.stdout.strip()
    if answer == expected_val:
        print(f"  R({n}) = {answer} OK")
    else:
        print(f"  R({n}) = {answer} (expected {expected_val}) FAIL")
        sys.exit(1)

# Test R(100000) for the known congruence
print("Testing R for factorized values...")
