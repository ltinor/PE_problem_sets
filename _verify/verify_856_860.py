#!/usr/bin/env python3
"""PE 856-860: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    856: ("2.59149127",              "Waiting for a Pair / 等待对子"),
    857: ("697354363",               "Beautiful Graphs / 美丽图"),
    858: ("930235231314",            "LCM / 最小公倍数"),
    859: ("18989964",               "Cookie Game / 饼干游戏"),
    860: ("71743330777707",          "Gold and Silver Coin Game / 金银硬币游戏"),
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
