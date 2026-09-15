#!/usr/bin/env python3
"""Verify PE473 answer: sum of palindromic phigital ≤ 10^10 = 772566"""
import subprocess, sys

result = subprocess.run(['./std'], input='10000000000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '772566'
if answer == expected:
    print(f"PE473: PASS (got {answer})")
else:
    print(f"PE473: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

result = subprocess.run(['./std'], input='1000', capture_output=True, text=True)
ans = result.stdout.strip()
if ans == '4345':
    print(f"  sum(≤1000) = {ans} OK")
else:
    print(f"  sum(≤1000) = {ans} (expected 4345) FAIL")
    sys.exit(1)
