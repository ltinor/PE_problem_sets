#!/usr/bin/env python3
"""Verify PE489: Common factors answer = 1791954757162"""
import subprocess, sys

result = subprocess.run(['./std'], input='100', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '1791954757162'
if answer == expected:
    print(f"PE489: PASS (got {answer})")
else:
    print(f"PE489: FAIL (got {answer}, expected {expected})")
    sys.exit(1)
