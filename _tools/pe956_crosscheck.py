#!/usr/bin/env python3
"""Cross-check D(n,m) implementation for a larger case."""
from math import isqrt


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
    t = 0
    for i in range(1, isqrt(n) + 1):
        if n % i == 0:
            if omega(i) % m == 0:
                t += i
            j = n // i
            if j != i and omega(j) % m == 0:
                t += j
    return t


print("D(24,3)      =", D(24, 3))
print("D(1000000,5) =", D(1000000, 5))
print("D(720, 3)    =", D(720, 3))
