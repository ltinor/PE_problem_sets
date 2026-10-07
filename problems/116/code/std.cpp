#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

ull count_ways(int n, int L) {
    vector<ull> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        if (i >= L) dp[i] += dp[i - L];
    }
    return dp[n] - 1;  // exclude all-black
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    ull ans = count_ways(N, 2) + count_ways(N, 3) + count_ways(N, 4);
    cout << ans << "\n";
    return 0;
}
