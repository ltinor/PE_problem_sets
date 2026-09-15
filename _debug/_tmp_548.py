# Systematic search for g(n) = n patterns
# Using the formula: g(1)=1, g(n) = sum_{d|n, d<n} g(d)
# For prime powers: g(p^e) = 2^{e-1}

from collections import Counter

# Compute g for all n up to limit
def compute_g_sieve(limit):
    g = [0] * (limit + 1)
    g[1] = 1
    for n in range(2, limit + 1):
        total = 0
        # iterate over divisors
        d = 1
        while d * d <= n:
            if n % d == 0:
                total += g[d]
                other = n // d
                if other != d and other < n:
                    total += g[other]
            d += 1
        g[n] = total
    return g

g = compute_g_sieve(500000)
solutions = [(n, g[n]) for n in range(2, 500001) if g[n] == n]
print(f'Found {len(solutions)} solutions up to 500000')
for n, val in solutions[:20]:
    factors = []
    m = n
    p = 2
    while p * p <= m:
        while m % p == 0:
            factors.append(p)
            m //= p
        p += 1
    if m > 1:
        factors.append(m)
    c = Counter(factors)
    print(f'n={n:>10}, factors={dict(c)}')

# Check the family 2^{4k} * p_k where p_k is k-th odd prime
print("\nFamily check: 2^{4k} * p (p odd prime)")
odd_primes = [3,5,7,11,13,17,19,23,29,31,37,41,43,47]
for k, p in enumerate(odd_primes, 1):
    n = (2 ** (4*k)) * p
    if n <= 500000:
        print(f'k={k}: n=2^{4*k}*{p}={n}, g={g[n] if n <= 500000 else "N/A"}, match={g[n]==n if n <= 500000 else "N/A"}')

# Check if g(2^a * p) = 2^a * p has solutions
print("\nCheck: 2^e * p solutions")
import math
for e in range(1, 21):
    for p in [3,5,7,11,13,17,19,23,29,31,37]:
        n = (1 << e) * p
        if n <= 500000 and g[n] == n:
            print(f'  2^{e} * {p} = {n}')

# Check: 2^a * 3^b * p solutions
print("\nCheck: 2^a * 3^b * p")
for a in range(1, 16):
    for b in range(1, 8):
        for p in odd_primes:
            n = (1 << a) * (3 ** b) * p
            if n <= 500000 and g[n] == n:
                print(f'  2^{a} * 3^{b} * {p} = {n}')
