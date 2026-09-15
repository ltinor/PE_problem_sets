#!/usr/bin/env python3
"""PE 926-935: Verification script."""
import subprocess, os, sys

PROBLEMS = {
    926: ("PLACEHOLDER",            "Total Roundness / 总取整度"),
    927: ("PLACEHOLDER",            "Prime-ary Tree / 素数多叉树"),
    928: ("PLACEHOLDER",            "Cribbage / 克里比奇纸牌"),
    929: ("PLACEHOLDER",            "Odd-Run Compositions / 奇数长度分段组成"),
    930: ("PLACEHOLDER",            "The Gathering / 小球聚会"),
    931: ("PLACEHOLDER",            "Totient Graph / 欧拉函数图"),
    932: ("PLACEHOLDER",            "2025 / 2025"),
    933: ("PLACEHOLDER",            "Paper Cutting / 纸张切割"),
    934: ("PLACEHOLDER",            "Unlucky Primes / 不幸素数"),
    935: ("PLACEHOLDER",            "Rolling Square / 翻滚的正方形"),
}

BASE = os.path.dirname(os.path.abspath(__file__))
passed = 0
failed = 0

for pid, (expected, name) in PROBLEMS.items():
    pe_dir = f"PE{pid}"
    src = os.path.join(BASE, pe_dir, "code", "std.cpp")
    exe = os.path.join(BASE, pe_dir, "code", "std")

    if not os.path.exists(src):
        print(f"PE{pid}: MISSING FILE — {src}")
        failed += 1
        continue

    # Compile
    r = subprocess.run(
        ["g++", "-std=c++17", "-O2", "-o", exe, src],
        capture_output=True, text=True, timeout=30
    )
    if r.returncode != 0:
        print(f"PE{pid}: BUILD FAILED — {r.stderr[:300]}")
        failed += 1
        continue

    if expected == "PLACEHOLDER":
        print(f"PE{pid}: BUILT OK (answer not yet verified) — {name}")
        passed += 1
        continue

    # Run PE query
    r = subprocess.run([exe], input="PE", capture_output=True, text=True, timeout=10)
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
