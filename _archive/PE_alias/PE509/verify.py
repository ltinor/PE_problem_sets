#!/usr/bin/env python3
"""Verify PE509: answer is 151725678"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '151725678'
if answer == expected:
    print(f"PE509: PASS (got {answer})")
else:
    print(f"PE509: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('10', '692'), ('100', '735494')]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    status = "OK" if ans == exp else "FAIL"
    print(f"  n={w}: got {ans} (expected {exp}) [{status}]")
