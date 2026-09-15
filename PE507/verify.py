#!/usr/bin/env python3
"""Verify PE507: answer is 316558047002627160"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '316558047002627160'
if answer == expected:
    print(f"PE507: PASS (got {answer})")
else:
    print(f"PE507: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

# Known test cases
tests = [
    ('1', '32'),
]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    status = "OK" if ans == exp else "FAIL"
    print(f"  N={w}: got {ans} (expected {exp}) [{status}]")
