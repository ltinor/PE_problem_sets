#!/usr/bin/env python3
"""Verify PE475: f(600) mod 1e9+7 = 75780067"""
import subprocess, sys

result = subprocess.run(['./std'], input='600', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '75780067'
if answer == expected:
    print(f"PE475: PASS (got {answer})")
else:
    print(f"PE475: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('12', '576'), ('24', '509089824')]
for n, exp in tests:
    result = subprocess.run(['./std'], input=n, capture_output=True, text=True)
    ans = result.stdout.strip()
    state = "OK" if ans == exp else f"FAIL (expected {exp})"
    print(f"  f({n}) = {ans} {state}")
    if ans != exp: sys.exit(1)
