#include<bits/stdc++.h>
using namespace std;

// Brute force: DP for small k, n
// dp[i][a][b] = probability after i defects, a chips have 1, b chips have 2
// But memory is an issue. Use DP with states collapsed.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    cin >> k >> n;

    // Use map-based DP: state (a, b) -> probability
    // a = chips with 1 defect, b = chips with 2 defects
    // After placing i defects: a + 2b = i, a + b <= n

    // dp[i] = map from (b) to probability (a = i - 2b)
    vector<unordered_map<int, double>> dp(k + 1);
    dp[0][0] = 1.0;

    for (int i = 0; i < k; i++) {
        for (auto& [b, prob] : dp[i]) {
            if (prob == 0) continue;
            int a = i - 2 * b;

            // Place next defect to:
            // 1) empty chip: a+b chips used, (n - a - b) empty
            int empty = n - a - b;
            if (empty > 0) {
                dp[i + 1][b] += prob * empty / n;
            }
            // 2) chip with 1 defect: a such chips
            if (a > 0) {
                dp[i + 1][b + 1] += prob * a / n;
            }
            // 3) chip with 2 defects: not allowed (would make 3)
            // (probability goes to failure state)
        }
    }

    // Sum probabilities of all states (no chip has >=3)
    double p_ok = 0.0;
    for (auto& [b, prob] : dp[k]) {
        p_ok += prob;
    }

    double ans = 1.0 - p_ok;
    if (ans < 0) ans = 0.0;
    if (ans > 1) ans = 1.0;

    cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}
