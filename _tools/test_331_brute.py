"""
PE 331 - Cross flips brute-force analysis
For odd N, T(N) = min_{R,C} Σ_x Σ_y (M[x][y] XOR R[x] XOR C[y])
where M[x][y] = 1 iff (N-1)^2 <= x^2 + y^2 < N^2
"""
import math

def compute_M(N):
    """Compute the configuration matrix M for given N"""
    M = [[0]*N for _ in range(N)]
    lo = (N-1)*(N-1)
    hi = N*N
    for x in range(N):
        for y in range(N):
            v = x*x + y*y
            if lo <= v < hi:
                M[x][y] = 1
    return M

def solve_T_bruteforce(N):
    """Brute force T(N) by trying all R and C (2^(2N) possibilities)"""
    M = compute_M(N)
    best = N*N + 1
    # For odd N, any R,C works. Try all.
    for r_mask in range(1 << N):
        R = [(r_mask >> x) & 1 for x in range(N)]
        # For each row, after applying R, we choose C to minimize
        # We can optimize: for fixed R, we want to choose C_y to minimize
        # For column y: each row x contributes M[x][y] XOR R[x]. 
        # We choose C[y] to minimize 1s: compare cnt when C[y]=0 vs C[y]=1
        total = 0
        for y in range(N):
            cnt1 = 0
            for x in range(N):
                if M[x][y] ^ R[x]:
                    cnt1 += 1
            # If C[y]=0: cnt1 ones. If C[y]=1: N-cnt1 ones.
            total += min(cnt1, N - cnt1)
        if total < best:
            best = total
    return best

def solve_T_formula(N):
    """Possible formula for T(N) when N is odd"""
    M = compute_M(N)
    # Count black cells
    s = sum(sum(row) for row in M)
    return s  # Just a guess for now

print("Testing small N:")
for N in [3, 5, 7]:
    M = compute_M(N)
    s = sum(sum(row) for row in M)
    print(f"N={N}: black cells={s}")
    try:
        t = solve_T_bruteforce(N)
        print(f"  T({N}) = {t}")
    except:
        print(f"  (too large to brute force)")

# Verify T(5)=3
print("\nVerification for N=5:")
print(f"T(5) = {solve_T_bruteforce(5)} (expected 3)")

# Try N=7,9,11
for N in [7, 9]:
    print(f"T({N}) = {solve_T_bruteforce(N)}")
