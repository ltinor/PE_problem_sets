#!/usr/bin/env python3
"""Explore PE 955: Finding Triangles"""
import math

def is_triangle(x):
    """Check if x is a triangle number T_m = m(m+1)/2"""
    # Solve m(m+1)/2 = x => m^2 + m - 2x = 0
    # m = (-1 + sqrt(1 + 8x))/2
    d = 1 + 8*x
    s = int(math.isqrt(d))
    if s*s != d:
        return False
    return (-1 + s) % 2 == 0

def triangle_index(x):
    """Return m such that T_m = x, or -1"""
    d = 1 + 8*x
    s = int(math.isqrt(d))
    if s*s != d:
        return -1
    m = (-1 + s) // 2
    if m*(m+1)//2 == x:
        return m
    return -1

# Generate sequence and find triangle numbers
a_prev = 3  # a_0
a_curr = None

# First, compute a_1
# a_0 = 3 is a triangle number (T_2 = 3)
# So a_1 = a_0 + 1 = 4
assert is_triangle(3)

a = [3]
n = 0
a_n = 3
a_prev = None  # a_{-1} doesn't exist for n=0

triangle_positions = [(0, 3, 2)]  # (index n, value a_n, m where T_m = a_n)

while len(triangle_positions) < 20:
    if is_triangle(a_n):
        a_next = a_n + 1
    else:
        if a_prev is None:
            # For n=0, a_0 = 3 is triangle, so this branch doesn't happen
            a_next = 2*a_n + 1  # a_{n-1} doesn't exist, use something else?
        else:
            a_next = 2*a_n - a_prev + 1
    
    a_prev = a_n
    a_n = a_next
    n += 1
    
    a.append(a_n)
    if is_triangle(a_n):
        m = triangle_index(a_n)
        triangle_positions.append((n, a_n, m))

print("First 15 triangle numbers in sequence:")
for i, (idx, val, m) in enumerate(triangle_positions[:15]):
    print(f"  #{i+1}: a_{idx} = {val} = T_{m}")

print(f"\n10th triangle number: a_{triangle_positions[9][0]} = {triangle_positions[9][1]} (should be a_2964 = 1439056)")
print(f"  Got: a_{triangle_positions[9][0]} = {triangle_positions[9][1]}")

# Check if the 10th matches the given value
if len(triangle_positions) >= 10:
    idx10, val10, m10 = triangle_positions[9]
    print(f"  Expected: a_2964 = 1439056, Got: a_{idx10} = {val10}, T_{m10}")
