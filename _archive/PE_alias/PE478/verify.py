#!/usr/bin/env python3
"""Verify PE478: E(10^7) mod 11^8 = 59510337"""
import subprocess, sys

result = subprocess.run(['./std'], input='10000000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '59510337'
if answer == expected:
    print(f"PE478: PASS (got {answer})")
else:
    print(f"PE478: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [
    ('1', '103'),
    ('2', '520447'),
    ('10', '82608406'),
    ('500', '13801403'),
]
for n, exp in tests:
    result = subprocess.run(['./std'], input=n, capture_output=True, text=True)
    ans = result.stdout.strip()
    state = "OK" if ans == exp else f"FAIL (expected {exp})"
    print(f"  E({n}) = {ans} {state}")
    if ans != exp: sys.exit(1)
