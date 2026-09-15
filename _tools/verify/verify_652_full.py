#!/usr/bin/env python3
"""PE 652: Compute D(10^18) last 9 digits - efficient version."""

from math import gcd, isqrt

MOD = 10**9

def integer_kth_root(n, k):
    """Floor of n^(1/k), corrected for floating point."""
    if k == 1:
        return n
    r = int(n ** (1.0 / k))
    while (r + 1) ** k <= n:
        r += 1
    while r ** k > n:
        r -= 1
    return r

def count_coprime_pairs(limit):
    """Count (r,s) with 1≤r,s≤limit, gcd(r,s)=1."""
    total = 0
    for r in range(1, limit + 1):
        for s in range(1, limit + 1):
            if gcd(r, s) == 1:
                total += 1
    return total

def compute_all_F(N):
    """Compute F(x) for all x = floor(N^(1/e))."""
    # Collect all needed values
    values = set()
    values.add(N)
    e = 2
    while True:
        x = integer_kth_root(N, e)
        if x < 2:
            break
        values.add(x)
        e += 1
    
    # Also need values for the recursion: need F(y) for y = floor(x^(1/e)) for all x in values
    all_vals = set(values)
    for x in list(values):
        e = 2
        while True:
            y = integer_kth_root(x, e)
            if y < 2:
                break
            all_vals.add(y)
            e += 1
    
    sorted_vals = sorted(all_vals)
    
    # Compute F for each value bottom-up
    F = {}
    for x in sorted_vals:
        if x < 2:
            F[x] = 0
        else:
            total = (x - 1) * (x - 1)
            e = 2
            while True:
                y = integer_kth_root(x, e)
                if y < 2:
                    break
                total -= F[y]
                e += 1
            F[x] = total
    
    return F

def compute_cnt_npp(N, memo_npp):
    """Count non-perfect-powers in [2, N]."""
    if N < 2:
        return 0
    if N in memo_npp:
        return memo_npp[N]
    
    # Count perfect powers for subtraction
    cnt_pp = 0
    e = 2
    while True:
        root = integer_kth_root(N, e)
        if root < 2:
            break
        cnt_pp += compute_cnt_npp(root, memo_npp)  # only count if base is not a perfect power
        e += 1
    
    result = (N - 1) - cnt_pp
    memo_npp[N] = result
    return result

def pairs_with_max_k(k):
    """Count coprime ordered pairs (r,s) with max(r,s)=k."""
    if k == 1:
        return 1  # (1,1)
    cnt = 0
    for s in range(1, k):
        if gcd(k, s) == 1:
            cnt += 1
    for r in range(1, k):
        if gcd(r, k) == 1:
            cnt += 1
    return cnt

def compute_D(N):
    import math
    max_k = int(math.log2(N))
    
    # D_rat
    dr = count_coprime_pairs(max_k)
    
    # F(N)
    F = compute_all_F(N)
    
    # R_prim(N)
    memo_npp = {}
    rp = 0
    for k in range(1, max_k + 1):
        d_max = integer_kth_root(N, k)
        if d_max < 2:
            continue
        cnt_pairs = pairs_with_max_k(k)
        cnt_npp = compute_cnt_npp(d_max, memo_npp)
        rp += cnt_pairs * cnt_npp
    
    P_N = F[N] - rp
    return dr + P_N

if __name__ == "__main__":
    # Quick verification
    for N_test, expected in [(5, 13), (10, 69), (100, 9607)]:
        result = compute_D(N_test)
        ok = "✓" if result == expected else "✗"
        print(f"D({N_test}) = {result} (expected {expected}) {ok}")
    
    print("\nComputing D(10^18)...")
    N = 10**18
    result = compute_D(N)
    print(f"D(10^18) = {result}")
    print(f"Last 9 digits: {result % 10**9:09d}")
