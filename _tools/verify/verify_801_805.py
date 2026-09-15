#!/usr/bin/env python3
"""PE 801-805: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    801: ("7937995",                    "Equable Matrices / 公正矩阵"),
    802: ("139786440370676700",         "Iterated Composition / 迭代组合"),
    803: ("150056452701858318",         "Pseudorandom Sequence / 伪随机序列"),
    804: ("721014409585053",            "Count Binary Quadratic Representations / 二元二次型表示计数"),
    805: ("7007143846988468270",        "Shifted Multiples / 平移倍数"),
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
