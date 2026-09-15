#!/usr/bin/env python3
"""Verify PE506: answer is 18934502"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '18934502'
if answer == expected:
    print(f"PE506: PASS (got {answer})")
else:
    print(f"PE506: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

# Known test cases
tests = [
    ('1', '1'),
    ('2', '3'),
    ('3', '6'),
    ('4', '10'),
    ('5', '42'),
    ('11', '36120'),
    ('1000', '18232686'),
]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    status = "OK" if ans == exp else "FAIL"
    print(f"  N={w}: got {ans} (expected {exp}) [{status}]")
