#!/usr/bin/env python3
"""PE 886-895: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    886: ("178245463",           "Coprime Permutations / 互质排列"),
    887: ("60.9112535",          "Bounded Primes / 有界素数"),
    888: ("350608994",           "1249 Numbers / 1249数"),
    889: ("0.00801483",          "Rational Blancmange / 有理牛奶冻"),
    890: ("120592557",           "Clock II / 时钟II"),
    891: ("7541783",             "Unambiguous Clock / 无歧义时钟"),
    892: ("34683298",            "Zebra Irrationals / 斑马无理数"),
    893: ("0.99993832",          "Möbius Matchsticks / 莫比乌斯火柴"),
    894: ("85516249",            "Spiral of Theodorus / 泰奥多勒斯螺线"),
    895: ("66687705",            "Goldbach's Other Comet / 哥德巴赫的另一彗星"),
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
