#!/usr/bin/env python3
"""Analyze pattern of f(n) for PE 958."""
import math

def quotients_sum(n, m):
    """Sum of continued fraction quotients of n/m."""
    s = 0
    a, b = n, m
    while b != 0:
        q = a // b
        s += q
        a, b = b, a % b
    return s

def d_steps(n, m):
    """Subtraction steps."""
    return quotients_sum(n, m) - 1

def f(n):
    """Smallest m < n, gcd(n,m)=1 minimizing d(n,m)."""
    best_d = float('inf')
    best_m = None
    for m in range(1, n):
        if math.gcd(n, m) == 1:
            steps = d_steps(n, m)
            if steps < best_d:
                best_d = steps
                best_m = m
    return best_m, best_d

# Look at pattern for Fibonacci numbers
fib = [1, 1]
while fib[-1] < 10000:
    fib.append(fib[-1] + fib[-2])

print("Fibonacci n:")
for n in fib[3:15]:  # skip 1,1,2
    m, steps = f(n)
    print(f"  n=F_{fib.index(n)}={n}: f(n)={m} (d={steps}, n/m≈{n/m:.4f})")

print("\nPowers of 2 minus 1:")
for k in range(3, 14):
    n = 2**k - 1
    m, steps = f(n)
    print(f"  n=2^{k}-1={n}: f(n)={m} (d={steps})")

print("\nNear 1e12+39:")
# Can't brute force this, need mathematical approach
n = 10**12 + 39
print(f"  n = {n}")
# Check if n is prime
print(f"  Is prime? Checking small factors...")
for p in [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47]:
    if n % p == 0:
        print(f"  Divisible by {p}")
        break
else:
    print(f"  No small factors found")
