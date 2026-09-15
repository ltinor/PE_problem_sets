#!/usr/bin/env python3
"""PE 653: Verify formula for d(L,N,j)."""
R = 10

def compute_d(L, N, j):
    MOD_PRNG = 32745673
    r = 6563116
    free_dist = []
    x_prev = 0  # center of previous marble (or 0 for first)
    
    for i in range(N):
        gap = (r % 1000) + 1
        if i == 0:
            x = gap + R
        else:
            x = x_prev + R + gap + R
        x_prev = x
        
        direction = 1 if r <= 10000000 else -1
        
        if direction == 1:
            fd = L - x
        else:
            fd = (x - R) + (L - R)
        free_dist.append(fd)
        
        r = (r * r) % MOD_PRNG
    
    free_dist.sort()
    idx = N - j  # 0-indexed
    result = free_dist[idx] - 2 * (2 * R)  # subtract 40
    return result

# Test
for L, N, j, expected in [
    (5000, 3, 2, 5519),
    (10000, 11, 6, 11780),
    (100000, 101, 51, 114101),
]:
    result = compute_d(L, N, j)
    ok = "✓" if result == expected else "✗"
    print(f"d({L},{N},{j}) = {result} (expected {expected}) {ok}")

# Full problem
L = 1_000_000_000
N = 1_000_001
j = 500_001
result = compute_d(L, N, j)
print(f"\nd(1e9, 1000001, 500001) = {result}")
print(f"Expected: 1130671207")
print(f"Match: {'✓' if result == 1130671207 else '✗'}")
