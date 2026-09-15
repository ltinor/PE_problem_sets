#!/usr/bin/env python3
"""Verify PE494: answer is 28800671344"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '28800671344'
if answer == expected:
    print(f"PE494: PASS (got {answer})")
else:
    print(f"PE494: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('1 20', '20'), ('2 50', '50')]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    print(f"  {w}: got {ans} (expected {exp})")
