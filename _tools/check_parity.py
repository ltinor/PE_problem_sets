"""Check which 2^k-1 have consistent row parities"""
import math

def check_row_parities(N):
    lo = (N-1)*(N-1)
    hi = N*N
    parities = set()
    for x in range(N):
        cnt = 0
        for y in range(N):
            if lo <= x*x + y*y < hi:
                cnt += 1
        parities.add(cnt % 2)
    return len(parities) == 1, parities

print("k, N=2^k-1, all_rows_same_parity, parity_set")
for k in range(2, 15):
    N = (1 << k) - 1
    ok, pset = check_row_parities(N)
    print(f"k={k}, N={N}, same={ok}, parity_set={pset}")
