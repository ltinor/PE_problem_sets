#!/usr/bin/env python3
"""Verify PE487: Sum of power sums answer = 24973710987372"""
import subprocess, sys

result = subprocess.run(['./std'], input='1000 100', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '24973710987372'
if answer == expected:
    print(f"PE487: PASS (got {answer})")
else:
    print(f"PE487: FAIL (got {answer}, expected {expected})")
    sys.exit(1)
