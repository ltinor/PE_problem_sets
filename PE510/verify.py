#!/usr/bin/env python3
"""Verify PE510: answer is 315306518862563689"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '315306518862563689'
if answer == expected:
    print(f"PE510: PASS (got {answer})")
else:
    print(f"PE510: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('5', '9'), ('100', '3072')]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    status = "OK" if ans == exp else "FAIL"
    print(f"  n={w}: got {ans} (expected {exp}) [{status}]")
