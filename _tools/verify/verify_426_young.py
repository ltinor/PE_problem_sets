#!/usr/bin/env python3
"""Try Maya diagram / Young diagram approach for BBS"""
import sys

def generate_t(N):
    s = 290797
    MOD = 50515093
    t = []
    for _ in range(N + 1):
        t.append((s % 64) + 1)
        s = (s * s) % MOD
    return t

def alternating_to_ball_positions(t):
    """Get sorted list of ball positions from alternating sequence"""
    positions = []
    pos = 0
    for i, length in enumerate(t):
        if i % 2 == 0:  # occupied
            positions.extend(range(pos, pos + length))
        pos += length
    return positions

def young_from_balls(positions):
    """Compute Young diagram from ball positions using Maya correspondence.
    λ_i = x_{N-i} - (N-1-i) for i = 0,...,N-1 (using 0-indexed positions)"""
    N = len(positions)
    lam = []
    for i in range(N):
        # i=0 corresponds to rightmost ball
        lam.append(positions[N-1-i] - (N-1-i))
    return lam  # lam is non-increasing

def conjugate(lam):
    """Conjugate a partition"""
    if not lam:
        return []
    conj = []
    for i in range(lam[0]):
        # Count how many parts are > i
        cnt = sum(1 for x in lam if x > i)
        conj.append(cnt)
    return conj

# Test with example
t = generate_t(10)
positions = alternating_to_ball_positions(t)
print(f"Balls: {len(positions)}, positions: {positions[:30]}...")

lam = young_from_balls(positions)
print(f"Young diagram (first 20): {lam[:20]}...")
print(f"Lam max: {lam[0]}, min: {lam[-1]}")

conj = conjugate(lam)
print(f"Conjugate (first 20): {conj[:20]}...")
print(f"Conj length: {len(conj)}")

# The soliton sizes should be something related to lam or conj
# Let me check if the row lengths (lam) or column lengths (conj) match
expected = [1, 3, 10, 24, 51, 75]
print(f"\nExpected: {expected}")
print(f"Sum lam: {sum(lam)}")
print(f"Sum expected: {sum(expected)}")
print(f"Len lam: {len(lam)}, len expected: {len(expected)}")

# Sort lam and take unique? 
# Maybe soliton sizes = distinct values in lam?
unique_lam = sorted(set(lam), reverse=True)
print(f"Unique lam (first 20): {unique_lam[:20]}")

# Maybe the soliton sizes are given by the "profile" of lam?
# Count how many times each value appears
from collections import Counter
cnt = Counter(lam)
common = cnt.most_common(20)
print(f"Most common lam values: {common}")

# The conjugate partition might give soliton sizes
print(f"\nConjugate partition: {conj}")
print(f"Sum conj: {sum(conj)}")

# Another try: maybe soliton sizes are the MULTIPLICITIES in lam
mult = sorted(cnt.values(), reverse=True)
print(f"Multiplicities (first 20): {mult[:20]}")
print(f"Sum of multiplicities: {sum(mult)}, expected: {len(expected)}")
