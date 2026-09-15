#!/usr/bin/env python3
"""Debug PE 390: find all triangles with area <= 10000"""
import math

def brute(n):
    """Find all (b,c) with b,c positive, area integer <= n"""
    results = []
    for b in range(1, 200):
        b2 = b * b
        for c in range(1, 2000):
            val = b2 + c * c + b2 * c * c
            d = int(math.isqrt(val))
            if d * d == val and d % 2 == 0:
                area = d // 2
                if area <= n:
                    results.append((b, c, area))
    return results

# Find all solutions area <= 1000
sols = brute(1000)
print("All solutions with area <= 1000:")
for b, c, area in sorted(sols, key=lambda x: x[2]):
    print(f"b={b}, c={c}, area={area}, b%2={b%2}")

print(f"\nTotal (b<=c): {sum(1 for b,c,a in sols if b<=c)}")
print(f"Total sum (b<=c): {sum(a for b,c,a in sols if b<=c)}")
print(f"Total sum (all): {sum(a for _,_,a in sols)}")

# Check which b values appear
from collections import Counter
b_counts = Counter(b for b,_,_ in sols)
print(f"\nUnique b values: {sorted(b_counts.keys())}")
