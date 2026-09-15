#!/usr/bin/env python3
"""PE 958: Compute f(n) = smallest m coprime to n minimizing subtraction steps."""
import math

def d(n, m):
    """Number of subtraction steps in Euclidean algorithm for gcd(n,m)."""
    a, b = n, m
    steps = 0
    while a != b:
        if a > b:
            a -= b
        else:
            b -= a
        steps += 1
    return steps

def f_brute(n):
    """Brute force f(n) for small n."""
    best_d = float('inf')
    best_m = None
    for m in range(1, n):
        if math.gcd(n, m) == 1:
            steps = d(n, m)
            if steps < best_d:
                best_d = steps
                best_m = m
    return best_m, best_d

# Test with given examples
for n in [7, 89, 8191]:
    m, steps = f_brute(n)
    print(f"n={n}: f(n)={m}, d(n,{m})={steps}")

# Let's analyze the structure
print("\nAnalysis for n=89:")
for m in range(1, 89):
    if math.gcd(89, m) == 1:
        steps = d(89, m)
        if steps <= 20:
            print(f"  m={m}: d={steps}")
