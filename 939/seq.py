import sys

def compute_E(N):
    # dp[total][n+N][o], o in {0,1}
    OFF = N
    dp = [[[0,0] for _ in range(2*N+1)] for _ in range(N+1)]
    dp[0][OFF][0] = 1
    for k in range(1, N+1):
        km1 = k-1
        par = k & 1
        # A-pile of size k: total+k, n+km1, o^par
        for t in range(k, N+1):
            dpt = dp[t]; dptk = dp[t-k]
            for n in range(2*N+1):
                src = n - km1
                if 0 <= src <= 2*N:
                    # o=0
                    dpt[n][0] += dptk[src][0 ^ par]
                    dpt[n][1] += dptk[src][1 ^ par]
        # B-pile of size k: total+k, n-km1, o^par
        for t in range(k, N+1):
            dpt = dp[t]; dptk = dp[t-k]
            for n in range(2*N+1):
                src = n + km1
                if 0 <= src <= 2*N:
                    dpt[n][0] += dptk[src][0 ^ par]
                    dpt[n][1] += dptk[src][1 ^ par]
    ans = 0
    for t in range(0, N+1):
        for n in range(2*N+1):
            real_n = n - OFF
            # win iff n>=2 or (n==1 and o==0)
            for o in (0,1):
                if (real_n >= 2) or (real_n == 1 and o == 0):
                    ans += dp[t][n][o]
    return ans

for N in range(1, 21):
    print(f"E({N}) = {compute_E(N)}")
