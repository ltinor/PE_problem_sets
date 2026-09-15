#!/usr/bin/env python3
"""Verify PE 871-875 answers match expected values."""

import subprocess
import os

WORKDIR = "/Users/yini/Desktop/test/cpp/ProjectEuler"

problems = [
    (871, 497300941),
    (872, 622370484708689),
    (873, 644288016),
    (874, 75640242),
    (875, 130702327),
]

all_pass = True
for pe, expected in problems:
    exe = os.path.join(WORKDIR, f"PE{pe}/code/std")
    if not os.path.exists(exe):
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
        print(f"PE{pe}: \u2705 PASS  (expected={expected}, got={actual})")
    else:
        print(f"PE{pe}: \u274c FAIL  (expected={expected}, got={actual})")
        all_pass = False

print()
if all_pass:
    print("All PE 871-875 answers verified! \u2705")
else:
    print("Some verifications failed! \u274c")
