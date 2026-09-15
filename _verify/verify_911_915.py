#!/usr/bin/env python3
"""PE 911-915: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    911: ("21.303979",               "Khinchin's Constant / 辛钦常数"),
    912: ("562685338",               "Where are the Primes? / 素数在哪"),
    913: ("2101925115560555020",     "Row-Major vs Column-Major / 行主序vs列主序"),
    914: ("66514746",                "Triangle in the Saddle / 鞍中三角"),
    915: ("60112743",                "Sudoku Variant / 数独变种"),
}

BASE = os.path.dirname(os.path.abspath(__file__))
passed = 0
failed = 0

for pid, (expected, name) in PROBLEMS.items():
    pe_dir = f"PE{pid:04d}"
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
        print(f"PE{pid}: \u2713 ANSWER MATCH — {name}")
        passed += 1
    else:
        print(f"PE{pid}: \u2717 MISMATCH — got '{actual}', expected '{expected}' ({name})")
        failed += 1

print(f"\n{'='*50}")
print(f"Results: {passed} passed, {failed} failed out of {len(PROBLEMS)}")
sys.exit(0 if failed == 0 else 1)
