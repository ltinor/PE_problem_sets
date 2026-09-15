#!/usr/bin/env python3
"""Check convergence speed of BBS"""
import sys

def generate_t(N):
    s = 290797
    MOD = 50515093
    t = []
    for _ in range(N + 1):
        t.append((s % 64) + 1)
        s = (s * s) % MOD
    return t

def bbs_turn_blocks(seq):
    c = 0
    result = []  # (type, size)
    for i, val in enumerate(seq):
        if i % 2 == 0:
            c += val
            result.append(('E', val))
        else:
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
    
    while merged and merged[0][0] == 'E':
        merged.pop(0)
    while merged and merged[-1][0] == 'E':
        merged.pop()
    
    if not merged: return [0]
    flat = [merged[0][1]]
    for i in range(1, len(merged)):
        flat.append(merged[i][1])
    return flat

def extract_occupied(seq):
    return sorted([seq[i] for i in range(0, len(seq), 2)])

# Test convergence for increasing sizes
for N in [10, 50, 100, 200, 500, 1000]:
    t = generate_t(N)
    seq = list(t)
    prev_occ = None
    for turn in range(1, 10001):
        seq = bbs_turn_blocks(seq)
        occ = extract_occupied(seq)
        if occ == prev_occ:
            print(f"N={N+1} elements: converged in {turn} turns, {len(occ)} solitons")
            break
        prev_occ = occ
    else:
        print(f"N={N+1}: did not converge in 10000 turns")
