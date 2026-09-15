#!/usr/bin/env python3
"""Verify PE476: S(1803) = 110242.87794"""
import subprocess, sys

result = subprocess.run(['./std'], input='1803', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '110242.87794'
if answer == expected:
    print(f"PE476: PASS (got {answer})")
else:
    print(f"PE476: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('2', '0.31998'), ('5', '1.25899')]
for n, exp in tests:
    result = subprocess.run(['./std'], input=n, capture_output=True, text=True)
    ans = result.stdout.strip()
    state = "OK" if ans == exp else f"FAIL (expected {exp})"
    print(f"  S({n}) = {ans} {state}")
    if ans != exp: sys.exit(1)
