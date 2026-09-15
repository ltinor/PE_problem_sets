#!/usr/bin/env python3
"""PE 634: Count distinct numbers of form a^2*b^3 with a,b >= 2, up to N.
Algorithm:
1. For each squarefree b >= 2 up to N^(1/3): count a >= 2 with a^2*b^3 <= N
   (These are all in the unique representation a^2*b^3 with b squarefree)
2. Add squares a^2 (a >= 2) where a is not cube-free AND a != p^3 for prime p
   (These cannot be represented with b>=2 in unique rep, but have alt rep with a,b>=2)
"""
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
    """Count numbers a in [1, M] that are NOT cube-free (divisible by some cube >= 8)."""
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
    """Count primes p such that p^3 <= M."""
    limit = int(M ** (1/3))
    while (limit + 1) ** 3 <= M: limit += 1
    while limit ** 3 > M: limit -= 1
    if limit < 2: return 0
    is_prime = [True] * (limit + 1)
    is_prime[0] = is_prime[1] = False
    for i in range(2, int(limit**0.5) + 1):
        if is_prime[i]:
            for j in range(i*i, limit + 1, i):
                is_prime[j] = False
    return sum(1 for i in range(2, limit + 1) if is_prime[i])

def F(N):
    N_cbrt = int(N ** (1/3))
    while (N_cbrt + 1) ** 3 <= N: N_cbrt += 1
    while N_cbrt ** 3 > N: N_cbrt -= 1
    
    sqfree = count_squarefree(N_cbrt)
    ans = 0
    for b in sqfree:
        if b == 1: continue
        b3 = b * b * b
        max_a = int(math.isqrt(N // b3))
        if max_a >= 2:
            ans += max_a - 1
    
    M = int(math.isqrt(N))
    not_cubefree = count_not_cubefree(M)
    prime_cubes = count_prime_cubes_le(M)
    ans += (not_cubefree - prime_cubes)
    
    return ans

# Verify against known values
print("Verification against problem statement:")
print(f"F(100) = {F(100)} (expected 2)")
print(f"F(20000) = {F(20000)} (expected 130)")
print(f"F(3000000) = {F(3000000)} (expected 2014)")

# Brute force verification for small N
def brute_F(N):
    s = set()
    max_a = int(math.isqrt(N // 8))
    for a in range(2, max_a + 1):
        a2 = a * a
        max_b = int(round((N // a2) ** (1/3)))
        while (max_b + 1) ** 3 * a2 <= N: max_b += 1
        while max_b >= 2 and max_b ** 3 * a2 > N: max_b -= 1
        for b in range(2, max_b + 1):
            s.add(a2 * b * b * b)
    return len(s)

print("\nBrute force check (small N):")
all_ok = True
for N in [100, 500, 1000, 2000, 5000]:
    f = F(N)
    b = brute_F(N)
    ok = f == b
    print(f"F({N}) = {f}, brute = {b} {'✓' if ok else '✗'}")
    if not ok: all_ok = False

if all_ok:
    print("\nAll checks passed! Computing F(9e18)...")
    N = 9 * 10**18
    result = F(N)
    print(f"F(9×10^18) = {result}")
    print(f"Expected: 4019680944")
    print(f"Match: {result == 4019680944}")
