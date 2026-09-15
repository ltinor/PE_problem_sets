#!/usr/bin/env python3
"""Verify PE492: answer is 2425869629239289"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '2425869629239289'
if answer == expected:
    print(f"PE492: PASS (got {answer})")
else:
    print(f"PE492: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('5', '203456792'), ('10', '203456797')]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    print(f"  N={w}: got {ans}")
