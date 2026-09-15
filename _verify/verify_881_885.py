#!/usr/bin/env python3
"""PE 881-885: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    881: ("183182007700",           "Divisor Graph Width / 约数图宽度"),
    882: ("245143924",              "Removing the Joker / 去掉鬼牌"),
    883: ("196246694",              "Remarkable Harmonic Triangles / 显著调和三角形"),
    884: ("966580193",              "Removing the Joker from the Game / 游戏中去除鬼牌"),
    885: ("827759707",              "Sorted Digits / 排序数字"),
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
