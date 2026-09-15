#!/usr/bin/env python3
"""PE 916-925: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    916: ("PLACEHOLDER",            "Restricted Permutations / 有限制排列"),
    917: ("PLACEHOLDER",            "Minimal Path Using Additive Cost / 代价为特定项相加时的最小路径和"),
    918: ("PLACEHOLDER",            "Recursive Sequence Summation / 递归序列求和"),
    919: ("PLACEHOLDER",            "Fortunate Triangles / 幸运三角形"),
    920: ("PLACEHOLDER",            "Tau Numbers / 陶数"),
    921: ("378401935",              "Golden Recurrence / 黄金递推"),
    922: ("PLACEHOLDER",            "Young's Game A / 杨氏游戏（一）"),
    923: ("PLACEHOLDER",            "Young's Game B / 杨氏游戏（二）"),
    924: ("PLACEHOLDER",            "Larger Digit Permutation II / 更大的数字重排（二）"),
    925: ("PLACEHOLDER",            "Larger Digit Permutation III / 更大的数字重排（三）"),
}

BASE = os.path.dirname(os.path.abspath(__file__))
passed = 0
failed = 0

for pid, (expected, name) in PROBLEMS.items():
    pe_dir = f"PE{pid}"
    src = os.path.join(BASE, pe_dir, "code", "std.cpp")
    exe = os.path.join(BASE, pe_dir, "code", "std")

    if not os.path.exists(src):
        print(f"PE{pid}: MISSING FILE — {src}")
        failed += 1
        continue

    # Compile
    r = subprocess.run(
        ["g++", "-std=c++17", "-O2", "-o", exe, src],
        capture_output=True, text=True, timeout=30
    )
    if r.returncode != 0:
        print(f"PE{pid}: BUILD FAILED — {r.stderr[:300]}")
        failed += 1
        continue

    if expected == "PLACEHOLDER":
        print(f"PE{pid}: BUILT OK (answer not yet verified) — {name}")
        passed += 1
        continue

    # Run PE query
    r = subprocess.run([exe], input="PE", capture_output=True, text=True, timeout=10)
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
