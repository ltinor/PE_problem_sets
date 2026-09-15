#!/usr/bin/env python3
"""Verify PE484: Arithmetic Derivative answer = 8907904768686152599"""
import subprocess, sys

result = subprocess.run(['./std'], input='1000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '8907904768686152599'
if answer == expected:
    print(f"PE484: PASS (got {answer})")
else:
    print(f"PE484: FAIL (got {answer}, expected {expected})")
    sys.exit(1)
