#!/usr/bin/env python3
"""Verify PE496: answer is 666577909"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '666577909'
if answer == expected:
    print(f"PE496: PASS (got {answer})")
else:
    print(f"PE496: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('10', '24'), ('20', '72'), ('30', '204')]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    print(f"  N={w}: got {ans} (expected {exp})")
