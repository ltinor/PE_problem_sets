#!/usr/bin/env python3
"""Verify PE485: Maximum number of divisors answer = 51281274353247367"""
import subprocess, sys

result = subprocess.run(['./std'], input='1000000 1000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '51281274353247367'
if answer == expected:
    print(f"PE485: PASS (got {answer})")
else:
    print(f"PE485: FAIL (got {answer}, expected {expected})")
    sys.exit(1)
