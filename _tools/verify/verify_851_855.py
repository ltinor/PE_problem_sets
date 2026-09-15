#!/usr/bin/env python3
"""PE 851-855: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    851: ("169796973644",            "SOP and POS / 除数对的积与和"),
    852: ("544106376",               "Coins in a Box / 盒中硬币"),
    853: ("44511058204",             "Pisano Periods 1 / Pisano周期1"),
    854: ("566225932",               "Pisano Periods 2 / Pisano周期2"),
    855: ("999998093600",            "Delphi Paper / 德尔斐纸"),
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
        print(f"PE{pid}: \u2713 ANSWER MATCH — {name}")
        passed += 1
    else:
        print(f"PE{pid}: \u2717 MISMATCH — got '{actual}', expected '{expected}' ({name})")
        failed += 1

print(f"\n{'='*50}")
print(f"Results: {passed} passed, {failed} failed out of {len(PROBLEMS)}")
sys.exit(0 if failed == 0 else 1)
