#!/usr/bin/env python3
"""Verify PE508: answer is 891874596"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '891874596'
if answer == expected:
    print(f"PE508: PASS (got {answer})")
else:
    print(f"PE508: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('500', '10795060')]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    status = "OK" if ans == exp else "FAIL"
    print(f"  L={w}: got {ans} (expected {exp}) [{status}]")
