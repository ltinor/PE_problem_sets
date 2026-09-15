#!/usr/bin/env python3
"""Compute PE 426 final answer using block simulation (for verification only)"""
import sys

def solve_426(N_max):
    """Generate t_0..t_N, simulate BBS, return sum of squares"""
    MOD = 50515093
    s = 290797
    t = []
    for _ in range(N_max + 1):
        t.append((s % 64) + 1)
        s = (s * s) % MOD
    
    # Block-level simulation
    seq = list(t)
    prev = None
    for turn in range(100000):
        c = 0
        result = []
        for val in seq:
            if not result or len(result) % 2 == 0:  # currently at occupied block
                c += val
                result.append(('E', val))
            else:  # currently at empty block
                fill = min(c, val)
                c -= fill
                if fill > 0:
                    result.append(('O', fill))
                remaining = val - fill
                if remaining > 0:
                    result.append(('E', remaining))
        
        if c > 0:
            result.append(('O', c))
        
        # Merge same type
        merged = []
        for typ, size in result:
            if size == 0: continue
            if merged and merged[-1][0] == typ:
                merged[-1] = (typ, merged[-1][1] + size)
            else:
                merged.append((typ, size))
        while merged and merged[0][0] == 'E': merged.pop(0)
        while merged and merged[-1][0] == 'E': merged.pop()
        
        if not merged:
            seq = [0]
        else:
            seq = [merged[0][1]]
            for j in range(1, len(merged)): seq.append(merged[j][1])
        
        occ = sorted([seq[j] for j in range(0, len(seq), 2)])
        if occ == prev:
            ans = sum(x * x for x in occ)
            return ans
        prev = occ
    
    return -1

# Test small cases
for N in [10, 100, 500, 2000]:
    ans = solve_426(N)
    print(f"N={N}: sum_sq = {ans}")

# The PE answer should be 31591886008 for N=10000000
print(f"Expected PE answer: 31591886008")
