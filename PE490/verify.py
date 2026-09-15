#!/usr/bin/env python3
"""Verify PE490: Jumping frog answer = 777577439507945"""
import subprocess, sys

result = subprocess.run(['./std'], input='1000 10', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '777577439507945'
if answer == expected:
    print(f"PE490: PASS (got {answer})")
else:
    print(f"PE490: FAIL (got {answer}, expected {expected})")
    sys.exit(1)
