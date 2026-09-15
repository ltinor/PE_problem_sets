#!/usr/bin/env python3
"""PE 796-800: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    796: ("42.52546609",              "A Grand Shuffle / 大洗牌"),
    797: ("16436913",                 "Cyclogenic Polynomials / 循环多项式"),
    798: ("19.16212503",              "Card Stacking Game / 堆牌游戏"),
    799: ("209566086",                "Langton's ant II / 兰顿蚂蚁II"),
    800: ("1412403576",               "Hybrid Integers / 混合整数"),
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
