"""Check row parities for 2^k-1 in detail"""
import math

def analyze(N):
    lo = (N-1)*(N-1)
    hi = N*N
    row_counts = []
    col_counts = []
    for x in range(N):
        cnt = 0
        for y in range(N):
            if lo <= x*x + y*y < hi:
                cnt += 1
        row_counts.append(cnt)
    for y in range(N):
        cnt = 0
        for x in range(N):
            if lo <= x*x + y*y < hi:
                cnt += 1
        col_counts.append(cnt)
    row_par = [c % 2 for c in row_counts]
    col_par = [c % 2 for c in col_counts]
    all_same_row = len(set(row_par)) == 1
    all_same_col = len(set(col_par)) == 1
    return all_same_row and all_same_col, row_counts, col_counts

print("Checking 2^k-1 for k=2..15:")
print("k, N, solvable, row_counts(first 10)")
for k in range(2, 16):
    N = (1 << k) - 1
    solvable, rows, cols = analyze(N)
    print(f"k={k:2d}, N={N:6d}, solvable={solvable}, rows[:10]={rows[:10]}, rows[-5:]={rows[-5:]}")
