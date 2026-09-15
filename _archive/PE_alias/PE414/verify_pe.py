#!/usr/bin/env python3
"""Verify PE414: sum_{k=2..300} S(6k+3) last 18 digits = 552506775824935461"""
import subprocess, os

os.chdir(os.path.dirname(os.path.abspath(__file__)))
subprocess.run(["make", "std"], capture_output=True)
result = subprocess.run(["./std"], input="0\n", capture_output=True, text=True)
output = result.stdout.strip()
expected = "552506775824935461"
if output == expected:
    print(f"PE414 VERIFIED: {output}")
else:
    print(f"PE414 FAILED: got {output}, expected {expected}")
    exit(1)
