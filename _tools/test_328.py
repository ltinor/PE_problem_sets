# Debug PE 328 C(n) values
C = [0]*101
D = [0]*101
best_k = [0]*101
C[0]=0; D[0]=0
C[1]=0; D[1]=0; best_k[1]=1
C[2]=1; D[2]=1; best_k[2]=1
C[3]=2; D[3]=1; best_k[3]=2

for n in range(4, 101):
    best = 10**18
    best_d = 0
    bk = 1
    for k in range(1, n+1):
        left = k + (C[k-1] if k>1 else 0)
        m = n-k
        if m==0:
            right = k
            rd = 0
        elif m==1:
            right = k
            rd = 0
        else:
            right = k*(D[m]+1) + C[m]
            rd = 1 + D[m]
        worst = max(k, left, right)
        wd = 1
        if worst == left and k>1: wd = 1 + D[k-1]
        elif worst == right and m>1: wd = rd
        
        if worst < best or (worst == best and wd < best_d):
            best = worst
            best_d = wd
            bk = k
    C[n] = best
    D[n] = best_d
    best_k[n] = bk

print("n: C(n), D(n), best_k")
for n in [1,2,3,4,5,6,7,8,10,20,50,100]:
    print(f"n={n}: C={C[n]}, D={D[n]}, k={best_k[n]}")

# Check: should C(4)=4, C(5)=6, C(6)=8, C(7)=10?
print()
print("C(4..12):", [C[i] for i in range(4,13)])
print("Expected:   [4, 6, 8, 10, 12, 14, 16, 18, 20]")
