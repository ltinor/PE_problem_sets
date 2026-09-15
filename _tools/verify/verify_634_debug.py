#!/usr/bin/env python3
"""Debug PE 634 algorithm."""
import math

def count_squarefree(limit):
    is_sqfree = [True] * (limit + 1)
    is_sqfree[0] = False
    for i in range(2, int(limit**0.5) + 1):
        i2 = i * i
        for j in range(i2, limit + 1, i2):
            is_sqfree[j] = False
    return [i for i in range(1, limit + 1) if is_sqfree[i]]

def mobius(limit):
    mu = [1] * (limit + 1)
    is_prime = [True] * (limit + 1)
    primes = []
    mu[0] = 0
    for i in range(2, limit + 1):
        if is_prime[i]:
            primes.append(i)
            mu[i] = -1
        for p in primes:
            if i * p > limit: break
            is_prime[i * p] = False
            if i % p == 0:
                mu[i * p] = 0
                break
            mu[i * p] = -mu[i]
    return mu

def count_not_cubefree(M):
    limit = int(M ** (1/3))
    while (limit + 1) ** 3 <= M: limit += 1
    while limit ** 3 > M: limit -= 1
    mu = mobius(limit)
    result = 0
    for k in range(1, limit + 1):
        if mu[k] == 0: continue
        result += mu[k] * (M // (k * k * k))
    return M - result

def count_prime_cubes_le(M):
    limit = int(M ** (1/3))
    while (limit + 1) ** 3 <= M: limit += 1
    while limit ** 3 > M: limit -= 1
    is_prime = [True] * (limit + 1)
    is_prime[0] = is_prime[1] = False
    for i in range(2, int(limit**0.5) + 1):
        if is_prime[i]:
            for j in range(i*i, limit + 1, i):
                is_prime[j] = False
    return sum(1 for i in range(2, limit + 1) if is_prime[i])

def F_debug(N):
    print(f"\n=== F({N}) ===")
    # Cube root
    N_cbrt = int(N ** (1/3))
    while (N_cbrt + 1) ** 3 <= N: N_cbrt += 1
    while N_cbrt ** 3 > N: N_cbrt -= 1
    print(f"N_cbrt = {N_cbrt}")
    
    sqfree = count_squarefree(N_cbrt)
    print(f"squarefree ≤ {N_cbrt}: {sqfree}")
    
    ans = 0
    for b in sqfree:
        if b == 1: continue
        b3 = b * b * b
        max_a = int(math.isqrt(N // b3))
        print(f"  b={b}: b3={b3}, N//b3={N//b3}, max_a={max_a}, add={max(0,max_a-1)}")
        if max_a >= 2:
            ans += max_a - 1
    print(f"Step 1 ans = {ans}")
    
    M = int(math.isqrt(N))
    not_cubefree = count_not_cubefree(M)
    prime_cubes = count_prime_cubes_le(M)
    print(f"Step 2: M={M}, not_cubefree={not_cubefree}, prime_cubes={prime_cubes}")
    ans += (not_cubefree - prime_cubes)
    print(f"Final ans = {ans}")
    return ans

for N in [100, 500, 1000]:
    F_debug(N)
