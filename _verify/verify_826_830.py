#!/usr/bin/env python3
"""PE 826-830: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    826: ("23.77311635",            "Birds on a Wire / 电线上的鸟"),
    827: ("34981821048",             "Pseudoprime Nimbers / 伪素数Nim"),
    828: ("764545780025915",         "Numbers Challenge / 数字挑战"),
    829: ("883344930",               "Integral Fusion / 积分融合"),
    830: ("6822681719333421",        "Shifted Exponentiation / 平移指数"),
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
