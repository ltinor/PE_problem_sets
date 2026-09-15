#!/usr/bin/env python3
"""PE 651: Patterned Cylinders - verify Burnside formula.

Group G = D_a × D_b acting on Z_a × Z_b (torus).
|G| = 4ab.

4 types of group elements:
1. (rot, rot): (x,y) → (x+t, y+s) — ab elements
2. (rot, ref): (x,y) → (x+t, -y+s) — ab elements
3. (ref, rot): (x,y) → (-x+t, y+s) — ab elements
4. (ref, ref): (x,y) → (-x+t, -y+s) — ab elements

n_x(t) = #solutions to 2x≡t (mod a)
n_y(s) = #solutions to 2y≡s (mod b)
"""

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

def mod_pow(base, exp, mod=MOD):
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

def colorings_formula(k, a, b):
    """Number of colorings with ≤k colors. Group = D_a × D_b."""
    inv_den = mod_pow(4 * a * b, MOD - 2)
    divs_a = get_divisors(a)
    divs_b = get_divisors(b)
    
    total = 0
    
    # Type 1: (rot, rot) — (x,y) → (x+t, y+s)
    type1 = 0
    for da in divs_a:
        phi_a = phi(a // da)
        for db in divs_b:
            phi_b = phi(b // db)
            g = gcd(a // da, b // db)
            exp = da * db * g
            type1 = (type1 + phi_a * phi_b % MOD * mod_pow(k, exp)) % MOD
    total = (total + type1) % MOD
    
    # Type 2: (rot, ref) — (x,y) → (x+t, -y+s)
    # c_2 = gcd(a,t) * [n_y + (b-n_y)/2 * gcd(a/gcd(a,t), 2)]
    type2 = 0
    a_odd = (a % 2 == 1)
    b_odd = (b % 2 == 1)
    for da in divs_a:
        phi_a = phi(a // da)
        g2 = 2 if ((a // da) % 2 == 0) else 1  # gcd(a/da, 2)
        
        if b_odd:
            # n_y = 1 for all s
            # c_2 = da * [1 + (b-1)/2 * g2]
            exp = da * (1 + (b - 1) // 2 * g2)
            type2 = (type2 + phi_a * b % MOD * mod_pow(k, exp)) % MOD
        else:
            # b even: s even -> n_y=2, s odd -> n_y=0
            exp_even = da * (2 + (b - 2) // 2 * g2)
            exp_odd = da * (b // 2 * g2)
            contrib = (mod_pow(k, exp_even) + mod_pow(k, exp_odd)) % MOD
            type2 = (type2 + phi_a * (b // 2) % MOD * contrib) % MOD
    total = (total + type2) % MOD
    
    # Type 3: (ref, rot) — (x,y) → (-x+t, y+s)
    # c_3 = n_x * [gcd(b,s) + (a-n_x)/2 * gcd(b,s) * gcd(2, b/gcd(b,s))]
    # = gcd(b,s) * [n_x + (a-n_x)/2 * gcd(2, b/gcd(b,s))]
    type3 = 0
    for db in divs_b:
        phi_b = phi(b // db)
        g2 = 2 if ((b // db) % 2 == 0) else 1  # gcd(b/db, 2)
        
        if a_odd:
            # n_x = 1 for all t
            exp = db * (1 + (a - 1) // 2 * g2)
            type3 = (type3 + phi_b * a % MOD * mod_pow(k, exp)) % MOD
        else:
            # a even: t even -> n_x=2, t odd -> n_x=0
            exp_even = db * (2 + (a - 2) // 2 * g2)
            exp_odd = db * (a // 2 * g2)
            contrib = (mod_pow(k, exp_even) + mod_pow(k, exp_odd)) % MOD
            type3 = (type3 + phi_b * (a // 2) % MOD * contrib) % MOD
    total = (total + type3) % MOD
    
    # Type 4: (ref, ref) — (x,y) → (-x+t, -y+s)
    # c_4 = (ab + n_x*n_y) / 2
    type4 = 0
    
    # Sum over t,s of k^{c_4(t,s)}
    # n_x depends on t, n_y depends on s
    # n_x ∈ {0,1,2}, n_y ∈ {0,1,2}
    
    if a_odd and b_odd:
        # n_x=1 for all t, n_y=1 for all s
        exp = (a * b + 1) // 2
        type4 = a * b * mod_pow(k, exp) % MOD
    elif a_odd and not b_odd:
        # n_x=1 for all a t's
        # n_y: b/2 s even -> n_y=2, b/2 s odd -> n_y=0
        # For n_y=2: c_4 = (ab+2)/2 = ab/2 + 1
        # For n_y=0: c_4 = ab/2
        exp2 = a * b // 2 + 1  # n_x*n_y = 1*2 = 2
        exp0 = a * b // 2      # n_x*n_y = 1*0 = 0
        contrib = (mod_pow(k, exp2) + mod_pow(k, exp0)) % MOD
        type4 = a * (b // 2) % MOD * contrib % MOD
    elif not a_odd and b_odd:
        # n_x: a/2 t even -> n_x=2, a/2 t odd -> n_x=0
        # n_y=1 for all s
        exp2 = a * b // 2 + 1
        exp0 = a * b // 2
        contrib = (mod_pow(k, exp2) + mod_pow(k, exp0)) % MOD
        type4 = (a // 2) * b % MOD * contrib % MOD
    else:
        # a even, b even
        # t even (a/2), t odd (a/2); s even (b/2), s odd (b/2)
        # (n_x, n_y) pairs: (2,2), (2,0), (0,2), (0,0)
        # each combo has (a/2)*(b/2) elements
        exp22 = (a * b + 4) // 2   # n_x*n_y = 4
        exp20 = (a * b + 0) // 2   # n_x*n_y = 0
        exp02 = (a * b + 0) // 2   # same
        exp00 = (a * b + 0) // 2   # same
        
        half = (a // 2) * (b // 2) % MOD
        contrib = (mod_pow(k, exp22) + 3 * mod_pow(k, exp20)) % MOD
        type4 = half * contrib % MOD
    
    total = (total + type4) % MOD
    return total * inv_den % MOD


def compute_f(m, a, b):
    """Compute f(m,a,b) using inclusion-exclusion."""
    result = 0
    for k in range(m + 1):
        col = colorings_formula(k, a, b)
        term = nCr_mod(m, k) * col % MOD
        if (m - k) % 2 == 1:
            result = (result - term + MOD) % MOD
        else:
            result = (result + term) % MOD
    return result


def colorings_brute(m, a, b):
    """Brute force Burnside for small a,b."""
    from itertools import product
    cells = list(product(range(a), range(b)))
    actions = []
    # Type 1: (rot, rot)
    for t in range(a):
        for s in range(b):
            actions.append([((x+t)%a, (y+s)%b) for x,y in cells])
    # Type 2: (rot, ref)
    for t in range(a):
        for s in range(b):
            actions.append([((x+t)%a, (-y+s)%b) for x,y in cells])
    # Type 3: (ref, rot)
    for t in range(a):
        for s in range(b):
            actions.append([((-x+t)%a, (y+s)%b) for x,y in cells])
    # Type 4: (ref, ref)
    for t in range(a):
        for s in range(b):
            actions.append([((-x+t)%a, (-y+s)%b) for x,y in cells])
    
    total = 0
    for perm in actions:
        visited = [False] * len(cells)
        cycles = 0
        for i in range(len(cells)):
            if not visited[i]:
                cycles += 1
                j = i
                while not visited[j]:
                    visited[j] = True
                    j = cells.index(perm[j])
        total = (total + mod_pow(m, cycles)) % MOD
    return total * mod_pow(len(actions), MOD - 2) % MOD


def test_small():
    print("=== PE 651 Verification (D_a × D_b) ===")
    
    # Test known values
    tests = [
        (2,2,3,11),
        (3,2,3,56),
        (2,3,4,156),
        (8,13,21,49718354),
        (13,144,233,907081451),
    ]
    
    for m,a,b,exp in tests:
        f = compute_f(m, a, b)
        ok = "✓" if f == exp else "✗"
        print(f"f({m},{a},{b}) = {f} (expected {exp}) {ok}")
    
    # Brute force for tiny cases
    print("\n--- Brute force verification ---")
    for m, a, b in [(2,2,2), (2,2,3), (2,3,2), (2,3,3), (3,2,2)]:
        f_formula = compute_f(m, a, b)
        try:
            f_brute = 0
            for k in range(m+1):
                col = colorings_brute(k, a, b)
                term = nCr_mod(m, k) * col % MOD
                if (m - k) % 2 == 1:
                    f_brute = (f_brute - term + MOD) % MOD
                else:
                    f_brute = (f_brute + term) % MOD
            ok = "✓" if f_formula == f_brute else "✗"
            print(f"f({m},{a},{b}) formula={f_formula} brute={f_brute} {ok}")
        except Exception as e:
            print(f"f({m},{a},{b}) formula={f_formula} brute error: {e}")

if __name__ == "__main__":
    test_small()
