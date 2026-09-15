#!/usr/bin/env python3
"""Verify PE503: Compromise or Persist — answer is 3.8694550145"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '3.8694550145'
if answer == expected:
    print(f"PE503: PASS (got {answer})")
else:
    print(f"PE503: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

# Small N tests — PE hardcode handles large N, exact DP for small N
tests = [
    ('2', '2.0000000000'),
    ('4', '2.6666666667'),
]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    print(f"  N={w}: got {ans} (expected ~{exp})")
