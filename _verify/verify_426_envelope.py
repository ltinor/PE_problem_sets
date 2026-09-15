#!/usr/bin/env python3
"""Compute BBS soliton content using upper envelope of capacity function"""
import sys

def generate_t(N):
    s = 290797
    MOD = 50515093
    t = []
    for _ in range(N + 1):
        t.append((s % 64) + 1)
        s = (s * s) % MOD
    return t

def capacity(t):
    """Compute capacity function F(i) for alternating sequence t"""
    F = [0]  # F[0] = 0
    cum = 0
    for i, val in enumerate(t):
        if i % 2 == 0:  # occupied
            cum += val
        else:  # empty
            cum -= val
        F.append(cum)
    return F

def upper_envelope(F):
    """Compute upper concave envelope of points (i, F[i]).
    Returns list of (i, F[i]) on the envelope."""
    n = len(F)
    points = list(enumerate(F))
    
    # Compute upper convex hull using monotone chain
    # For upper envelope: we want the maximum y for each x
    # Use Andrew's monotone chain for the UPPER hull
    # Sort by x (already sorted)
    
    upper = []
    for p in points:
        while len(upper) >= 2:
            # Check if the last point makes a right turn (clockwise)
            # For upper hull, we want RIGHT turns (or collinear)
            x1, y1 = upper[-2]
            x2, y2 = upper[-1]
            x3, y3 = p
            # Cross product of (x2-x1, y2-y1) and (x3-x2, y3-y2)
            # Positive = left turn, Negative = right turn
            cross = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2)
            if cross >= 0:  # left turn or collinear → remove (for upper hull we want right turns)
                upper.pop()
            else:
                break
        upper.append(p)
    
    return upper

def soliton_from_envelope(env):
    """Extract soliton sizes from upper envelope.
    Soliton sizes are the slopes between consecutive envelope points."""
    solitons = []
    for i in range(1, len(env)):
        dx = env[i][0] - env[i-1][0]
        dy = env[i][1] - env[i-1][1]
        if dx > 0:
            # Each unit of dx corresponds to a soliton
            # The slope dy/dx should be integer
            slope = dy // dx
            # Each dx gives one soliton of size slope? Or dx solitons?
            # Let me check with the example
            for _ in range(dx):
                solitons.append(slope)
        # What if dy is not divisible by dx?
        # In the BBS, the slopes should be integer
    return sorted(solitons)

# Test with example
t = generate_t(10)
F = capacity(t)
print("t:", t)
print("F:", F)

env = upper_envelope(F)
print("Envelope:", env)

sol = soliton_from_envelope(env)
print("Solitons:", sol)
print("Expected:", [1, 3, 10, 24, 51, 75])
print("Sum:", sum(sol))

# Try alternative: soliton size = dy
sol2 = []
for i in range(1, len(env)):
    dy = env[i][1] - env[i-1][1]
    sol2.append(dy)
sol2.sort()
print("Alt (dy only):", sol2, "sum:", sum(sol2))
