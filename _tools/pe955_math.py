#!/usr/bin/env python3
"""PE 955: Finding Triangles - mathematical approach
Solve a^2 + b^2 - c^2 = 1 with a,b,c odd.
Given a, find smallest b>1 (odd) such that a^2 + b^2 - 1 = c^2.
This is equivalent to c^2 - b^2 = a^2 - 1 => factor N = a^2 - 1 = d1*d2
where d1=c-b, d2=c+b, d1*d2 = N.
b = (d2-d1)/2, c = (d1+d2)/2.
We want minimal b > 1.
"""
import math
import sys

def find_next(a):
    """Given odd a = 2p+1, find the next odd c = 2q+1 and b = 2k+1.
    Returns (b, c, k, q, p) where k is the advance.
    """
    N = a*a - 1
    
    # Find factor pair (d1, d2) with d1*d2 = N, d1 <= d2
    # that minimizes d2-d1 (while ensuring b > 1 and b,c odd)
    best_d1 = None
    best_diff = None
    
    # Iterate over divisors d1 of N
    sqrtN = int(math.isqrt(N))
    
    for d1 in range(1, sqrtN + 1):
        if N % d1 == 0:
            d2 = N // d1
            # b = (d2-d1)/2 must be > 1 (b >= 3)
            b = (d2 - d1) // 2
            if b <= 1:
                continue
            # b must be odd
            if b % 2 == 0:
                continue
            # c = (d1+d2)/2 must be integer and odd
            if (d1 + d2) % 2 != 0:
                continue
            c = (d1 + d2) // 2
            if c % 2 == 0:
                continue
            # Check: a^2 + b^2 - 1 == c^2
            # This should automatically hold
            diff = d2 - d1
            if best_diff is None or diff < best_diff:
                best_diff = diff
                best_d1 = d1
    
    if best_d1 is None:
        return None
    
    d2 = N // best_d1
    b = (d2 - best_d1) // 2
    c = (d1 + d2) // 2  # Wait, this should use best_d1
    c = (best_d1 + d2) // 2
    k = (b - 1) // 2
    q = (c - 1) // 2
    p = (a - 1) // 2
    
    # Verify
    assert a*a + b*b - 1 == c*c, f"Verification failed: {a}^2 + {b}^2 - 1 = {a*a + b*b - 1} != {c}^2"
    assert b % 2 == 1 and c % 2 == 1
    assert T(p) + T(k) == T(q), f"T({p}) + T({k}) != T({q})"
    
    return b, c, k, q, p

def T(n):
    return n*(n+1)//2

# Test with known values
a = 5  # 2*2+1, T_2 = 3
results = [(0, 3, 2)]  # (index, value, triangle_index m)

for step in range(1, 20):
    res = find_next(a)
    if res is None:
        print(f"Failed at step {step}")
        break
    b, c, k, q, p = res
    # Previous index += k
    prev_idx = results[-1][0]
    new_idx = prev_idx + k
    new_val = T(q)
    results.append((new_idx, new_val, q))
    print(f"  #{step+1}: a_{new_idx} = {new_val} = T_{q} (advance {k})", file=sys.stderr)
    a = c

print(f"\nFinal results (first {len(results)}):")
for i, (idx, val, m) in enumerate(results):
    print(f"  #{i+1}: a_{idx} = {val} = T_{m}")
