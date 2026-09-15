#!/usr/bin/env python3
"""Verify PE441 answer: S(10^7) = 5000088.8395"""
import subprocess, sys

# Test PE answer
result = subprocess.run(['./std'], input='10000000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '5000088.8395'
if answer == expected:
    print(f"PE441: PASS (got {answer})")
else:
    print(f"PE441: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

# Test S(10) for sanity
result = subprocess.run(['./std'], input='10', capture_output=True, text=True)
print(f"S(10) = {result.stdout.strip()}")
