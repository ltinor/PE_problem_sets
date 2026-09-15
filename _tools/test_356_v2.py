# Compare Python vs C++ for PE356
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

for n in range(1, 31):
    # Compute tn same way as C++ (loop mod)
    tn = 1
    for i in range(n):
        tn = (tn * 2) % MOD
    
    M = [[tn, 0, (MOD - n % MOD) % MOD], [1, 0, 0], [0, 1, 0]]
    S2 = tn * tn % MOD
    S1 = tn
    S0 = 3 % MOD
    
    if K == 0:
        Sk = S0
    elif K == 1:
        Sk = S1
    elif K == 2:
        Sk = S2
    else:
        Mp = mat_pow(M, K - 2)
        Sk = (Mp[0][0] * S2 + Mp[0][1] * S1 + Mp[0][2] * S0) % MOD
    
    print(f"n={n}: Sk={Sk}")

# Also compute with direct 2^n (exact then mod)
total1 = 0
total2 = 0
for n in range(1, 31):
    tn1 = 1
    for i in range(n):
        tn1 = (tn1 * 2) % MOD
    tn2 = (1 << n) % MOD
    if tn1 != tn2:
        print(f"n={n}: tn1={tn1}, tn2={tn2}")
    
    M1 = [[tn1, 0, (MOD - n % MOD) % MOD], [1, 0, 0], [0, 1, 0]]
    M2 = [[tn2, 0, (MOD - n % MOD) % MOD], [1, 0, 0], [0, 1, 0]]
    
    S2_1 = tn1 * tn1 % MOD
    S1_1 = tn1
    S0_1 = 3
    S2_2 = tn2 * tn2 % MOD
    S1_2 = tn2
    S0_2 = 3
    
    if K == 0:
        Sk1, Sk2 = S0_1, S0_2
    elif K == 1:
        Sk1, Sk2 = S1_1, S1_2
    elif K == 2:
        Sk1, Sk2 = S2_1, S2_2
    else:
        Mp1 = mat_pow(M1, K - 2)
        Mp2 = mat_pow(M2, K - 2)
        Sk1 = (Mp1[0][0] * S2_1 + Mp1[0][1] * S1_1 + Mp1[0][2] * S0_1) % MOD
        Sk2 = (Mp2[0][0] * S2_2 + Mp2[0][1] * S1_2 + Mp2[0][2] * S0_2) % MOD
    
    if Sk1 != Sk2:
        print(f"n={n}: Sk1={Sk1}, Sk2={Sk2}, tn1={tn1}, tn2={tn2}")
    total1 = (total1 + Sk1) % MOD
    total2 = (total2 + Sk2) % MOD

print(f"Total1 (loop): {total1}")
print(f"Total2 (1<<n): {total2}")
