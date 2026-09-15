#!/usr/bin/env python3
"""Verify PE449 answer: coating volume for a=3, b=1 = 103.37870096"""
import subprocess, sys

# Test PE answer
result = subprocess.run(['./std'], input='3', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '103.37870096'
if answer == expected:
    print(f"PE449: PASS (got {answer})")
else:
    print(f"PE449: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

# Test given values
# a=1: 28*pi/3 ≈ 29.32153088
import math
expected1 = f"{28*math.pi/3:.8f}"
result = subprocess.run(['./std'], input='1', capture_output=True, text=True)
answer1 = result.stdout.strip()
if answer1 == expected1:
    print(f"  a=1: {answer1} OK")
else:
    print(f"  a=1: {answer1} (expected {expected1})")

# a=2: 60.35475635
result = subprocess.run(['./std'], input='2', capture_output=True, text=True)
answer2 = result.stdout.strip()
expected2 = '60.35475635'
if answer2 == expected2:
    print(f"  a=2: {answer2} OK")
else:
    print(f"  a=2: {answer2} (expected {expected2}) FAIL")
    sys.exit(1)
