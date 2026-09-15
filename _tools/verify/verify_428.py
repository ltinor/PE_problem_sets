#!/usr/bin/env python3
"""Verify PE 428 necklace triplet counting"""
import sys
from math import gcd, isqrt

def count_triplets_brute(n):
    """Brute force count of necklace triplets with b ≤ n"""
    import math
    count = 0
    for b in range(1, n + 1):
        for a in range(1, 1000):  # reasonable bound
            for c in range(1, 1000):
                # Check Steiner chain condition
                S = b * (a + b + c) / ((a + b) * (b + c))
                # Check if S = sin^2(pi/k) for some integer k ≥ 3
                # sin^2(pi/k) for k=3: 0.75, k=4: 0.5, k=6: 0.25
                for k in [3, 4, 6]:
                    target = math.sin(math.pi / k) ** 2
                    if abs(S - target) < 1e-12:
                        count += 1
                        break
    return count

def count_divisors(x):
    cnt = 0
    for d in range(1, isqrt(x) + 1):
        if x % d == 0:
            cnt += 1
            if d * d != x:
                cnt += 1
    return cnt

def count_divisors_mod(x, target, mod_val):
    cnt = 0
    for d in range(1, isqrt(x) + 1):
        if x % d == 0:
            if d % mod_val == target:
                cnt += 1
            e = x // d
            if e != d and e % mod_val == target:
                cnt += 1
    return cnt

def count_formula(n):
    """Count using divisor formula"""
    ans = 0
    for b in range(1, n + 1):
        # k=4
        ans += count_divisors(2 * b * b)
        # k=6
        ans += count_divisors(12 * b * b)
        # k=3
        target = (-b) % 3
        ans += count_divisors_mod(4 * b * b, target, 3)
    return ans

# Verify for small n against known results
print("T(1) =", count_formula(1), "(expected 9)")
print("T(20) =", count_formula(20), "(expected 732)")
# T(3000) would be slow; verify smaller values

# Also verify individual b values
def count_for_b(b):
    ans = count_divisors(2 * b * b)
    ans += count_divisors(12 * b * b)
    target = (-b) % 3
    ans += count_divisors_mod(4 * b * b, target, 3)
    return ans

print("\nPer b:")
for b in range(1, 6):
    print(f"  b={b}: {count_for_b(b)}")

# Let me enumerate triplets for b=1 to see if they match
print("\nEnumerating triplets for b=1:")
# k=4: (a-1)(c-1) = 2*1^2 = 2
for d in range(1, 3):
    if 2 % d == 0:
        e = 2 // d
        a = d + 1
        c = e + 1
        print(f"  k=4: a={a}, c={c}")

# k=3: (3a-1)(3c-1) = 4*1^2 = 4
for d in range(1, 5):
    if 4 % d == 0:
        if (d + 1) % 3 == 0:
            e = 4 // d
            a = (d + 1) // 3
            c = (e + 1) // 3
            print(f"  k=3: a={a}, c={c}")

# k=6: (a-3)(c-3) = 12*1^2 = 12
for d in range(1, 13):
    if 12 % d == 0:
        e = 12 // d
        a = d + 3
        c = e + 3
        print(f"  k=6: a={a}, c={c}")
