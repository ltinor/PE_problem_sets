#!/usr/bin/env python3
"""Verify PE495: answer is 789107601"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '789107601'
if answer == expected:
    print(f"PE495: PASS (got {answer})")
else:
    print(f"PE495: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('6 2', '4'), ('12 3', '18')]  # 12=2^2*3: C(2+3-1,2)*C(1+3-1,2)=C(4,2)*C(3,2)=6*3=18
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    print(f"  {w}: got {ans} (expected {exp})")
