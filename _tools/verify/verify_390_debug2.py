#!/usr/bin/env python3
"""Debug PE 390: find all solutions systematically"""
import math

def brute_larger(n):
    """Find all (b,c) with area <= n, using iteration over c"""
    results = {}
    # For each c, find b
    for c in range(1, int(math.isqrt(2 * n)) + 500):
        c2 = c * c
        # area ≈ b*c/2, so b <= 2n/c roughly
        for b in range(1, 2 * n // c + 10):
            val = b*b + c2 + b*b*c2
            d = int(math.isqrt(val))
            if d*d == val and d % 2 == 0:
                area = d // 2
                if area <= n:
                    key = (min(b,c), max(b,c))
                    if key not in results:
                        results[key] = area
    return results

# Find solutions for area <= 1000
sols = brute_larger(1000)
print("All unique triangles with area <= 1000:")
for (b, c), area in sorted(sols.items(), key=lambda x: x[1]):
    print(f"b={b}, c={c}, area={area}")

print(f"\nTotal triangles: {len(sols)}")
print(f"Sum of areas: {sum(sols.values())}")
