#!/usr/bin/env python3
"""PE 861-870: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    861: ("1940527636228617032",   "Products of Divisors / 约数乘积"),
    862: ("380463671",              "Larger Digit Permutations / 较大数字排列"),
    863: ("264577536823",           "Digital Digit Factorial / 数字数字阶乘"),
    864: ("779724178",              "Square + 1 / 平方+1"),
    865: ("0.776767313",            "Trillion Zeckendorf Representation / 万亿Zeckendorf表示"),
    866: ("370223510432700",        "Tidying Up B / 整理B"),
    867: ("631682239",              "T-polyominoes / T多联骨牌"),
    868: ("636384916",              "BELFORT"),
    869: ("14.97696693",            "Prime Guessing / 素数猜数"),
    870: ("84618346",               "Unbreaking / 不打破"),
}

BASE = os.path.dirname(os.path.abspath(__file__))
passed = 0
failed = 0

for pid, (expected, name) in PROBLEMS.items():
    pe_dir = f"PE0{pid}" if pid >= 1000 else f"PE{pid:04d}"
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
