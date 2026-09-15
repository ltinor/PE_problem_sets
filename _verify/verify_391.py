#!/usr/bin/env python3
"""PE 391: Hopping Game - final version for n=1000"""
import sys

def popcount(x):
    return bin(x).count('1')

def solve(N):
    S_bound = N * 400 + 100000
    S = [0]
    k = 1
    while S[-1] <= S_bound:
        S.append(S[-1] + popcount(k))
        k += 1
    m = len(S)
    print(f"S: {m} values, max={S[-1]}, bound={S_bound}", flush=True)
    
    total = 0
    
    for n in range(1, N + 1):
        next_lose = float('inf')
        M = 0
        
        for i in range(m - 1, -1, -1):
            p = S[i]
            if next_lose - p > n:
                if p <= n and p > M:
                    M = p
                next_lose = p
        
        total += M * M * M
        
        if n % 100 == 0:
            print(f"  n={n}: M={M}, total so far={total}", flush=True)
    
    return total

if __name__ == '__main__':
    print("Computing PE 391 for N=1000...", flush=True)
    result = solve(1000)
    print(f"\nSum M(n)^3 for n=1..1000: {result}")
    print(f"Expected: 61029882288")
    assert result == 61029882288, f"Got {result}, expected 61029882288"
    print("PASSED!")
