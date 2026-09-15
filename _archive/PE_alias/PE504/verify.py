#!/usr/bin/env python3
"""Verify PE504: Square on the Inside — answer is 694687"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '694687'
if answer == expected:
    print(f"PE504: PASS (got {answer})")
else:
    print(f"PE504: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [
    ('1', '1'),
    ('2', '48'),
]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    status = "OK" if ans == exp else "MISMATCH"
    print(f"  N={w}: got {ans} (expected {exp}) [{status}]")
