#!/usr/bin/env python3
"""Verify PE415: T(10^11) mod 10^8 = 55859775"""
import subprocess, os

os.chdir(os.path.dirname(os.path.abspath(__file__)))
subprocess.run(["make", "std"], capture_output=True)
result = subprocess.run(["./std"], input="100000000000\n", capture_output=True, text=True)
output = result.stdout.strip()
expected = "55859775"
if output == expected:
    print(f"PE415 VERIFIED: {output}")
else:
    print(f"PE415 FAILED: got {output}, expected {expected}")
    exit(1)
