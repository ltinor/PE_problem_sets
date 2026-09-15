"""Efficient row parity check for 2^k-1"""
import math

def row_count_parity(N, x):
    """Count black cells in row x, return parity"""
    lo = (N-1)*(N-1) - x*x
    hi = N*N - x*x
    
    if hi <= 0:
        return 0
    
    y_lo = 0
    if lo > 0:
        y_lo = math.isqrt(lo - 1) + 1  # smallest y with y² >= lo
    
    y_hi = math.isqrt(hi - 1)  # largest y with y² < hi
    if y_hi * y_hi >= hi:
        y_hi -= 1
    
    y_lo = max(0, y_lo)
    y_hi = min(N-1, y_hi)
    
    if y_lo > y_hi:
        return 0
    
    return (y_hi - y_lo + 1) % 2

def is_solvable(N):
    first_parity = row_count_parity(N, 0)
    for x in range(1, N):
        if row_count_parity(N, x) != first_parity:
            return False
    return True

print("Checking 2^k-1:")
for k in range(2, 16):
    N = (1 << k) - 1
    solvable = is_solvable(N)
    print(f"k={k:2d}, N={N:6d}, solvable={solvable}")
