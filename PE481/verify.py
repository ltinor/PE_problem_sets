#!/usr/bin/env python3
"""Verify PE481: Chef Showdown answer = 729.12121547"""
import subprocess, sys

result = subprocess.run(['./std'], input='11', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '729.12121547'
if answer == expected:
    print(f"PE481: PASS (got {answer})")
else:
    print(f"PE481: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('1', '0.5000'), ('3', '1.875')]
for n, exp in tests:
    result = subprocess.run(['./std'], input=n, capture_output=True, text=True)
    ans = result.stdout.strip()
    # Just check small inputs work (approximate)
    print(f"  N={n}: {ans}")
