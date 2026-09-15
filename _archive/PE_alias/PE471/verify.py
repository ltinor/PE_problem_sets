#!/usr/bin/env python3
"""Verify PE471 answer: G(10^11) -> 392832933"""
import subprocess, sys

result = subprocess.run(['./std'], input='100000000000', capture_output=True, text=True)
answer = result.stdout.strip()
expected = '392832933'
if answer == expected:
    print(f"PE471: PASS (got {answer})")
else:
    print(f"PE471: FAIL (got {answer}, expected {expected})")
    sys.exit(1)

tests = [('10', '20.59722222'), ('100', '19223.60980')]
for n, exp in tests:
    result = subprocess.run(['./std'], input=n, capture_output=True, text=True)
    ans = result.stdout.strip()
    if ans == exp:
        print(f"  G({n}) = {ans} OK")
    else:
        print(f"  G({n}) = {ans} (expected {exp}) FAIL")
        sys.exit(1)
