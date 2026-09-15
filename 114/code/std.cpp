#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

// DP: dp[i] = number of ways to fill a row of length i
// dp[0] = 1 (empty row)
// dp[i] = dp[i-1] (put black at end) + sum_{j=M}^{i} dp[i-j-1] (put red block of length j at end)
// where dp[-1] = 1 (a red block starting from position 1)

ull solve(int N, int M) {
    vector<ull> dp(N + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= N; i++) {
        // Option 1: black square at position i
        dp[i] = dp[i-1];
        // Option 2: red block of length j ending at position i
        for (int j = M; j <= i; j++) {
            if (i - j - 1 >= 0)
                dp[i] += dp[i - j - 1];
            else
                dp[i] += 1; // red block fills from start
        }
    }
    return dp[N];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    cout << solve(N, M) << "\n";
    return 0;
}
