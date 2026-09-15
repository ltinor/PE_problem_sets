#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<ull> dp(N + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= N; i++) {
        dp[i] = dp[i - 1];
        if (i >= 2) dp[i] += dp[i - 2];
        if (i >= 3) dp[i] += dp[i - 3];
        if (i >= 4) dp[i] += dp[i - 4];
    }
    cout << dp[N] << "\n";
    return 0;
}
