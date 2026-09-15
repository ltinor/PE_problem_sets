#!/usr/bin/env python3
"""PE 632: Compute C_k(10^16) and product of non-zero ones mod 1e9+7."""
import math

def compute_Ck(N, max_k=8):
    limit = int(math.isqrt(N))
    # Generate primes up to sqrt(N) = 10^8
    import sys
    # Use segmented sieve for 10^8
    pr = []
    M = limit
    is_prime = bytearray(b'\x01') * (M + 1)
    is_prime[0:2] = b'\x00\x00'
    for i in range(2, int(M**0.5) + 1):
        if is_prime[i]:
            step = i
            start = i * i
            is_prime[start:M+1:step] = b'\x00' * ((M - start) // step + 1)
    pr = [i for i in range(2, M+1) if is_prime[i]]
    print(f"Generated {len(pr)} primes up to {M}", file=sys.stderr)
    
    P = len(pr)
    T = [0] * (max_k + 1)
    T[0] = N
    
    # T[1]
    for i in range(P):
        p = pr[i]
        p2 = p * p
        if p2 > N: break
        T[1] += N // p2
    
    # T[2]
    for i in range(P):
        p = pr[i]
        max_q = limit // p
        if i+1 < P and pr[i+1] > max_q:
            continue
        p2 = p * p
        for j in range(i+1, P):
            q = pr[j]
            if q > max_q: break
            prod2 = p2 * q * q
            if prod2 > N: break
            T[2] += N // prod2
    
    # T[3..8]
    def dfs(idx, depth, prod, target):
        if depth == target:
            np2 = prod * prod
            if np2 <= N:
                T[target] += N // np2
            return
        for i in range(idx, P):
            p = pr[i]
            if p > limit // prod: break
            new_prod = prod * p
            np2 = new_prod * new_prod
            if np2 > N: break
            dfs(i+1, depth+1, new_prod, target)
    
    for target in range(3, max_k+1):
        dfs(0, 0, 1, target)
    
    # C_k via inclusion-exclusion
    from math import comb
    Ck = [0] * (max_k + 1)
    for k in range(max_k + 1):
        val = 0
        for j in range(k, max_k + 1):
            term = comb(j, k) * T[j]
            if (j - k) % 2 == 1:
                val -= term
            else:
                val += term
        Ck[k] = val
    
    return Ck

if __name__ == '__main__':
    N = 10**16
    print(f"Computing C_k(10^16)...")
    Ck = compute_Ck(N, 8)
    print(f"C_k values:")
    prod = 1
    MOD = 1000000007
    for k in range(9):
        print(f"  C_{k} = {Ck[k]}")
        if Ck[k] > 0:
            prod = (prod * (Ck[k] % MOD)) % MOD
    print(f"\nProduct of non-zero C_k mod {MOD}: {prod}")
    print(f"Expected: 728378714")
