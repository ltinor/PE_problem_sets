#!/usr/bin/env python3
"""Verify PE472 answer: Σf(N) for N≤10^12 last 8 digits = 1486642873"""
import subprocess, sys

result = subprocess.run(['./std'], input='1000000000000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '1486642873'
if answer == expected:
    print(f"PE472: PASS (got {answer})")
else:
    print(f"PE472: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('1', '1'), ('15', '9'), ('20', '6'), ('500', '16')]
for n, exp in tests:
    result = subprocess.run(['./std'], input=n, capture_output=True, text=True)
    ans = result.stdout.strip()
    state = "OK" if ans == exp else f"FAIL (expected {exp})"
    print(f"  f({n}) = {ans} {state}")
    if ans != exp: sys.exit(1)
