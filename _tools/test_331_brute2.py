"""
PE 331 - Cross flips brute-force analysis - extended
"""
import math

def compute_M(N):
    M = [[0]*N for _ in range(N)]
    lo = (N-1)*(N-1)
    hi = N*N
    for x in range(N):
        for y in range(N):
            v = x*x + y*y
            if lo <= v < hi:
                M[x][y] = 1
    return M

def solve_T(N):
    """Brute force with optimization: try all R masks, optimal C per R."""
    M = compute_M(N)
    best = N*N + 1
    # Precompute column counts for each R mask efficiently
    for r_mask in range(1 << N):
        total = 0
        for y in range(N):
            cnt1 = 0
            for x in range(N):
                if M[x][y] ^ ((r_mask >> x) & 1):
                    cnt1 += 1
            total += min(cnt1, N - cnt1)
        if total < best:
            best = total
            if best <= 0:
                break
    return best

print("N, T(N), black_cells")
for N in [3, 5, 7, 9, 11]:
    M = compute_M(N)
    s = sum(sum(row) for row in M)
    t = solve_T(N)
    print(f"N={N}: T={t}, black={s}, ratio={t/N:.4f}")

# Also try N that are 2^i-1
for i in range(3, 7):
    N = (1 << i) - 1
    if N <= 15:
        M = compute_M(N)
        s = sum(sum(row) for row in M)
        t = solve_T(N)
        print(f"2^{i}-1={N}: T={t}, black={s}")
