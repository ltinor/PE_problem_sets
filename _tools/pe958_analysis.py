#!/usr/bin/env python3
"""More analysis for PE 958."""
import math

def quotients_sum(n, m):
    s = 0
    a, b = n, m
    while b != 0:
        q = a // b
        s += q
        a, b = b, a % b
    return s

def d_steps(n, m):
    return quotients_sum(n, m) - 1

def f_brute(n):
    best_d = float('inf')
    best_m = None
    for m in range(1, n):
        if math.gcd(n, m) == 1:
            steps = d_steps(n, m)
            if steps < best_d:
                best_d = steps
                best_m = m
    return best_m, best_d

# Check detailed structure for selected n
for n in [7, 13, 31, 89, 127, 8191]:
    m, steps = f_brute(n)
    print(f"\nn={n}: f(n)={m}, d={steps}")
    print(f"  n/m = {n/m:.6f}")
    print(f"  n/phi = {n/1.618033988749895:.6f}")
    print(f"  n/phi^2 = {n/2.618033988749895:.6f}")
    print(f"  m/(n/phi^2) = {m/(n/2.618033988749895):.6f}")
    # Compute continued fraction of n/m
    a, b = n, m
    cf = []
    while b:
        cf.append(a//b)
        a, b = b, a % b
    print(f"  CF of n/m: {cf}, sum={sum(cf)}, length={len(cf)}")
