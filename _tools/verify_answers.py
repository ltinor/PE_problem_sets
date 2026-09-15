#!/usr/bin/env python3
"""Verify PE answers: compare runtime output against embedded expected answers."""
import subprocess
import os
import tempfile
import re

WORKDIR = "/Users/yini/Desktop/test/cpp/ProjectEuler"

def extract_expected(content):
    """Extract PE answer from source code. Priority:
    1. PE_ANSWER constant definition
    2. Comment: "PE answer: X" (but not if it's a huge number that clearly isn't the modulo)
    """
    # Method 1: const ll PE_ANSWER = value;
    m = re.search(r'const\s+\w+\s+PE_ANSWER\s*=\s*([^;]+);', content)
    if m:
        val = m.group(1).strip()
        # Could be an expression like "269496760"
        # Handle simple cases
        if re.match(r'^[\d.]+$', val):
            return val
    
    # Method 2: Look for cout << "X" or cout << X in the "PE" branch
    # Find the if (query == "PE") block
    pe_block = re.search(r'if\s*\(.*?"PE".*?\)\s*\{([^}]+)\}', content)
    if pe_block:
        block = pe_block.group(1)
        # Look for cout << value
        m = re.search(r'cout\s*<<\s*"?([\d.]+)"?', block)
        if m:
            val = m.group(1)
            if re.match(r'^[\d.]+$', val):
                return val
        # Try PE_ANSWER
        m = re.search(r'cout\s*<<\s*PE_ANSWER', block)
        if m:
            # Look up PE_ANSWER value
            m2 = re.search(r'const\s+\w+\s+PE_ANSWER\s*=\s*([\d.]+)', content)
            if m2:
                return m2.group(1)
    
    # Method 3: Comment "PE answer: X"
    m = re.search(r'PE\s*answer[:：]\s*([\d.]+)', content)
    if m:
        return m.group(1)
    
    return None

def main():
    os.chdir(WORKDIR)
    print("=== PE 551-650 Answer Verification ===")
    
    issues = []
    verified = 0
    no_expected = 0
    total = 0
    all_results = []
    
    for num in range(551, 651):
        src = f"PE{num}/code/std.cpp"
        if not os.path.exists(src):
            continue
        total += 1
        
        with open(src) as f:
            content = f.read()
        
        expected = extract_expected(content)
        
        # Compile
        with tempfile.NamedTemporaryFile(suffix='', prefix=f'pe{num}_', delete=False) as tmp:
            bin_path = tmp.name
        
        subprocess.run(['g++', '-std=c++17', '-O2', '-o', bin_path, src],
                       capture_output=True, timeout=60)
        
        # Run
        result = subprocess.run([bin_path], input='PE\n', capture_output=True, text=True, timeout=120)
        actual = result.stdout.strip().split('\n')[-1].strip()
        os.unlink(bin_path)
        
        if result.returncode != 0:
            issues.append(f"PE{num}: RUNTIME ERROR - {actual[:100]}")
            continue
        
        if expected:
            exp_norm = expected.strip()
            act_norm = actual.strip()
            if exp_norm != act_norm:
                issues.append(f"PE{num}: MISMATCH expected={exp_norm} actual={act_norm}")
                print(f"  [MISMATCH] PE{num}: expected={exp_norm} actual={act_norm}")
            else:
                verified += 1
                print(f"  [MATCH] PE{num}: {act_norm}")
        else:
            no_expected += 1
            print(f"  [NO_EXP] PE{num}: {actual}")
        all_results.append((num, actual))
    
    print()
    print("=== SUMMARY ===")
    print(f"Total: {total}")
    print(f"Verified matches: {verified}")
    print(f"No embedded answer found: {no_expected}")
    if issues:
        print(f"Issues ({len(issues)}):")
        for i in issues:
            print(f"  {i}")
    
    print()
    print("=== ALL ANSWERS (PE551-650) ===")
    for num, ans in all_results:
        print(f"  PE{num}: {ans}")
    print("Done.")

if __name__ == "__main__":
    main()
