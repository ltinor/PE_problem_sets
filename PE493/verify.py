#!/usr/bin/env python3
"""Verify PE493: answer is 6.458740616"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '6.458740616'
if answer == expected:
    print(f"PE493: PASS (got {answer})")
else:
    print(f"PE493: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('10 3 2 5', '1.833333333')]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    print(f"  {w}: got {ans} (expected {exp})")
