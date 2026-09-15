#!/usr/bin/env python3
"""Verify PE491: answer is 30531024"""
import subprocess, sys

# PE check
result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '30531024'
if answer == expected:
    print(f"PE491: PASS (got {answer})")
else:
    print(f"PE491: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

# Known checks
tests = [
    ('2', '0'),     # N=2: only number is 0? No. Actually 2-digit using digit 0 twice is just 00, but first digit can't be 0. So 0.
    ('4', '2'),     # N=4: 1001, 1100
    ('20', '30531024'),  # PE answer
]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    status = "PASS" if ans == exp else f"FAIL (got {ans}, expected {exp})"
    print(f"  N={w}: {status}")
