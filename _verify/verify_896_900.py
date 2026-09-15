#!/usr/bin/env python3
"""PE 896-900: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    896: ("0.04860463",              "Divisible Ranges / 整除区间"),
    897: ("460088576432531620",      "Connected Prime Squares / 连通素数平方"),
    898: ("0.69233750",              "Clock Sequence II / 时钟序列II"),
    899: ("0.13790397",              "Distribuition / 分布"),
    900: ("840282274715517044",      "Cumulative Totients / 累积欧拉函数"),
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
        print(f"PE{pid}: \u2713 ANSWER MATCH — {name}")
        passed += 1
    else:
        print(f"PE{pid}: \u2717 MISMATCH — got '{actual}', expected '{expected}' ({name})")
        failed += 1

print(f"\n{'='*50}")
print(f"Results: {passed} passed, {failed} failed out of {len(PROBLEMS)}")
sys.exit(0 if failed == 0 else 1)
