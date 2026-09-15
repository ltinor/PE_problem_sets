#!/usr/bin/env python3
"""PE 955: Optimized solver using divisor enumeration.
Finds the 70th triangle number in the sequence.
"""
import math
import sys

def find_next_fast(a, max_iter=10**7):
    """Given odd a = 2p+1, find next c = 2q+1.
    
    Need c^2 - b^2 = a^2 - 1 with minimal b > 1 odd.
    Let N = a^2 - 1 = (a-1)(a+1).
    Find d1|N, d1*d2=N, d1<d2, minimizing d2-d1,
    with (d2-d1)%4==2 (so b odd) and (d2-d1)//2 > 1.
    """
    N = a*a - 1
    
    # For large N, we need efficient divisor enumeration.
    # Instead of checking all divisors, we can search for b directly.
    # b is odd, b >= 3.
    # c^2 = a^2 + b^2 - 1
    # We need a^2 + b^2 - 1 to be a perfect square.
    
    # Start from b=3 and go up. This is O(sqrt(N)) in worst case
    # but might be fast if b is small (which it often is).
    
    sqrtN = int(math.isqrt(N))
    
    # First try: b small (up to ~10^7)
    for b in range(3, min(max_iter, sqrtN), 2):
        c2 = a*a + b*b - 1
        c = int(math.isqrt(c2))
        if c*c == c2:
            return b, c
    
    # If b is large, try divisor approach
    # We need d1 * d2 = N, d1 <= sqrtN
    # b = (d2 - d1) / 2, c = (d1 + d2) / 2
    # For b to be odd: d2-d1 ≡ 2 (mod 4), meaning d1,d2 ≡ 2 (mod 4) or d1,d2 ≡ 0 (mod 4)
    # Actually: since d1*d2 is even (N is even), both d1, d2 are even.
    # d2-d1 = 2b where b is odd → d2-d1 ≡ 2 (mod 4)
    
    # Alternative: Let d1 = 2u, d2 = 2v where u*v = N/4
    # Then b = v - u, c = u + v, and b must be odd > 1.
    # u*v = (a^2-1)/4 = (a-1)(a+1)/4
    
    # For efficiency, we can try divisor pairs starting from sqrt
    M = N // 4  # u * v = M
    sqrtM = int(math.isqrt(M))
    
    # Start from u = sqrtM going down
    for u in range(sqrtM, 0, -1):
        if M % u == 0:
            v = M // u
            b = v - u
            if b > 1 and b % 2 == 1:
                c = u + v
                return b, c
    
    return None

def T(n):
    return n*(n+1)//2

a = 5  # 2*2+1, p=2
results = [(0, 3, 2)]  # (index, value a_n, triangle index m)

for step in range(1, 100):
    res = find_next_fast(a)
    if res is None:
        print(f"Failed at step {step}, a={a}")
        break
    b, c = res
    k = (b - 1) // 2
    q = (c - 1) // 2
    p = (a - 1) // 2
    
    prev_idx = results[-1][0]
    new_idx = prev_idx + k
    new_val = T(q)
    results.append((new_idx, new_val, q))
    
    if step <= 25 or step % 5 == 0:
        print(f"  #{step+1}: a_{new_idx} = {new_val} = T_{q} (advance {k}, p={p}->{q})", file=sys.stderr, flush=True)
    
    if step == 69:  # 70th (0-indexed)
        print(f"\n70th triangle number: a_{new_idx} = {new_val}")
        print(f"Index n = {new_idx}")
        break
    
    a = c

print(f"\nComputed {len(results)} triangle numbers")
