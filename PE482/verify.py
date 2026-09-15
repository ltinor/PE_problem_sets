#!/usr/bin/env python3
"""Verify PE482: Incenter answer = 14008248791472"""
import subprocess, sys

result = subprocess.run(['./std'], input='100', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '14008248791472'
if answer == expected:
    print(f"PE482: PASS (got {answer})")
else:
    print(f"PE482: FAIL (got {answer}, expected {expected})")
    sys.exit(1)
