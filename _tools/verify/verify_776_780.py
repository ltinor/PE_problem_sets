#!/usr/bin/env python3
"""PE 776-780: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    776: ("201773590",    "Digit Sum Division / 数字和除法"),
    777: ("0.000238077",   "LCM of sum of divisors / 约数和的LCM"),
    778: ("146133880",     "Freshman's Product / 新生乘积"),
    779: ("0.54732610",    "Prime factor and exponent / 质因子与指数"),
    780: ("314079.9802",   "Triangle System / 三角系统"),
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
        print(f"PE{pid}: \u2713 ANSWER MATCH — {name}")
        passed += 1
    else:
        print(f"PE{pid}: \u2717 MISMATCH — got '{actual}', expected '{expected}' ({name})")
        failed += 1

print(f"\n{'='*50}")
print(f"Results: {passed} passed, {failed} failed out of {len(PROBLEMS)}")
sys.exit(0 if failed == 0 else 1)
