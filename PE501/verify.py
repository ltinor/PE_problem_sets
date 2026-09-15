#!/usr/bin/env python3
"""Verify PE501: Eight Divisors — answer is 197912312715"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '197912312715'
if answer == expected:
    print(f"PE501: PASS (got {answer})")
else:
    print(f"PE501: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [
    ('10', '0'),
    ('24', '1'),
    ('30', '2'),
    ('100', '10'),
    ('1000', '111'),
]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    status = "OK" if ans == exp else "MISMATCH"
    print(f"  N={w}: got {ans} (expected {exp}) [{status}]")
