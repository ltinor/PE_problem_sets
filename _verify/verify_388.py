#!/usr/bin/env python3
"""PE 388: Distinct Lines in 3D
D(N) = number of distinct lines from origin to lattice points (a,b,c), 0<=a,b,c<=N
D(N) = sum_{d=1}^N mu(d) * (floor(N/d) + 1)^3
"""
import sys
import math

def mobius_sieve(n):
    """Compute Möbius function for 1..n"""
    mu = [1] * (n + 1)
    is_prime = [True] * (n + 1)
    primes = []
    mu[0] = 0
    
    for i in range(2, n + 1):
        if is_prime[i]:
            primes.append(i)
            mu[i] = -1
        for p in primes:
            if i * p > n:
                break
            is_prime[i * p] = False
            if i % p == 0:
                mu[i * p] = 0
                break
            mu[i * p] = -mu[i]
    
    return mu

def D(N):
    """Compute D(N) using Möbius inversion
    D(N) = sum_{d=1}^N mu(d) * ((floor(N/d)+1)^3 - 1)
    Exclude origin (0,0,0) which has gcd=0, not 1.
    """
    mu = mobius_sieve(N)
    total = 0
    for d in range(1, N + 1):
        if mu[d] != 0:
            k = N // d
            total += mu[d] * ((k + 1) ** 3 - 1)
    return total

def D_fast(N):
    """Compute D(N) using Dirichlet hyperbola method for large N"""
    # For large N, use the formula:
    # D(N) = sum_{d=1}^N mu(d) * floor((N/d+1)^3)
    # We need prefix sums of mu: M(n) = sum_{i=1}^n mu(i)
    # Using the identity: sum mu(i) * floor(n/i) = 1
    # M(n) = 1 - sum_{i=2}^n M(floor(n/i))
    
    import math
    sqrt_N = int(math.isqrt(N))
    
    # Precompute mu for small values
    L = int(N ** (2/3))  # threshold
    L = max(L, sqrt_N)
    
    mu_small = [0] * (L + 1)
    mu_small[1] = 1
    is_prime = [True] * (L + 1)
    primes = []
    
    for i in range(2, L + 1):
        if is_prime[i]:
            primes.append(i)
            mu_small[i] = -1
        for p in primes:
            if i * p > L:
                break
            is_prime[i * p] = False
            if i % p == 0:
                mu_small[i * p] = 0
                break
            mu_small[i * p] = -mu_small[i]
    
    # Prefix sum of mu for small values
    M_small = [0] * (L + 1)
    for i in range(1, L + 1):
        M_small[i] = M_small[i-1] + mu_small[i]
    
    # Memoization for M(n)
    M_cache = {}
    
    def M(n):
        if n <= L:
            return M_small[n]
        if n in M_cache:
            return M_cache[n]
        
        res = 1
        i = 2
        while i <= n:
            q = n // i
            j = n // q
            res -= (j - i + 1) * M(q)
            i = j + 1
        M_cache[n] = res
        return res
    
    # Now compute D(N) = sum_{d=1}^N mu(d) * ((floor(N/d)+1)^3 - 1)
    # Using block division: group by floor(N/d)
    total = 0
    i = 1
    while i <= N:
        q = N // i
        j = N // q  # last index with same floor(N/d)
        # sum mu(d) for d in [i, j]
        total += (M(j) - M(i-1)) * ((q + 1) ** 3 - 1)
        i = j + 1
    
    return total

if __name__ == '__main__':
    print("Testing PE 388...")
    
    # Small tests
    for N in [1, 2, 3, 5, 10]:
        print(f"D({N}) = {D(N)}")
    
    # Verify: D(1,000,000) = 831909254469114121
    N = 1_000_000
    result = D(N)
    print(f"D({N}) = {result}")
    expected = 831909254469114121
    print(f"Expected: {expected}")
    assert result == expected, f"Mismatch: {result} vs {expected}"
    
    # Test D_fast on a moderate size
    print(f"\nD_fast(1,000,000) = {D_fast(1_000_000)}")
    
    print("Tests passed!")
