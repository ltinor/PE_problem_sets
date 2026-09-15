# PE 356: compute sum of floor(a_n^K) for n=1..30, last 8 digits
MOD = 10**8
K = 987654321

def mat_mul(A, B):
    return [[sum(A[i][k]*B[k][j] for k in range(3)) % MOD for j in range(3)] for i in range(3)]

def mat_pow(M, e):
    R = [[1,0,0],[0,1,0],[0,0,1]]
    while e:
        if e & 1:
            R = mat_mul(R, M)
        M = mat_mul(M, M)
        e >>= 1
    return R

total = 0
for n in range(1, 31):
    two_n = 1 << n
    M = [[two_n % MOD, 0, (-n) % MOD], [1, 0, 0], [0, 1, 0]]
    S2 = (two_n * two_n) % MOD
    S1 = two_n % MOD
    S0 = 3 % MOD
    
    if K == 0:
        Sk = S0
    elif K == 1:
        Sk = S1
    elif K == 2:
        Sk = S2
    else:
        Mp = mat_pow(M, K-2)
        Sk = (Mp[0][0] * S2 + Mp[0][1] * S1 + Mp[0][2] * S0) % MOD
    
    # n=1: other root is 1, so S_K = a_1^K + 1^K + ...
    if n == 1:
        floor_val = (Sk - 1) % MOD
    else:
        floor_val = Sk % MOD
    
    total = (total + floor_val) % MOD
    print(f"n={n}: S_K mod 1e8 = {Sk}, floor = {floor_val}")

print(f"\nTotal (mod 10^8): {total}")
print(f"Expected: 28010159")
