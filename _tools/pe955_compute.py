#!/usr/bin/env python3
"""Compute PE 955: find index of 70th triangle number"""
import math
import sys

def is_triangle(x):
    d = 1 + 8*x
    s = int(math.isqrt(d))
    return s*s == d and (-1 + s) % 2 == 0

def find_nth_triangle(n_target, max_terms=10**9):
    """Find the index of the n_target-th triangle number"""
    a = 3      # current value
    d = 1      # current difference = a_n - a_{n-1}
    idx = 0     # current index n
    
    # a_0 = 3 is the 1st triangle
    tri_count = 1
    if n_target == 1:
        return 0, 3
    
    while tri_count < n_target and idx < max_terms:
        if is_triangle(a):
            d = 1
        else:
            d += 1
        a += d
        idx += 1
        
        if is_triangle(a):
            tri_count += 1
            if tri_count <= 15 or tri_count % 5 == 0:
                print(f"  #{tri_count}: a_{idx} = {a}", file=sys.stderr, flush=True)
            if tri_count == n_target:
                return idx, a
    
    return None

# For quick testing, first find the 20th
print("Computing...", file=sys.stderr)
result = find_nth_triangle(20)
if result:
    idx, val = result
    print(f"20th triangle: a_{idx} = {val}")
