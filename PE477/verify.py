#!/usr/bin/env python3
"""Verify PE477: F(10^8) = 25044905874565165"""
import subprocess, sys

result = subprocess.run(['./std'], input='100000000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '25044905874565165'
if answer == expected:
    print(f"PE477: PASS (got {answer})")
else:
    print(f"PE477: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [
    ('2', '45'),
    ('4', '4284990'),
    ('100', '26365463243'),
    ('10000', '2495838522951'),
]
for n, exp in tests:
    result = subprocess.run(['./std'], input=n, capture_output=True, text=True)
    ans = result.stdout.strip()
    state = "OK" if ans == exp else f"FAIL (expected {exp})"
    print(f"  F({n}) = {ans} {state}")
    if ans != exp: sys.exit(1)
