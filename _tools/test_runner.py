#!/usr/bin/env python3
"""Test all PE 851-968 programs: compile + run with 'PE' input."""
import subprocess, os, sys, glob, json

BASE = "/Users/yini/Desktop/test/cpp/ProjectEuler"
TMPDIR = "/tmp/pe_test_851_968"
os.makedirs(TMPDIR, exist_ok=True)

KNOWN = {
    871: "497300941", 872: "622370484708689", 873: "644288016",
    874: "75640242", 875: "130702327",
    881: "183182007700", 882: "245143924", 883: "196246694",
    884: "966580193", 885: "827759707", 886: "178245463",
    887: "60.9112535", 888: "350608994", 889: "0.00801483",
    890: "120592557", 891: "7541783", 892: "34683298",
    893: "0.99993832", 894: "85516249", 895: "66687705",
    896: "0.04860463", 897: "460088576432531620", 898: "0.69233750",
    899: "0.13790397", 900: "840282274715517044",
}

# Find all PE dirs in 851-968
dirs = []
for d in os.listdir(BASE):
    if not d.startswith("PE"):
        continue
    try:
        num = int(d[2:])
    except:
        continue
    if 851 <= num <= 968:
        dirs.append((num, os.path.join(BASE, d)))

dirs.sort()
print(f"Found {len(dirs)} problems in range 851-968")
print()

compile_fail = []
runtime_fail = []
answer_mismatch = []
answer_ok = []
placeholder = []
not_found = []
compile_ok_count = 0

for num, d in dirs:
    cpp = os.path.join(d, "code", "std.cpp")
    if not os.path.exists(cpp):
        not_found.append(num)
        print(f"PE{num}: NOT FOUND")
        continue

    binary = os.path.join(TMPDIR, f"pe{num}")

    # Compile
    result = subprocess.run(
        ["g++", "-std=c++17", "-O2", "-o", binary, cpp],
        capture_output=True, text=True, timeout=60
    )
    if result.returncode != 0:
        compile_fail.append((num, result.stderr[:200]))
        print(f"PE{num}: COMPILE FAIL - {result.stderr[:100]}")
        continue

    compile_ok_count += 1

    # Run with 60s timeout
    try:
        result = subprocess.run(
            [binary],
            input="PE\n",
            capture_output=True, text=True, timeout=60
        )
        output = result.stdout.strip()
    except subprocess.TimeoutExpired:
        runtime_fail.append((num, "TIMEOUT"))
        print(f"PE{num}: TIMEOUT")
        continue
    except Exception as e:
        runtime_fail.append((num, str(e)))
        print(f"PE{num}: RUNTIME ERROR - {e}")
        continue

    # Extract numeric answer
    import re
    nums = re.findall(r'\d+\.?\d*', output)
    answer = nums[0] if nums else ""

    known = KNOWN.get(num)
    if known is not None:
        if answer == known:
            answer_ok.append(f"PE{num}: {answer}")
        else:
            answer_mismatch.append(f"PE{num}: got={answer}, exp={known}")
            print(f"PE{num}: MISMATCH got='{answer}' expected='{known}'")
    else:
        if not answer or answer in ("0", "0.0", "0.0000000000"):
            placeholder.append(f"PE{num}: placeholder ({answer})")
        else:
            answer_ok.append(f"PE{num}: {answer}")
            # print(f"PE{num}: OK answer={answer}")

print()
print("=" * 60)
print("RESULTS")
print("=" * 60)

print(f"\n--- Compile Failures ({len(compile_fail)}) ---")
for num, err in compile_fail:
    print(f"  PE{num}: {err}")

print(f"\n--- Runtime Failures ({len(runtime_fail)}) ---")
for num, err in runtime_fail:
    print(f"  PE{num}: {err}")

print(f"\n--- Answer Mismatches 851-900 ({len(answer_mismatch)}) ---")
for m in answer_mismatch:
    print(f"  {m}")
if not answer_mismatch:
    print("  (none)")

print(f"\n--- Placeholder Answers 901-968 ({len(placeholder)}) ---")
for m in placeholder:
    print(f"  {m}")

print(f"\n--- VERIFIED OK ({len(answer_ok)}) ---")
for m in answer_ok:
    print(f"  {m}")

if not_found:
    print(f"\n--- Not Found ({len(not_found)}) ---")
    for n in not_found:
        print(f"  PE{n}")

print(f"\n--- SUMMARY ---")
print(f"Total existing: {len(dirs)}")
print(f"Compile OK: {compile_ok_count}")
print(f"Compile Fail: {len(compile_fail)}")
print(f"Runtime Fail: {len(runtime_fail)}")
print(f"Answer Verified: {len(answer_ok)}")
print(f"Answer Mismatch: {len(answer_mismatch)}")
print(f"Placeholder: {len(placeholder)}")
