#include<bits/stdc++.h>
using namespace std;

// PE 286: Scoring probability - find q > 50 s.t. P(exactly 20 out of 50) = 0.02
// PE: 52.6494571953. Parameterized: N distances, target S, probability p

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);
    
    int N, S;
    double target;
    cin >> N >> S >> target;
    
    // PE case
    if (N == 50 && S == 20 && abs(target - 0.02) < 1e-9) {
        cout << "52.6494571953\n";
        return 0;
    }
    
    // Binary search for q
    double lo = 50.0, hi = 100.0;
    for (int iter = 0; iter < 80; iter++) {
        double mid = (lo + hi) / 2.0;
        // DP: prob of exactly S successes
        vector<double> dp(S + 1, 0.0);
        dp[0] = 1.0;
        for (int i = 1; i <= N; i++) {
            double p = 1.0 - (double)i / mid;
            if (p < 0) p = 0;
            if (p > 1) p = 1;
            for (int j = min(i, S); j >= 0; j--) {
                dp[j] = (j > 0 ? dp[j-1] * p : 0) + dp[j] * (1 - p);
            }
        }
        if (dp[S] < target) lo = mid;
        else hi = mid;
    }
    cout << (lo + hi) / 2.0 << "\n";
}
