#!/usr/bin/env python3
"""Verify PE502: Counting Castles — answer is 1201932627"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '1201932627'
if answer == expected:
    print(f"PE502: PASS (got {answer})")
else:
    print(f"PE502: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [
    ('1 1', '0'),
    ('2 2', '3'),
    ('3 3', '10'),
]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    status = "OK" if ans == exp else "MISMATCH"
    print(f"  {w}: got {ans} (expected {exp}) [{status}]")
