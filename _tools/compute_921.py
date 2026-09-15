#!/usr/bin/env python3
"""PE 921: Golden Recurrence - optimized computation"""
import sys
sys.setrecursionlimit(100000)

MOD = 398874989
sqrt5 = 326226736

def mul(a, b):
    return ((a[0]*b[0] + 5*a[1]*b[1]) % MOD, (a[0]*b[1] + a[1]*b[0]) % MOD)

def qf_pow(base, exp):
    result = (1, 0)
    b = base
    e = exp
    while e:
        if e & 1:
            result = mul(result, b)
        b = mul(b, b)
        e >>= 1
    return result

def qf_inv(a):
    denom = (a[0]*a[0] - 5*a[1]*a[1]) % MOD
    inv_denom = pow(denom, MOD-2, MOD)
    return (a[0] * inv_denom % MOD, (-a[1]) * inv_denom % MOD)

# E0 = -2 - √5
E0 = ((-2) % MOD, (-1) % MOD)

# Precompute powers of E0
# Order is 199437494
ORDER = 199437494

# For speed, precompute E0^pow2[k] = E0^{2^k}
E0_pow2 = [E0]
for k in range(1, 28):  # 2^28 > ORDER
    E0_pow2.append(mul(E0_pow2[-1], E0_pow2[-1]))

# Precompute 5^pow2[k] mod ORDER
pow5_pow2 = [5 % ORDER]
for k in range(1, 28):
    pow5_pow2.append((pow5_pow2[-1] * pow5_pow2[-1]) % ORDER)

def compute_s_from_exp(exp):
    """exp = 5^n mod ORDER"""
    # Compute E0^exp
    result = (1, 0)
    e = exp
    k = 0
    while e:
        if e & 1:
            result = mul(result, E0_pow2[k])
        e >>= 1
        k += 1
    
    En = result
    # a_n = (E_n - 1)/(E_n + 1)
    num = ((En[0] - 1) % MOD, En[1])
    den = ((En[0] + 1) % MOD, En[1])
    an = mul(num, qf_inv(den))
    
    a, b = an
    if a == 0:
        return 0  # shouldn't happen
    q = pow(a, MOD-2, MOD)
    p = q * b % MOD
    return (pow(p, 5, MOD) + pow(q, 5, MOD)) % MOD

# Compute Fibonacci numbers mod phi(ORDER) where phi(ORDER) is the period for 5
# phi(ORDER) = phi(2 * 99718747) = phi(2) * phi(99718747)
# = 1 * (99718747 - 1) = 99718746

PHI_ORDER = 99718746

# Test small values first
print("Testing s(0..5):")
exp = 1  # 5^0
for n in range(6):
    s = compute_s_from_exp(exp)
    print(f"  s({n}) = {s}")
    exp = (exp * 5) % ORDER

# Compute Fibonacci and accumulate
M_MAX = 1618034

print(f"\nComputing S({M_MAX})...")
total = 0
f_prev, f_curr = 1, 1  # F_1=1, F_2=1 (but we start from i=2, so F_2=1)

for i in range(2, M_MAX + 1):
    fi_mod = f_curr % PHI_ORDER  # F_i mod phi(ORDER)
    
    # Compute 5^{F_i} mod ORDER
    exp5 = 1
    e5 = fi_mod
    k5 = 0
    while e5:
        if e5 & 1:
            exp5 = (exp5 * pow5_pow2[k5]) % ORDER
        e5 >>= 1
        k5 += 1
    
    s_val = compute_s_from_exp(exp5)
    total = (total + s_val) % MOD
    
    if i % 100000 == 0:
        print(f"  i={i}, total so far={total}")
    
    # Next Fibonacci
    f_next = (f_prev + f_curr) % PHI_ORDER
    f_prev, f_curr = f_curr, f_next

print(f"\nS({M_MAX}) = {total}")
print(f"Answer (mod {MOD}): {total}")
