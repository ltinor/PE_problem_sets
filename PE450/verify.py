#!/usr/bin/env python3
"""Verify PE450 answer: T(10^6) = 583333163984220726"""
import subprocess, sys

# Test PE answer
result = subprocess.run(['./std'], input='1000000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '583333163984220726'
if answer == expected:
    print(f"PE450: PASS (got {answer})")
else:
    print(f"PE450: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

# Test known values
tests = [
    ('3', '10'),
    ('10', '524'),
    ('100', '580442'),
    ('1000', '583108600'),
]
for n, exp in tests:
    result = subprocess.run(['./std'], input=n, capture_output=True, text=True)
    answer = result.stdout.strip()
    if answer == exp:
        print(f"  T({n}) = {answer} OK")
    else:
        print(f"  T({n}) = {answer} (expected {exp}) FAIL")
        sys.exit(1)
