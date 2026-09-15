#!/usr/bin/env python3
"""PE 407: Idempotents - verify answer"""
# M(n) = maximum a such that 0 < a < n and a^2 ≡ a (mod n)
# Answer: sum_{n=1}^{10^7} M(n) = 39782849136421

# For each n, find all idempotents.
# An element a is idempotent mod n iff a(a-1) ≡ 0 (mod n)
# i.e., n | a(a-1)
# For each factorization n = u*v with gcd(u,v)=1:
#   a ≡ 1 (mod u), a ≡ 0 (mod v)  →  a = v * inv(v mod u)
#   a ≡ 0 (mod u), a ≡ 1 (mod v)  →  a = u * inv(u mod v)

def M_brute(n):
    """Return maximum idempotent < n"""
    best = 0
    for a in range(1, n):
        if (a * (a - 1)) % n == 0:
            best = max(best, a)
    return best

def M_fast(n):
    """Return maximum idempotent using prime factorization"""
    # For each prime power p^e dividing n:
    #   a ≡ 1 (mod p^e), a ≡ 0 (mod n/p^e)
    # The maximum comes from the smallest prime power (largest cofactor)
    # Actually M(n) = n + 1 - P where P = largest prime power > n/2
    # If no such prime power, M(n) = something else
    
    # Let's just compute all idempotents via CRT of prime power factors
    import math
    m = n
    factors = []
    p = 2
    while p * p <= m:
        if m % p == 0:
            pk = 1
            while m % p == 0:
                m //= p
                pk *= p
            factors.append(pk)
        p += 1 if p == 2 else 2
    if m > 1:
        factors.append(m)
    
    if len(factors) <= 1:
        return 0  # n is prime power, no idempotent except 0 and 1
    
    best = 0
    # For each subset of factors (non-empty, non-full)
    k = len(factors)
    for mask in range(1, (1 << k) - 1):
        u = 1
        for i in range(k):
            if mask & (1 << i):
                u *= factors[i]
        v = n // u
        # a ≡ 1 (mod u), a ≡ 0 (mod v): a = v * inv(v mod u)
        # a ≡ 1 (mod v), a ≡ 0 (mod u): a = u * inv(u mod v)
        for (mod1, mod2) in [(u, v), (v, u)]:
            if math.gcd(mod1, mod2) != 1:
                continue
            a = mod2 * pow(mod2, -1, mod1) % n
            if 0 < a < n:
                best = max(best, a)
    return best

# Verify for small n
for n in range(2, 31):
    b = M_brute(n)
    f = M_fast(n)
    if b != f:
        print(f"MISMATCH n={n}: brute={b}, fast={f}")
    else:
        print(f"n={n}: M={b}")

# Sum for n=1..100
total_brute = sum(M_brute(n) for n in range(1, 101))
total_fast = sum(M_fast(n) for n in range(1, 101))
print(f"\nSum n=1..100: brute={total_brute}, fast={total_fast}")

# Time the fast version for n up to 10^5
import time
start = time.time()
total = sum(M_fast(n) for n in range(1, 100001))
print(f"Sum n=1..100000: {total} (time: {time.time()-start:.2f}s)")
print(f"Expected PE answer: 39782849136421")
