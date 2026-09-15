#!/usr/bin/env python3
"""Compute PE 256-275 answers using Python, then write C++ implementations."""
import math, itertools
from collections import defaultdict

results = {}

# PE 269: Polynomials with integer roots
# Count n <= 10^16 where P_n has integer root
# P_n(r)=0 => sum_{i} d_i * r^i = 0
# r=0 => last digit = 0
# r=-1 => alternating digit sum = 0
# For higher |r|: digit DP

def count_269(N_str):
    """Count n in [1, N] where P_n has integer root."""
    L = len(N_str)
    # r=0: numbers ending in 0
    r0_count = int(N_str) // 10
    
    # r=-1: alternating sum = 0
    # DP[pos][diff+offset][tight]
    off = 9 * L
    dp = [[[0]*2 for _ in range(2*off+1)] for _ in range(L+1)]
    dp[0][off][1] = 1
    for pos in range(L):
        dig = int(N_str[pos])
        for d in range(2*off+1):
            for tight in range(2):
                if dp[pos][d][tight] == 0:
                    continue
                mx = dig if tight else 9
                for x in range(mx + 1):
                    nt = 1 if (tight and x == mx) else 0
                    sign = 1 if (L-1-pos) % 2 == 0 else -1
                    nd = d + sign * x
                    dp[pos+1][nd][nt] += dp[pos][d][tight]
    r_neg1 = dp[L][off][0] + dp[L][off][1] - 1  # exclude 0
    
    # r=±2 to ±10: digit DP tracking polynomial value
    def count_for_r(r):
        if r == 0:
            return 0
        # P_n(r) = sum d_i * r^i
        # For small r, compute max possible value
        max_val = 0
        p = 1
        for i in range(L):
            max_val += 9 * p
            p *= abs(r)
        
        off2 = max_val + 1
        dp2 = [[[0]*2 for _ in range(2*off2+1)] for _ in range(L+1)]
        dp2[0][off2][1] = 1
        for pos in range(L):
            dig = int(N_str[pos])
            for v in range(2*off2+1):
                for tight in range(2):
                    if dp2[pos][v][tight] == 0:
                        continue
                    mx = dig if tight else 9
                    for x in range(mx + 1):
                        nt = 1 if (tight and x == mx) else 0
                        # contribution: x * r^(L-1-pos)
                        contrib = x * (r ** (L-1-pos))
                        nv = v + contrib
                        if 0 <= nv <= 2*off2:
                            dp2[pos+1][nv][nt] += dp2[pos][v][tight]
        return dp2[L][off2][0] + dp2[L][off2][1] - 1  # exclude 0
    
    # Use a set to avoid double counting
    all_roots = set()
    # r=0
    all_roots.add(0)
    # r=-1
    all_roots.add(-1)
    # We need union, not sum
    # Actually we need count of n where ANY integer root exists
    # This requires inclusion-exclusion on the set of roots
    # Simpler: check all n up to some bound, find pattern
    
    # For small N, let's brute force to verify
    return 0

print(count_269("100000"))
