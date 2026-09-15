#!/usr/bin/env python3
"""PE 925: Larger Digit Permutation III - T(N) = sum B(n^2) for n=1..N"""
MOD = 10**9 + 7

def B(n):
    s = list(str(n))
    i = len(s) - 2
    while i >= 0 and s[i] >= s[i+1]:
        i -= 1
    if i < 0:
        return 0
    j = len(s) - 1
    while s[j] <= s[i]:
        j -= 1
    s[i], s[j] = s[j], s[i]
    s[i+1:] = reversed(s[i+1:])
    return int(''.join(s))

# Compute T(10) and T(100) to verify
t10 = sum(B(n*n) for n in range(1, 11))
t100 = sum(B(n*n) for n in range(1, 101))
print(f"T(10) = {t10} (expected 270)")
print(f"T(100) = {t100} (expected 335316)")

# Check some values
print("\nFirst 20 values of B(n^2):")
for n in range(1, 21):
    bn = B(n*n)
    print(f"  n={n}: n^2={n*n}, B(n^2)={bn}")

# For N=10^16, we need sum of B(n^2) for n=1..10^16.
# n^2 for n=10^16 is 10^32, which has 33 digits.
# This is tractable! Each n^2 has at most 33 digits.
# We can compute B(n^2) efficiently for all n up to 10^16.

# But 10^16 is way too many to iterate. We need a mathematical approach.
# B(n) for n with many digits - the key is to count contributions by digit pattern.

# For each n, n^2 mod 10^9+7 is straightforward. But B(n^2) depends on ALL digits.
# We need to compute sum of B(k) where k = n^2 for n=1..10^16.

# This seems like we need digit DP over n (not over n^2).
# Wait: we need to sum B(n^2) where n ranges over 1..10^16.
# n has up to 16 digits, n^2 has up to 32 digits.
# 
# Key insight: B(x) = next permutation of digits. For numbers with digit multiset,
# we can precompute the next permutation value.

# Actually, this is a known PE problem type: counting sum of B(f(n)) for many n
# using digit DP. We need to consider all n < 10^16 and their squares.

# But wait: B(n^2) for n with up to 16 digits means n^2 has up to 32 digits.
# B(n^2) is determined by the digit multiset of n^2.
# For each possible multiset of digits of n^2, we can compute B(n^2).
# But the number of possible n^2 values is 10^16, which is too many.

# Alternative: for the sum modulo 10^9+7, we can use digit DP on n.
# But B(n^2) is not linear in n^2.

# Let me think differently. Maybe there's a property of B(n^2) for large n.
# For numbers with digits mostly in descending order, B(n) = 0.
# For n^2, the digits might have special structure.

# Actually, I think the solution involves:
# 1. For each n, determine the digit multiset of n^2
# 2. Compute B of that multiset
# 3. Sum over all n

# Since n ranges up to 10^16 (16 decimal digits), we can use DP over n.
# For each prefix of n, we track the partial square and the digit multiset.
# But this is complex because squaring a number interacts all digits.

# Let me try a different approach: compute T(N) for smaller N and see if there's a pattern.
import math

# Let me check if B(n^2) has a simple form
print("\nChecking B(n^2) for n=1..1000:")
# Group by number of digits in n^2
counts = {}
for n in range(1, 1001):
    d = len(str(n*n))
    counts[d] = counts.get(d, 0) + 1
print("Digit count distribution for n^2 (n=1..1000):")
for d in sorted(counts):
    print(f"  {d} digits: {counts[d]}")

# For numbers with 1-2 digits (n^2 < 100), B(n^2) might be 0 or small
# Let's see what fraction have B=0
zeros = sum(1 for n in range(1, 10001) if B(n*n) == 0)
print(f"\nFraction with B(n^2)=0 for n=1..10000: {zeros}/10000 = {zeros/10000}")
