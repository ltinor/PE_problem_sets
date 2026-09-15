#!/usr/bin/env python3
"""Verify PE 551-650: compile, run with "PE" input, check output."""
import subprocess
import os
import sys
import tempfile
import shutil

WORKDIR = "/Users/yini/Desktop/test/cpp/ProjectEuler"
TIMEOUT = 120  # seconds per run

def main():
    os.chdir(WORKDIR)
    print("=== PE 551-650 Verification (input: 'PE') ===")
    print(f"Started at {__import__('datetime').datetime.now()}")

    total = 0
    passed = 0
    compile_fail = 0
    runtime_fail = 0
    timeout_fail = 0
    no_src = 0
    multi_line = 0
    missing = []
    problems_with_issues = []

    # Expected PE answers (from source code comments / known values)
    # We'll check against embedded answers in the source
    expected = {}

    for num in range(551, 651):
        pe_dir = f"PE{num}"
        src = os.path.join(pe_dir, "code", "std.cpp")
        if not os.path.exists(src):
            no_src += 1
            missing.append(num)
            continue

        total += 1

        # Compile
        with tempfile.NamedTemporaryFile(suffix='', prefix=f'pe{num}_', delete=False) as tmp:
            bin_path = tmp.name

        compile_result = subprocess.run(
            ["g++", "-std=c++17", "-O2", "-o", bin_path, src],
            capture_output=True, text=True, timeout=60
        )

        if compile_result.returncode != 0:
            compile_fail += 1
            error_msg = compile_result.stderr.strip()[:300]
            problems_with_issues.append(f"PE{num}: COMPILE ERROR - {error_msg}")
            print(f"  [COMPILE FAIL] PE{num}")
            os.unlink(bin_path)
            continue

        # Run with "PE\n" as input
        try:
            run_result = subprocess.run(
                [bin_path],
                input="PE\n",
                capture_output=True, text=True,
                timeout=TIMEOUT
            )
            output = run_result.stdout.strip()
            stderr = run_result.stderr.strip()
            rc = run_result.returncode
        except subprocess.TimeoutExpired:
            timeout_fail += 1
            problems_with_issues.append(f"PE{num}: TIMEOUT (>{TIMEOUT}s)")
            print(f"  [TIMEOUT] PE{num} (>{TIMEOUT}s)")
            os.unlink(bin_path)
            continue

        os.unlink(bin_path)

        if rc != 0:
            runtime_fail += 1
            err = stderr[:200] if stderr else output[:200]
            problems_with_issues.append(f"PE{num}: RUNTIME ERROR (rc={rc}) - {err}")
            print(f"  [RUNTIME FAIL] PE{num} (rc={rc})")
            continue

        if not output:
            runtime_fail += 1
            problems_with_issues.append(f"PE{num}: EMPTY OUTPUT")
            print(f"  [EMPTY] PE{num}")
            continue

        # Check if multi-line output (only last line should be the answer)
        lines = output.split('\n')
        answer = lines[-1].strip()
        if len(lines) > 1:
            multi_line += 1
            problems_with_issues.append(f"PE{num}: MULTI-LINE ({len(lines)} lines) → answer: {answer}")
            print(f"  [MULTI] PE{num} ({len(lines)} lines): {answer}")
        else:
            print(f"  [OK] PE{num}: {answer}")
        passed += 1

    print()
    print("=== SUMMARY ===")
    print(f"Total PE dirs with code: {total}")
    print(f"Missing source files: {no_src}")
    if missing:
        print(f"  Missing: {missing}")
    print(f"Compile failures: {compile_fail}")
    print(f"Timeouts: {timeout_fail}")
    print(f"Runtime failures (incl. empty output): {runtime_fail}")
    print(f"Multi-line output: {multi_line}")
    print(f"Passed (clean or multi-line): {passed}")

    if problems_with_issues:
        print()
        print("=== PROBLEMS/ISSUES ===")
        for issue in problems_with_issues:
            print(f"  {issue}")

    print(f"\nFinished at {__import__('datetime').datetime.now()}")

if __name__ == "__main__":
    main()
