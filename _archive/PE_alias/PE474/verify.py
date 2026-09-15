#!/usr/bin/env python3
"""Verify PE474: F(10^6!, 65432) mod (10^16+61) = 9690646731515010"""
import subprocess, sys

result = subprocess.run(['./std'], input='1000000 65432', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '9690646731515010'
if answer == expected:
    print(f"PE474: PASS (got {answer})")
else:
    print(f"PE474: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('12 12', '11'), ('50 123', '17888'), ('84 4', '3')]
for inp, exp in tests:
    result = subprocess.run(['./std'], input=inp, capture_output=True, text=True)
    ans = result.stdout.strip()
    state = "OK" if ans == exp else f"FAIL (expected {exp})"
    print(f"  F({inp}) = {ans} {state}")
    if ans != exp: sys.exit(1)
