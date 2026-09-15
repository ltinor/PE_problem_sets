#!/usr/bin/env python3
"""Verify PE 771-775 answers match expected values."""

import subprocess
import os

WORKDIR = "/Users/yini/Desktop/test/cpp/ProjectEuler"

problems = [
    (771, 205836930055736842),
    (772, 83985379),
    (773, 55620670),
    (774, 1064883765),
    (775, 946791106),
]

all_pass = True
for pe, expected in problems:
    exe = os.path.join(WORKDIR, f"PE{pe}/code/std")
    if not os.path.exists(exe):
        # Try to compile
        src = os.path.join(WORKDIR, f"PE{pe}/code/std.cpp")
        result = subprocess.run(
            ["g++", "-std=c++17", "-O2", src, "-o", exe],
            capture_output=True, text=True
        )
        if result.returncode != 0:
            print(f"PE{pe}: COMPILE ERROR\n{result.stderr}")
            all_pass = False
            continue
    
    result = subprocess.run(
        [exe], input="PE", capture_output=True, text=True, timeout=10
    )
    actual = result.stdout.strip()
    if actual == str(expected):
        print(f"PE{pe}: ✅ PASS  (expected={expected}, got={actual})")
    else:
        print(f"PE{pe}: ❌ FAIL  (expected={expected}, got={actual})")
        all_pass = False

print()
if all_pass:
    print("All PE 771-775 answers verified! ✅")
else:
    print("Some verifications failed! ❌")
