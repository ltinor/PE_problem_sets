"""Gaussian elimination over GF(2) for PE 331 - pure Python"""
def gauss_gf2(A, b):
    """Solve Ax = b over GF(2). Returns (solvable, solution, rank)"""
    n = len(A)
    m = len(A[0]) if A else 0
    # Augmented matrix
    M = [row[:] + [b[i]] for i, row in enumerate(A)]
    
    where = [-1] * m
    row = 0
    for col in range(m):
        # Find pivot
        pivot = -1
        for r in range(row, n):
            if M[r][col] == 1:
                pivot = r
                break
        if pivot == -1:
            continue
        # Swap
        M[row], M[pivot] = M[pivot], M[row]
        where[col] = row
        
        # Eliminate
        for r in range(n):
            if r != row and M[r][col] == 1:
                for c in range(m + 1):
                    M[r][c] ^= M[row][c]
        row += 1
    
    rank = row
    # Check consistency
    for r in range(rank, n):
        if M[r][m] == 1:
            return False, None, rank  # No solution
    
    # Extract solution (free vars = 0)
    x = [0] * m
    for col in range(m - 1, -1, -1):
        if where[col] != -1:
            r = where[col]
            val = M[r][m]
            for c in range(col + 1, m):
                if M[r][c]:
                    val ^= x[c]
            x[col] = val
    return True, x, rank

def test(N):
    n2 = N * N
    A = [[0]*n2 for _ in range(n2)]
    for x in range(N):
        for y in range(N):
            r = x*N + y
            for i in range(N):
                for j in range(N):
                    c = i*N + j
                    if x == i or y == j:
                        A[r][c] = 1
    
    lo = (N-1)*(N-1)
    hi = N*N
    CN = [0] * n2
    for x in range(N):
        for y in range(N):
            if lo <= x*x + y*y < hi:
                CN[x*N + y] = 1
    
    solvable, x, rank = gauss_gf2(A, CN)
    print(f"N={N}: solvable={solvable}, rank={rank}/{n2}")
    if solvable:
        flips = sum(x)
        print(f"  Solution has {flips} flips")
        # Positions
        pos = []
        for i in range(n2):
            if x[i]:
                pos.append((i//N, i%N))
        print(f"  Positions: {pos[:10]}..." if len(pos) > 10 else f"  Positions: {pos}")
    return solvable

for N in [3, 5, 7, 10]:
    test(N)
