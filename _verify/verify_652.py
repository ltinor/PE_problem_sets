#!/usr/bin/env python3
"""PE 652: Consecutive Logarithms / Distinct values of proto-logarithmic function.

Equivalence: (m1,n1) ~ (m2,n2) if:
1. m1=a^e,n1=a^f, m2=b^e,n2=b^f for some a,b,e,f
2. m1=a^e,n1=b^e, m2=a^f,n2=b^f for some a,b,e,f

Each pair (m,n) has a unique primitive form (u,v) where:
- e = gcd(power-GCD(m), power-GCD(n))
- m = u^e, n = v^e
- gcd(power-GCD(u), power-GCD(v)) = 1

Equivalence classes:
- Rational: determined by reduced fraction r/s. One class per r/s.
- Irrational: determined by primitive (u,v). One class per primitive pair.

D(N) = D_rat(N) + P(N) where P = #primitive irrational pairs ≤ N.

T(N) = (N-1)^2 = Σ_{e≥1} F(N^{1/e}) where F(x) = #primitive pairs ≤ x.
F(x) = T(x) - Σ_{e≥2} F(x^{1/e}).

D(N) = D_rat(N) + F(N) - R_prim(N)
where R_prim(N) = #primitive rational pairs ≤ N.
"""

from math import gcd, isqrt

def count_coprime_pairs(limit):
    """Count pairs (r,s) with 1 ≤ r,s ≤ limit, gcd(r,s)=1."""
    cnt = 0
    for r in range(1, limit+1):
        for s in range(1, limit+1):
            if gcd(r, s) == 1:
                cnt += 1
    return cnt

def is_perfect_power(n):
    """Check if n > 1 is a perfect power (a^e with e≥2)."""
    if n < 4:
        return False
    # Check small exponents
    e = 2
    while True:
        # integer e-th root
        lo, hi = 2, n
        while lo < hi:
            mid = (lo + hi) // 2
            if mid ** e < n:
                lo = mid + 1
            else:
                hi = mid
        if lo ** e == n:
            return True
        e += 1
        if (1 << e) > n:  # 2^e > n
            break
    return False

def count_non_perfect_powers(limit):
    """Count numbers in [2, limit] that are NOT perfect powers."""
    if limit < 2:
        return 0
    cnt = 0
    for n in range(2, limit + 1):
        if not is_perfect_power(n):
            cnt += 1
    return cnt

def D_rat(N):
    """Number of rational equivalence classes representable with m,n ≤ N."""
    import math
    max_k = int(math.log2(N))
    return count_coprime_pairs(max_k)

def R_prim(N):
    """Number of primitive rational PAIRS (not classes) with a,b ≤ N."""
    import math
    total = 0
    max_k = int(math.log2(N))
    for r in range(1, max_k + 1):
        for s in range(1, max_k + 1):
            if gcd(r, s) != 1:
                continue
            max_rs = max(r, s)
            d_max = int(N ** (1.0 / max_rs))
            if d_max < 2:
                continue
            total += count_non_perfect_powers(d_max)
    return total

def compute_F(N, memo):
    """F(N) = number of primitive pairs (rational + irrational) with a,b ≤ N."""
    if N < 2:
        return 0
    if N in memo:
        return memo[N]
    
    result = (N - 1) * (N - 1)  # T(N) = (N-1)^2
    
    e = 2
    while True:
        root = int(N ** (1.0 / e))
        # Correct for floating point errors
        while (root + 1) ** e <= N:
            root += 1
        while root ** e > N:
            root -= 1
        if root < 2:
            break
        result -= compute_F(root, memo)
        e += 1
    
    memo[N] = result
    return result

def compute_D(N):
    dr = D_rat(N)
    memo = {}
    F_N = compute_F(N, memo)
    rp = R_prim(N)
    P_N = F_N - rp
    return dr + P_N

def test():
    print("PE 652: Proto-logarithmic function")
    tests = [(5, 13), (10, 69), (100, 9607), (10000, 99959605)]
    for N, expected in tests:
        result = compute_D(N)
        ok = "✓" if result == expected else "✗"
        print(f"D({N}) = {result} (expected {expected}) {ok}")

if __name__ == "__main__":
    test()
