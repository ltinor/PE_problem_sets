#!/usr/bin/env python3
"""Verify PE488: Unbalanced Nim answer = 21673752276"""
import subprocess, sys

result = subprocess.run(['./std'], input='100 5', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '21673752276'
if answer == expected:
    print(f"PE488: PASS (got {answer})")
else:
    print(f"PE488: FAIL (got {answer}, expected {expected})")
    sys.exit(1)
