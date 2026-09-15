#!/usr/bin/env python3
"""PE 652: Compute D(10^18) carefully."""
from math import gcd, log2

def integer_kth_root(n, k):
    if k == 1: return n
    r = int(n ** (1.0 / k))
    while (r + 1) ** k <= n: r += 1
    while r ** k > n: r -= 1
    return r

def phi(n):
    result = n
    p = 2
    while p * p <= n:
        if n % p == 0:
            while n % p == 0: n //= p
            result -= result // p
        p += 1 if p == 2 else 2
    if n > 1: result -= result // n
    return result

def count_coprime_pairs(limit):
    cnt = 0
    for r in range(1, limit+1):
        for s in range(1, limit+1):
            if gcd(r, s) == 1: cnt += 1
    return cnt

def build_value_tree(N):
    """Collect all N^(1/e) values needed."""
    vals = {N}
    e = 2
    while True:
        x = integer_kth_root(N, e)
        if x < 2: break
        vals.add(x)
        e += 1
    # Add recursive values
    all_vals = set(vals)
    for x in list(vals):
        e = 2
        while True:
            y = integer_kth_root(x, e)
            if y < 2: break
            all_vals.add(y)
            e += 1
    return sorted(all_vals)

def compute_all_F(sorted_vals):
    F = {}
    for x in sorted_vals:
        if x < 2:
            F[x] = 0
        else:
            total = (x - 1) * (x - 1)
            e = 2
            while True:
                y = integer_kth_root(x, e)
                if y < 2: break
                total -= F[y]
                e += 1
            F[x] = total
    return F

def compute_all_cnt_npp(sorted_vals):
    cnt = {}
    for x in sorted_vals:
        if x < 2:
            cnt[x] = 0
        else:
            total = x - 1
            e = 2
            while True:
                y = integer_kth_root(x, e)
                if y < 2: break
                total -= cnt[y]
                e += 1
            cnt[x] = total
    return cnt

for N, expected in [(5,13), (10,69), (100,9607), (10000,99959605)]:
    vals = build_value_tree(N)
    F = compute_all_F(vals)
    cnt_npp = compute_all_cnt_npp(vals)
    
    max_k = int(log2(N))
    dr = count_coprime_pairs(max_k)
    rp = 0
    for k in range(1, max_k + 1):
        fk = 1 if k == 1 else 2 * phi(k)
        a = integer_kth_root(N, k)
        rp += fk * cnt_npp.get(a, 0)
    
    D = dr + F[N] - rp
    ok = "✓" if D == expected else "✗"
    print(f"D({N})={D} expected={expected} {ok} (dr={dr}, F={F[N]}, rp={rp})")

# Now compute N=10^18
print("\nComputing D(10^18)...")
N = 10**18
vals = build_value_tree(N)
print(f"  Number of distinct values: {len(vals)}")
F = compute_all_F(vals)
cnt_npp = compute_all_cnt_npp(vals)

max_k = int(log2(N))
print(f"  max_k = {max_k}")
dr = count_coprime_pairs(max_k)
print(f"  D_rat = {dr}")

rp = 0
for k in range(1, max_k + 1):
    fk = 1 if k == 1 else 2 * phi(k)
    a = integer_kth_root(N, k)
    rp += fk * cnt_npp.get(a, 0)

print(f"  F(N) = {F[N]}")
print(f"  R_prim = {rp}")
P = F[N] - rp
D = dr + P
print(f"  P = {P}")
print(f"  D(10^18) = {D}")
print(f"  Last 9 digits: {D % 10**9:09d}")
print(f"  Expected:     983358497")
