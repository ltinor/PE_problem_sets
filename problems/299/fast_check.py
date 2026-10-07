from math import isqrt

def count_fast(N):
    total = 0
    # Case 1: a even, u=v=a/2, alpha*beta = a^2/2, alpha+beta < N-2a
    for a in range(2, N, 2):
        M = a*a // 2
        lim = N - 2*a  # alpha+beta < lim
        if lim <= 2:
            break  # increasing a decreases lim, once too small, done? not monotonic safely
        # enumerate divisors alpha of M
        for alpha in range(1, isqrt(M)+1):
            if M % alpha == 0:
                beta = M // alpha
                if alpha + beta < lim:
                    if alpha == beta:
                        total += 1
                    else:
                        total += 2  # (alpha,beta) and (beta,alpha)
    # Case 2: b=d, k=b-a, k^2=2uv, a^2-2k^2=s^2, 2(a+k)<N
    for a in range(1, N):
        # 2(a+k) < N -> k < N/2 - a
        kmax = (N - 1)//2 - a  # k <= floor((N-1)/2 - a) ... let's just loop k
        if kmax <= 0:
            break
        for k in range(1, kmax+1):
            D = a*a - 2*k*k
            if D < 0:
                break  # k increasing -> D decreasing, break
            s = isqrt(D)
            if s*s == D and s >= 1:
                total += 1
    return total

for N in [10, 20, 50, 100]:
    print(N, count_fast(N))
print("N=100000 ->", count_fast(100000))
