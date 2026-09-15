#!/usr/bin/env python3
"""Verify PE505: Bidirectional Recurrence — answer is 71459130866796214"""
import subprocess, sys

result = subprocess.run(['./std'], input='PE\n', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '71459130866796214'
if answer == expected:
    print(f"PE505: PASS (got {answer})")
else:
    print(f"PE505: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [
    ('0', '1'),
    ('1', '3'),
    ('2', '5'),
    ('5', '15'),
    ('10', '30'),
]
for w, exp in tests:
    result = subprocess.run(['./std'], input=w + '\n', capture_output=True, text=True)
    ans = result.stdout.strip()
    status = "OK" if ans == exp else "MISMATCH"
    print(f"  N={w}: got {ans} (expected {exp}) [{status}]")
