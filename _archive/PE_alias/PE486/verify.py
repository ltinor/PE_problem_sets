#!/usr/bin/env python3
"""Verify PE486: Palindrome-like sequences answer = 1140845050"""
import subprocess, sys

result = subprocess.run(['./std'], input='100', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '1140845050'
if answer == expected:
    print(f"PE486: PASS (got {answer})")
else:
    print(f"PE486: FAIL (got {answer}, expected {expected})")
    sys.exit(1)
