#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

// DP: F(M, n) = number of ways to fill row of length n with min red block M
ull F(int M, int n) {
    vector<ull> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i-1]; // black at end
        for (int j = M; j <= i; j++) {
            if (i - j - 1 >= 0)
                dp[i] += dp[i - j - 1];
            else
                dp[i] += 1;
        }
    }
    return dp[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    ull K;
    cin >> M >> K;

    // Find smallest n such that F(M, n) > K
    int n = M;
    while (true) {
        if (F(M, n) > K) {
            cout << n << "\n";
            break;
        }
        n++;
    }
    return 0;
}
