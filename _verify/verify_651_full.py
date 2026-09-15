#!/usr/bin/env python3
"""PE 651: Compute Σ_{i=4}^{40} f(i, F_{i-1}, F_i) mod 1e9+7."""

import math
from math import gcd

MOD = 1000000007

def get_divisors(n):
    divs = []
    for d in range(1, int(n**0.5) + 1):
        if n % d == 0:
            divs.append(d)
            if d * d != n:
                divs.append(n // d)
    return sorted(divs)

def phi(n):
    result = n
    p = 2
    while p * p <= n:
        if n % p == 0:
            while n % p == 0:
                n //= p
            result -= result // p
        p += 1 if p == 2 else 2
    if n > 1:
        result -= result // n
    return result

def factorize(n):
    """Return dict of prime -> exponent."""
    factors = {}
    d = 2
    while d * d <= n:
        while n % d == 0:
            factors[d] = factors.get(d, 0) + 1
            n //= d
        d += 1 if d == 2 else 2
    if n > 1:
        factors[n] = 1
    return factors

def get_divisors_from_factors(factors):
    """Generate all divisors from prime factorization."""
    divs = [1]
    for p, e in factors.items():
        new_divs = []
        pe = 1
        for _ in range(e + 1):
            for d in divs:
                new_divs.append(d * pe)
            pe *= p
        divs = new_divs
    return sorted(divs)

def phi_from_factors(factors):
    """Compute phi from prime factorization."""
    result = 1
    for p, e in factors.items():
        result *= (p - 1) * (p ** (e - 1))
    return result

def mod_pow(base, exp, mod=MOD):
    if exp < 0:
        return 0
    result = 1
    base %= mod
    while exp:
        if exp & 1:
            result = (result * base) % mod
        base = (base * base) % mod
        exp >>= 1
    return result

def nCr_mod(n, r, mod=MOD):
    if r < 0 or r > n:
        return 0
    if r > n - r:
        r = n - r
    num = 1
    den = 1
    for i in range(r):
        num = (num * (n - i)) % mod
        den = (den * (i + 1)) % mod
    return (num * mod_pow(den, mod - 2, mod)) % mod

def colorings_formula(k, a, b, divs_a, divs_b, phi_cache):
    """Number of colorings with ≤k colors. Group = D_a × D_b."""
    inv_den = mod_pow(4 * a * b, MOD - 2)
    
    total = 0
    a_odd = (a % 2 == 1)
    b_odd = (b % 2 == 1)
    
    # Type 1: (rot, rot)
    type1 = 0
    for da in divs_a:
        phi_a = phi_cache.get((a, da))
        if phi_a is None:
            phi_a = phi(a // da)
        ad = a // da
        for db in divs_b:
            phi_b = phi_cache.get((b, db))
            if phi_b is None:
                phi_b = phi(b // db)
            bd = b // db
            g = gcd(ad, bd)
            exp = da * db * g
            type1 = (type1 + phi_a * phi_b % MOD * mod_pow(k, exp)) % MOD
    total = (total + type1) % MOD
    
    # Type 2: (rot, ref)
    type2 = 0
    for da in divs_a:
        phi_a = phi_cache.get((a, da))
        if phi_a is None:
            phi_a = phi(a // da)
        g2 = 2 if ((a // da) % 2 == 0) else 1
        
        if b_odd:
            exp = da * (1 + (b - 1) // 2 * g2)
            type2 = (type2 + phi_a * b % MOD * mod_pow(k, exp)) % MOD
        else:
            exp_even = da * (2 + (b - 2) // 2 * g2)
            exp_odd = da * (b // 2 * g2)
            contrib = (mod_pow(k, exp_even) + mod_pow(k, exp_odd)) % MOD
            type2 = (type2 + phi_a * (b // 2) % MOD * contrib) % MOD
    total = (total + type2) % MOD
    
    # Type 3: (ref, rot)
    type3 = 0
    for db in divs_b:
        phi_b = phi_cache.get((b, db))
        if phi_b is None:
            phi_b = phi(b // db)
        g2 = 2 if ((b // db) % 2 == 0) else 1
        
        if a_odd:
            exp = db * (1 + (a - 1) // 2 * g2)
            type3 = (type3 + phi_b * a % MOD * mod_pow(k, exp)) % MOD
        else:
            exp_even = db * (2 + (a - 2) // 2 * g2)
            exp_odd = db * (a // 2 * g2)
            contrib = (mod_pow(k, exp_even) + mod_pow(k, exp_odd)) % MOD
            type3 = (type3 + phi_b * (a // 2) % MOD * contrib) % MOD
    total = (total + type3) % MOD
    
    # Type 4: (ref, ref)
    type4 = 0
    if a_odd and b_odd:
        exp = (a * b + 1) // 2
        type4 = a * b % MOD * mod_pow(k, exp) % MOD
    elif a_odd and not b_odd:
        exp2 = a * b // 2 + 1
        exp0 = a * b // 2
        contrib = (mod_pow(k, exp2) + mod_pow(k, exp0)) % MOD
        type4 = a * (b // 2) % MOD * contrib % MOD
    elif not a_odd and b_odd:
        exp2 = a * b // 2 + 1
        exp0 = a * b // 2
        contrib = (mod_pow(k, exp2) + mod_pow(k, exp0)) % MOD
        type4 = (a // 2) * b % MOD * contrib % MOD
    else:
        exp22 = (a * b + 4) // 2
        exp20 = (a * b) // 2
        half = (a // 2) * (b // 2) % MOD
        contrib = (mod_pow(k, exp22) + 3 * mod_pow(k, exp20)) % MOD
        type4 = half * contrib % MOD
    total = (total + type4) % MOD
    
    return total * inv_den % MOD

def compute_f(m, a, b, divs_a, divs_b, phi_cache):
    """Compute f(m,a,b) using inclusion-exclusion."""
    result = 0
    for k in range(m + 1):
        col = colorings_formula(k, a, b, divs_a, divs_b, phi_cache)
        term = nCr_mod(m, k) * col % MOD
        if (m - k) % 2 == 1:
            result = (result - term + MOD) % MOD
        else:
            result = (result + term) % MOD
    return result

def solve():
    fib = [0, 1]
    for i in range(2, 42):
        fib.append(fib[-1] + fib[-2])
    
    total = 0
    phi_cache = {}
    
    for i in range(4, 41):
        a = fib[i-1]
        b = fib[i]
        print(f"i={i}, a=F_{i-1}={a}, b=F_{i}={b}")
        
        fa = factorize(a)
        fb = factorize(b)
        divs_a = get_divisors_from_factors(fa)
        divs_b = get_divisors_from_factors(fb)
        
        f_val = compute_f(i, a, b, divs_a, divs_b, phi_cache)
        total = (total + f_val) % MOD
        print(f"  f({i},{a},{b}) = {f_val}")
    
    print(f"\nAnswer: {total}")
    return total

if __name__ == "__main__":
    solve()
