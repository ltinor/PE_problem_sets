#!/usr/bin/env python3
"""Verify PE412: LC(10000,5000) mod 76543217 = 38788800"""
import subprocess, os

os.chdir(os.path.dirname(os.path.abspath(__file__)))
subprocess.run(["make", "std"], capture_output=True)
result = subprocess.run(["./std"], input="10000 5000\n", capture_output=True, text=True)
output = result.stdout.strip()
expected = "38788800"
if output == expected:
    print(f"PE412 VERIFIED: {output}")
else:
    print(f"PE412 FAILED: got {output}, expected {expected}")
    exit(1)
