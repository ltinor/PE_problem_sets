"""Gaussian elimination over GF(2) for PE 331"""
import numpy as np

def build_system(N):
    """Build A where A[(x,y), (i,j)] = 1 iff x=i or y=j"""
    n2 = N*N
    A = np.zeros((n2, n2), dtype=np.int8)
    for x in range(N):
        for y in range(N):
            row = x*N + y
            for i in range(N):
                for j in range(N):
                    col = i*N + j
                    if x == i or y == j:
                        A[row, col] = 1
    return A

def compute_CN(N):
    lo = (N-1)*(N-1)
    hi = N*N
    CN = np.zeros(N*N, dtype=np.int8)
    for x in range(N):
        for y in range(N):
            if lo <= x*x + y*y < hi:
                CN[x*N + y] = 1
    return CN

def gaussian_elimination_gf2(A, b):
    """Solve Ax = b over GF(2). Returns solution if exists, else None."""
    n, m = A.shape
    M = np.hstack([A.copy(), b.reshape(-1, 1)])
    M = M % 2
    
    rank = 0
    col = 0
    row_used = [False] * n
    
    while col < m and rank < n:
        # Find pivot
        pivot = None
        for r in range(rank, n):
            if M[r, col] == 1:
                pivot = r
                break
        
        if pivot is not None:
            # Swap rows
            M[[rank, pivot]] = M[[pivot, rank]]
            
            # Eliminate
            for r in range(n):
                if r != rank and M[r, col] == 1:
                    M[r] ^= M[rank]
            
            rank += 1
            row_used[col] = True
        col += 1
    
    # Check consistency
    for r in range(rank, n):
        if M[r, m] == 1:  # augmented column has 1
            return None  # No solution
    
    # Extract solution (set free variables to 0)
    x = np.zeros(m, dtype=np.int8)
    for r in range(rank-1, -1, -1):
        # Find pivot column
        pivot_col = -1
        for c in range(m):
            if M[r, c] == 1:
                pivot_col = c
                break
        if pivot_col >= 0:
            val = M[r, m]
            for c in range(pivot_col+1, m):
                if M[r, c] == 1:
                    val ^= x[c]
            x[pivot_col] = val
    
    return x

# Test N=5
print("Testing N=5...")
N = 5
A = build_system(N)
CN = compute_CN(N)
x = gaussian_elimination_gf2(A, CN)
if x is not None:
    print(f"Found solution with {int(sum(x))} flips")
    # Print flip positions
    flips = []
    for i in range(N*N):
        if x[i]:
            flips.append((i//N, i%N))
    print(f"Flip positions: {flips}")
else:
    print("No solution!")

# Test N=7
print("\nTesting N=7...")
N = 7
A = build_system(N)
CN = compute_CN(N)
x = gaussian_elimination_gf2(A, CN)
if x is not None:
    print(f"Found solution with {int(sum(x))} flips")
else:
    print("No solution!")
    # Check rank and consistency
    n2 = N*N
    M = np.hstack([A.copy(), CN.reshape(-1, 1)])
    M = M % 2
    rank = 0
    for col in range(n2):
        pivot = None
        for r in range(rank, n2):
            if M[r, col] == 1:
                pivot = r
                break
        if pivot is not None:
            M[[rank, pivot]] = M[[pivot, rank]]
            for r in range(n2):
                if r != rank and M[r, col] == 1:
                    M[r] ^= M[rank]
            rank += 1
    print(f"Rank of A: {rank}")
    inconsistent = False
    for r in range(rank, n2):
        if M[r, n2] == 1:
            inconsistent = True
    print(f"Inconsistent: {inconsistent}")
