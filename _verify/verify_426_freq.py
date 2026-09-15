#!/usr/bin/env python3
"""Test frequency-based algorithm for BBS final state"""
import sys
import heapq

def generate_t(N):
    s = 290797
    MOD = 50515093
    t = []
    for _ in range(N + 1):
        t.append((s % 64) + 1)
        s = (s * s) % MOD
    return t

def final_state_freq(t):
    """Process alternating sequence using frequency array.
    For each occupied block x: add x to soliton pool
    For each empty block y: advance y smallest solitons by 1 each
    """
    # freq[i] = number of solitons of size i
    freq = {}
    max_size = 0
    
    for i, val in enumerate(t):
        if i % 2 == 0:  # occupied block
            freq[val] = freq.get(val, 0) + 1
            max_size = max(max_size, val)
        else:  # empty block
            remaining = val
            # Advance smallest solitons
            size = 1
            while remaining > 0:
                while size <= max_size and freq.get(size, 0) == 0:
                    size += 1
                if size > max_size:
                    break
                take = min(remaining, freq[size])
                freq[size] -= take
                if freq[size] == 0:
                    del freq[size]
                freq[size + 1] = freq.get(size + 1, 0) + take
                max_size = max(max_size, size + 1)
                remaining -= take
    
    # Convert to sorted list
    result = []
    for k in sorted(freq.keys()):
        result.extend([k] * freq[k])
    return result

def final_state_sim(t):
    """Block-level simulation (ground truth)"""
    seq = list(t)
    prev = None
    for _ in range(100000):
        # One turn
        c = 0
        result = []
        for i, val in enumerate(seq):
            if i % 2 == 0:
                c += val
                result.append(('E', val))
            else:
                fill = min(c, val)
                c -= fill
                if fill > 0:
                    result.append(('O', fill))
                if val - fill > 0:
                    result.append(('E', val - fill))
        if c > 0:
            result.append(('O', c))
        
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
        
        if not merged:
            seq = [0]
        else:
            seq = [merged[0][1]]
            for j in range(1, len(merged)):
                seq.append(merged[j][1])
        
        occ = sorted([seq[j] for j in range(0, len(seq), 2)])
        if occ == prev:
            return occ
        prev = occ
    return None

# Test for increasing N
for N in [10, 20, 50, 100, 200]:
    t = generate_t(N)
    
    freq_result = final_state_freq(t)
    sim_result = final_state_sim(t)
    
    match = freq_result == sim_result
    print(f"N={N+1}: freq={freq_result[:10]}... sum={sum(freq_result)}")
    print(f"       sim ={sim_result[:10]}... sum={sum(sim_result)}")
    print(f"       match: {match}")
    if not match:
        print("       MISMATCH!")
    print()
