"""Verify T(5)=3 using R,C formulation with correct constraint"""
N = 5
lo = (N-1)*(N-1)
hi = N*N
CN = [[0]*N for _ in range(N)]
for x in range(N):
    for y in range(N):
        if lo <= x*x + y*y < hi:
            CN[x][y] = 1

S = [sum(CN[x]) % 2 for x in range(N)]
T = [sum(CN[x][y] for x in range(N)) % 2 for y in range(N)]
print(f"Row parities: {S}")
print(f"Col parities: {T}")
print(f"All rows same parity: {len(set(S))==1}")
print(f"All cols same parity: {len(set(T))==1}")

# For odd N, need S[x] = C_total for all x
# C_total can be 0 or 1, must match S[x]
c_total = S[0]  # must equal this
r_total = T[0]  # must equal this

best = N*N + 1
best_R = best_C = None

for r_mask in range(1 << N):
    R = [(r_mask >> x) & 1 for x in range(N)]
    # For odd N, R can be anything, but C must have correct parity
    for c_mask in range(1 << N):
        C = [(c_mask >> y) & 1 for y in range(N)]
        if sum(C) % 2 != c_total:
            continue
        cnt = 0
        for x in range(N):
            for y in range(N):
                if CN[x][y] ^ R[x] ^ C[y]:
                    cnt += 1
        if cnt < best:
            best = cnt
            best_R = R[:]
            best_C = C[:]

print(f"T(5) = {best}")
print(f"R = {best_R}")
print(f"C = {best_C}")

# Also verify F
F = [[CN[x][y] ^ best_R[x] ^ best_C[y] for y in range(N)] for x in range(N)]
print("F:")
for row in F:
    print(row)
# Verify row sums of F match R
for x in range(N):
    row_sum = sum(F[x]) % 2
    print(f"row {x}: F sum={row_sum}, R={best_R[x]}, match={row_sum==best_R[x]}")
