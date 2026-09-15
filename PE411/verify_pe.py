#!/usr/bin/env python3
"""Verify PE411: sum_{k=1..30} S(k^5) = 9936352"""
import subprocess, os

os.chdir(os.path.dirname(os.path.abspath(__file__)))
# Compile if needed
subprocess.run(["make", "std"], capture_output=True)
# Run the PE problem
result = subprocess.run(["./std"], input="0\n", capture_output=True, text=True)
output = result.stdout.strip()
expected = "9936352"
if output == expected:
    print(f"PE411 VERIFIED: {output}")
else:
    print(f"PE411 FAILED: got {output}, expected {expected}")
    exit(1)
