#!/usr/bin/env python3
"""Compute PE 256-275 answers."""
import math, sys
sys.setrecursionlimit(10000)

answers = {}

# PE 274: Sum of divisibility multipliers for primes < 10^7 coprime to 10
def pe274():
    N = 10**7
    sieve = [True] * (N+1)
    sieve[0] = sieve[1] = False
    total = 0
    for i in range(2, N+1):
        if sieve[i]:
            for j in range(i*i, N+1, i):
                sieve[j] = False
            if i not in (2, 5):
                # m * 10 ≡ 1 (mod p) → m = pow(10, -1, p)
                m = pow(10, -1, i)
                total += m
    return total

answers[274] = pe274()
print(f"PE274: {answers[274]}")
