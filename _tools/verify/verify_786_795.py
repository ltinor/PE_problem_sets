#!/usr/bin/env python3
"""PE 786-795: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    786: ("18999616",               "Billiard / 台球"),
    787: ("202676543",              "Bezout's Game / Bezout游戏"),
    788: ("471745499",              "Dominating numbers / 支配数"),
    789: ("174047818579065",        "Minimal pairing modulo p / 模p最小配对"),
    790: ("73597483551591773",      "Clock Grid / 时钟网格"),
    791: ("40454087",               "Prefect Squares / 完全平方"),
    792: ("475019340",              "Too Many Twos / 太多2"),
    793: ("4758086501311202972",    "Median of Products / 乘积中位数"),
    794: ("56375722",               "Seventeen points / 十七个点"),
    795: ("955892601788276",        "Alternating gcd sum / 交替GCD和"),
}

BASE = os.path.dirname(os.path.abspath(__file__))
passed = 0
failed = 0

for pid, (expected, name) in PROBLEMS.items():
    pe_dir = f"PE{pid}"
    src = os.path.join(BASE, pe_dir, "code", "std.cpp")
    exe = os.path.join(BASE, pe_dir, "code", "std")

    r = subprocess.run(
        ["g++", "-std=c++17", "-O2", "-o", exe, src],
        capture_output=True, text=True
    )
    if r.returncode != 0:
        print(f"PE{pid}: BUILD FAILED — {r.stderr[:120]}")
        failed += 1
        continue

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
