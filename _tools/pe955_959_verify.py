#!/usr/bin/env python3
"""Verify check points and determine data ranges for PE 955-959 simple versions."""
import math
from math import gcd, isqrt, lgamma, log, exp

print("=" * 60)
print("PE 959: f(a,b) = 1/G, G = sum_m C((a'+b')m, a'm)/2^((a'+b')m)")
print("=" * 60)


def f_ab(a, b):
    g = gcd(a, b)
    ap, bp = a // g, b // g
    if ap == bp:
        return 0.0
    N = ap + bp
    K = ap
    G = 0.0
    m = 0
    while True:
        logterm = lgamma(N * m + 1) - lgamma(K * m + 1) - lgamma((N - K) * m + 1) - (N * m) * log(2.0)
        term = exp(logterm)
        G += term
        m += 1
        if term < 1e-20:
            break
    return 1.0 / G


for (a, b) in [(1, 1), (1, 2), (2, 1), (2, 4), (1, 3), (3, 1), (89, 97), (1, 1)]:
    print(f"f({a},{b}) = {f_ab(a, b):.12f}")

print()
print("=" * 60)
print("PE 958: f(n) = min m coprime to n minimizing subtraction steps")
print("=" * 60)


def d_steps(n, m):
    a, b = n, m
    if a < b:
        a, b = b, a
    steps = 0
    while b > 0:
        steps += a // b
        a, b = b, a % b
    return steps


def f_958(n):
    best_m, best_d = -1, float('inf')
    for m in range(1, n):
        if gcd(n, m) == 1:
            s = d_steps(n, m)
            if s < best_d:
                best_d = s
                best_m = m
    return best_m, best_d


for n in [7, 89, 8191]:
    m, s = f_958(n)
    print(f"f({n}) = {m} (d={s})")

print()
print("=" * 60)
print("PE 956: D(n,m) = sum of divisors d with Omega(d) divisible by m")
print("=" * 60)


def omega(x):
    c = 0
    p = 2
    y = x
    while p * p <= y:
        while y % p == 0:
            y //= p
            c += 1
        p += 1
    if y > 1:
        c += 1
    return c


def D(n, m):
    total = 0
    divs = []
    for i in range(1, isqrt(n) + 1):
        if n % i == 0:
            divs.append(i)
            if i * i != n:
                divs.append(n // i)
    for d in divs:
        if omega(d) % m == 0:
            total += d
    return total


print("D(24,3) =", D(24, 3))

print()
print("=" * 60)
print("PE 955: direct simulation of triangle sequence")
print("=" * 60)


def is_tri(x):
    s = isqrt(1 + 8 * x)
    return s * s == 1 + 8 * x and (-1 + s) % 2 == 0


a = 3
d = 1
idx = 0
tri_count = 1  # a_0 = 3 is T_2
res = [(0, 3)]
while tri_count < 25:
    if is_tri(a):
        d = 1
    else:
        d += 1
    a += d
    idx += 1
    if is_tri(a):
        tri_count += 1
        res.append((idx, a))
        if tri_count <= 20 or tri_count % 5 == 0:
            print(f"  #{tri_count}: a_{idx} = {a}")

print()
print("Index growth (for data range decision):")
for i, (ix, val) in enumerate(res[:21]):
    print(f"  #{i+1}: idx={ix} val={val}")
