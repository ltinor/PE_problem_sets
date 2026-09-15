#!/usr/bin/env python3
"""Verify PE498: answer is 4722948372011400"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '4722948372011400'
if answer == expected:
    print(f"PE498: PASS (got {answer})")
else:
    print(f"PE498: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('3 5 100', '24'), ('5 10 10000', '5120')]  # 9*8*7*6*5=15120 mod 10000=5120
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    print(f"  {w}: got {ans} (expected {exp})")
