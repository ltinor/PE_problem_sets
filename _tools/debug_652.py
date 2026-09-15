#!/usr/bin/env python3
"""PE 652: Debug D(100) computation."""

from math import gcd, isqrt, log2

def count_coprime_pairs(limit):
    cnt = 0
    for r in range(1, limit+1):
        for s in range(1, limit+1):
            if gcd(r, s) == 1:
                cnt += 1
    return cnt

def integer_kth_root(n, k):
    if k == 1: return n
    r = int(n ** (1.0 / k))
    while (r + 1) ** k <= n: r += 1
    while r ** k > n: r -= 1
    return r

def compute_F_vals(N):
    vals = set()
    vals.add(N)
    e = 2
    while True:
        x = integer_kth_root(N, e)
        if x < 2: break
        vals.add(x)
        e += 1
    
    all_vals = set(vals)
    for x in list(vals):
        e = 2
        while True:
            y = integer_kth_root(x, e)
            if y < 2: break
            all_vals.add(y)
            e += 1
    
    F = {}
    for x in sorted(all_vals):
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

def compute_cnt_npp_vals(max_val):
    vals = set()
    vals.add(max_val)
    e = 2
    while True:
        x = integer_kth_root(max_val, e)
        if x < 2: break
        vals.add(x)
        e += 1
    
    all_vals = set(vals)
    for x in list(vals):
        e = 2
        while True:
            y = integer_kth_root(x, e)
            if y < 2: break
            all_vals.add(y)
            e += 1
    
    cnt = {}
    for x in sorted(all_vals):
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

def compute_D(N):
    max_k = int(log2(N))
    dr = count_coprime_pairs(max_k)
    
    F = compute_F_vals(N)
    A_vals = {}
    for k in range(1, max_k + 1):
        A_vals[k] = integer_kth_root(N, k)
    
    max_A = max(A_vals.values())
    cnt_npp = compute_cnt_npp_vals(max_A)
    
    rp = 0
    for k in range(1, max_k + 1):
        if k == 1:
            fk = 1
        else:
            fk = 2 * phi(k)
        a = A_vals[k]
        rp += fk * cnt_npp.get(a, 0)
    
    P = F[N] - rp
    D = dr + P
    return D, dr, F[N], rp, P

# Test
print("N=5:", compute_D(5)[0])
print("N=10:", compute_D(10)[0])
print("N=100:")
D, dr, Fn, rp, P = compute_D(100)
print(f"  D_rat={dr}, F(N)={Fn}, R_prim={rp}, P={P}, D={D}")
print(f"  Expected D(100)=9607")
print(f"  Difference: {D - 9607}")

# Also compute D(100) using the original method from verify_652.py
from verify_652 import compute_D as compute_D_orig
print(f"\nOriginal method D(100)={compute_D_orig(100)}")
