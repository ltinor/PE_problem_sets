#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

// Independent brute: same DP with different structure
ull ways(int N, int M) {
    // dp[i] = ways for length i
    vector<ull> f(N + 1, 0);
    f[0] = 1;
    for (int n = 1; n <= N; n++) {
        // black at position n
        f[n] = f[n-1];
        // red block ending at n, length L
        for (int L = M; L <= n; L++) {
            f[n] += (n - L - 1 >= 0) ? f[n - L - 1] : 1ULL;
        }
    }
    return f[N];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    cout << ways(N, M) << "\n";
    return 0;
}
