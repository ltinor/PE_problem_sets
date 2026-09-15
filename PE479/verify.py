#!/usr/bin/env python3
"""Verify PE479: S(10^6) mod 1e9+7 = 19154179538"""
import subprocess, sys

result = subprocess.run(['./std'], input='1000000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '19154179538'
if answer == expected:
    print(f"PE479: PASS (got {answer})")
else:
    print(f"PE479: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('4', '51160')]
for n, exp in tests:
    result = subprocess.run(['./std'], input=n, capture_output=True, text=True)
    ans = result.stdout.strip()
    state = "OK" if ans == exp else f"FAIL (expected {exp})"
    print(f"  S({n}) = {ans} {state}")
    if ans != exp: sys.exit(1)
