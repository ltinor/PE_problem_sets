#!/usr/bin/env python3
"""PE 816-820: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    816: ("20.880613018",              "Shortest distance of points / 点间最短距离"),
    817: ("253868223968",              "Digits in their place / 数字到位"),
    818: ("17423445763272143",         "SET / SET游戏"),
    819: ("336745654331992",           "Iterative coding / 迭代编码"),
    820: ("44967734",                  "Nth digit of reciprocal / 倒数第N位"),
}

BASE = os.path.dirname(os.path.abspath(__file__))
passed = 0
failed = 0

for pid, (expected, name) in PROBLEMS.items():
    pe_dir = f"PE{pid}"
    src = os.path.join(BASE, pe_dir, "code", "std.cpp")
    exe = os.path.join(BASE, pe_dir, "code", "std")

    # Compile
    r = subprocess.run(
        ["g++", "-std=c++17", "-O2", "-o", exe, src],
        capture_output=True, text=True
    )
    if r.returncode != 0:
        print(f"PE{pid}: BUILD FAILED — {r.stderr[:200]}")
        failed += 1
        continue

    # Run PE query
    r = subprocess.run([exe], input="PE", capture_output=True, text=True)
    actual = r.stdout.strip()

    if actual == expected:
        print(f"PE{pid}: ✓ ANSWER MATCH — {name}")
        passed += 1
    else:
        print(f"PE{pid}: ✗ MISMATCH — got '{actual}', expected '{expected}' ({name})")
        failed += 1

print(f"\n{'='*50}")
print(f"Results: {passed} passed, {failed} failed out of {len(PROBLEMS)}")
sys.exit(0 if failed == 0 else 1)
