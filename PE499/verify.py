#!/usr/bin/env python3
"""Verify PE499: answer is 0.00097874"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '0.00097874'
if answer == expected:
    print(f"PE499: PASS (got {answer})")
else:
    print(f"PE499: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('3 1 10', '0.50000000')]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    print(f"  {w}: got {ans} (expected {exp})")
