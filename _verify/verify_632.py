#!/usr/bin/env python3
"""PE 632: Verify C_k for small N to debug algorithm."""
import math

def compute_Ck(N, max_k=8):
    """Compute C_k(N) for all k using inclusion-exclusion."""
    # Get primes up to sqrt(N)
    limit = int(math.isqrt(N))
    pr = []
    is_prime = [True] * (limit + 1)
    is_prime[0] = is_prime[1] = False
    for i in range(2, limit + 1):
        if is_prime[i]:
            pr.append(i)
            for j in range(i*i, limit + 1, i):
                is_prime[j] = False
    
    P = len(pr)
    
    # T[j] = sum over j-tuples of floor(N / (p1*...*pj)^2)
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
        if max_q < pr[i+1] if i+1 < P else float('inf'):
            pass
        if max_q < (pr[i+1] if i+1 < P else limit+1):
            continue
        p2 = p * p
        for j in range(i+1, P):
            q = pr[j]
            if q > max_q: break
            prod2 = p2 * q * q
            if prod2 > N: break
            T[2] += N // prod2
    
    # T[3..8] recursive: only add when we reach the target depth
    def dfs(idx, depth, prod, target):
        nonlocal P
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

# Test with N from problem table
for N_pow in range(1, 9):
    N = 10 ** N_pow
    Ck = compute_Ck(N, 5)
    print(f"N=10^{N_pow}: C0={Ck[0]}, C1={Ck[1]}, C2={Ck[2]}, C3={Ck[3]}, C4={Ck[4]}, C5={Ck[5]}")

# Expected from table:
expected = {
    1: [7, 3, 0, 0, 0, 0],
    2: [61, 36, 3, 0, 0, 0],
    3: [608, 343, 48, 1, 0, 0],
    4: [6083, 3363, 533, 21, 0, 0],
    5: [60794, 33562, 5345, 297, 2, 0],
    6: [607926, 335438, 53358, 3218, 60, 0],
    7: [6079291, 3353956, 533140, 32777, 834, 2],
    8: [60792694, 33539196, 5329747, 329028, 9257, 78],
}

print("\nChecking against table:")
for N_pow in range(1, 9):
    N = 10 ** N_pow
    Ck = compute_Ck(N, 5)
    exp = expected[N_pow]
    match = all(Ck[k] == exp[k] for k in range(6))
    print(f"10^{N_pow}: {'✓' if match else '✗'} (got {Ck[:6]}, expected {exp})")
