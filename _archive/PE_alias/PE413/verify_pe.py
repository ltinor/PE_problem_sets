#!/usr/bin/env python3
"""Verify PE413: F(10^19) = 3079418648040719"""
import subprocess, os

os.chdir(os.path.dirname(os.path.abspath(__file__)))
subprocess.run(["make", "std"], capture_output=True)
result = subprocess.run(["./std"], input="10000000000000000000\n", capture_output=True, text=True)
output = result.stdout.strip()
expected = "3079418648040719"
if output == expected:
    print(f"PE413 VERIFIED: {output}")
else:
    print(f"PE413 FAILED: got {output}, expected {expected}")
    exit(1)
