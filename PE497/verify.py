#!/usr/bin/env python3
"""Verify PE497: answer is 684901360"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '684901360'
if answer == expected:
    print(f"PE497: PASS (got {answer})")
else:
    print(f"PE497: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('1', '2'), ('2', '21')]  # E(2) ≈ 21 via value iteration
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    print(f"  n={w}: got {ans} (expected {exp})")
