#!/usr/bin/env python3
"""PE 781-785: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    781: ("322512059",               "Feynman diagram / 费曼图"),
    782: ("325499120",               "Distinct Rows and Columns / 不同行列"),
    783: ("506132494",               "Urns / 瓮"),
    784: ("5834231041212316",        "Reciprocal Pairs / 互反对"),
    785: ("295269766",               "5-sextuples / 五元组"),
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
