"""Correct brute force for PE 331 - directly try all flip subsets"""
from itertools import combinations

def compute_CN(N):
    lo = (N-1)*(N-1)
    hi = N*N
    CN = [[0]*N for _ in range(N)]
    for x in range(N):
        for y in range(N):
            if lo <= x*x + y*y < hi:
                CN[x][y] = 1
    return CN

def apply_flips(N, flips):
    """flips is a list of (i,j) positions. Returns final board."""
    board = [[0]*N for _ in range(N)]
    for i, j in flips:
        # Flip row i and column j
        for k in range(N):
            board[i][k] ^= 1  # flip row
            board[k][j] ^= 1  # flip column (note: (i,j) gets flipped twice = cancelled)
    # Actually, let me reconsider: flip row i, then flip col j.
    # (i,j) is in row i AND col j. If we flip row then col, (i,j) gets flipped twice.
    # The problem says 2N-1 disks flipped, meaning the disk at (i,j) is NOT flipped twice.
    return board

def apply_flips_v2(N, flips):
    """Alternative: flip all where x=i or y=j, but (i,j) only once."""
    board = [[0]*N for _ in range(N)]
    for i, j in flips:
        for x in range(N):
            for y in range(N):
                if x == i or y == j:
                    board[x][y] ^= 1
    return board

def find_min_flips(N):
    CN = compute_CN(N)
    positions = [(i,j) for i in range(N) for j in range(N)]
    
    for k in range(1, N*N+1):
        for combo in combinations(positions, k):
            board = apply_flips_v2(N, combo)
            if board == CN:
                return k, combo
    return 0, []

print("Testing v2 (OR pattern):")
for N in [3, 5, 7]:
    k, combo = find_min_flips(N)
    print(f"N={N}: min flips = {k}")
    if k > 0:
        print(f"  Example: {combo[:5]}...")
