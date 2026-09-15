#!/usr/bin/env python3
"""Verify PE500: answer is 35407281"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '35407281'
if answer == expected:
    print(f"PE500: PASS (got {answer})")
else:
    print(f"PE500: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('1', '2'), ('2', '6'), ('3', '24'), ('4', '120')]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    print(f"  K={w}: got {ans} (expected {exp})")
