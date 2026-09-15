#!/usr/bin/env python3
"""PE 751-755: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    751: ("2.18922322",     "Concatenation Coincidence / 拼接巧合"),
    752: ("56158650",        "Powers of 1+√7 / 1+√7的幂"),
    753: ("4714126766770661623", "Cauchy Matrix / 柯西矩阵"),
    754: ("1999092",         "Product of Gauss Factorials / 高斯阶乘积"),
    755: ("2877071595975576960", "Direct Zeckendorf Optimization / 直接Zeck优化"),
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
        print(f"PE{pid}: BUILD FAILED — {r.stderr[:120]}")
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
