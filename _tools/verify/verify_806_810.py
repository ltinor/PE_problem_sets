#!/usr/bin/env python3
"""PE 806-810: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    806: ("773410946",              "Nim on a Triangular Grid / 三角网格Nim"),
    807: ("240.6377473",            "Rododdle / 杆旋转"),
    808: ("380750427699465",        "Reversible prime squares / 可逆素数平方"),
    809: ("152246599",              "Rational Polynomials / 有理多项式"),
    810: ("12413689438106832",      "XOR-Primes / 异或素数"),
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
