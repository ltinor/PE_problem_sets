"""Find minimum weight solution for N=3 and N=5 by enumerating kernel"""
def gauss_gf2_full(A, b):
    """Returns (solvable, particular_sol, kernel_basis)"""
    n = len(A)
    m = len(A[0])
    M = [row[:] + [b[i]] for i, row in enumerate(A)]
    
    where = [-1] * m  
    row = 0
    for col in range(m):
        pivot = -1
        for r in range(row, n):
            if M[r][col] == 1:
                pivot = r
                break
        if pivot == -1:
            continue
        M[row], M[pivot] = M[pivot], M[row]
        where[col] = row
        for r in range(n):
            if r != row and M[r][col] == 1:
                for c in range(m + 1):
                    M[r][c] ^= M[row][c]
        row += 1
    
    rank = row
    for r in range(rank, n):
        if M[r][m] == 1:
            return False, None, None, rank
    
    # Particular solution (free vars = 0)
    x = [0] * m
    for col in range(m - 1, -1, -1):
        if where[col] != -1:
            r = where[col]
            val = M[r][m]
            for c in range(col + 1, m):
                if M[r][c]:
                    val ^= x[c]
            x[col] = val
    
    # Kernel basis
    kernel = []
    free_cols = [c for c in range(m) if where[c] == -1]
    for fc in free_cols:
        kv = [0] * m
        kv[fc] = 1
        for col in range(m - 1, -1, -1):
            if where[col] != -1:
                r = where[col]
                val = 0
                for c in range(col + 1, m):
                    if M[r][c]:
                        val ^= kv[c]
                kv[col] = val
        kernel.append(kv)
    
    return True, x, kernel, rank

def build_system(N):
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
    return A

def compute_CN(N):
    lo = (N-1)*(N-1)
    hi = N*N
    CN = [0] * (N*N)
    for x in range(N):
        for y in range(N):
            if lo <= x*x + y*y < hi:
                CN[x*N + y] = 1
    return CN

def find_min_weight(N):
    A = build_system(N)
    CN = compute_CN(N)
    solvable, x0, kernel, rank = gauss_gf2_full(A, CN)
    if not solvable:
        return None, rank
    
    # Enumerate all solutions (2^ker_dim)
    ker_dim = len(kernel)
    best = sum(x0)
    best_x = x0[:]
    
    for mask in range(1, 1 << ker_dim):
        x = x0[:]
        for i in range(ker_dim):
            if mask & (1 << i):
                for j in range(N*N):
                    x[j] ^= kernel[i][j]
        w = sum(x)
        if w < best:
            best = w
            best_x = x[:]
    
    flips = [(i//N, i%N) for i in range(N*N) if best_x[i]]
    return best, flips, rank

for N in [3, 5]:
    result = find_min_weight(N)
    if result:
        best, flips, rank = result
        print(f"N={N}: min weight = {best}, rank = {rank}")
        print(f"  Flips: {flips}")
    else:
        print(f"N={N}: unsolvable")
