#!/usr/bin/env python3
"""Verify PE483: Repeated Permutation answer = 32153032097171877"""
import subprocess, sys

result = subprocess.run(['./std'], input='100', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '32153032097171877'
if answer == expected:
    print(f"PE483: PASS (got {answer})")
else:
    print(f"PE483: FAIL (got {answer}, expected {expected})")
    sys.exit(1)
