"""Check row/col parities for CN"""
def analyze(N):
    lo = (N-1)*(N-1)
    hi = N*N
    row_sums = []
    col_sums = []
    for x in range(N):
        cnt = 0
        for y in range(N):
            if lo <= x*x + y*y < hi:
                cnt += 1
        row_sums.append(cnt)
    for y in range(N):
        cnt = 0
        for x in range(N):
            if lo <= x*x + y*y < hi:
                cnt += 1
        col_sums.append(cnt)
    print(f"N={N}:")
    print(f"  row sums: {row_sums}")
    print(f"  row parities: {[s%2 for s in row_sums]}")
    print(f"  all rows same parity: {len(set(s%2 for s in row_sums))==1}")
    print(f"  col sums: {col_sums}")
    print(f"  col parities: {[s%2 for s in col_sums]}")
    print(f"  all cols same parity: {len(set(s%2 for s in col_sums))==1}")
    print()

for N in [3, 5, 7, 10, 15, 31]:
    analyze(N)
