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

print("Method 1: exact 2^n, (-n) % MOD")
total = 0
for n in range(1, 31):
    two_n = 1 << n
    M = [[two_n % MOD, 0, (-n) % MOD], [1, 0, 0], [0, 1, 0]]
    S2 = (two_n * two_n) % MOD
    S1 = two_n % MOD
    S0 = 3 % MOD
    if K == 0: Sk = S0
    elif K == 1: Sk = S1
    elif K == 2: Sk = S2
    else:
        Mp = mat_pow(M, K-2)
        Sk = (Mp[0][0] * S2 + Mp[0][1] * S1 + Mp[0][2] * S0) % MOD
    total = (total + Sk) % MOD
    print(f"  n={n}: Sk={Sk}")
print(f"  Total: {total}")
