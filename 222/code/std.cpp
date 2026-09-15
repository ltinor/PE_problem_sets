#include<bits/stdc++.h>
using namespace std;

// Sphere Packing - Bitmask DP
// N balls radii 30..30+N-1, pipe radius R
// Distance between centers: h = sqrt((ri+rj)^2 - (2R - ri - rj)^2)
// Pipe length: r_first + sum(h) + r_last (in mm)
// Output: round(length * 1000) micrometers

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, R;
    cin >> N >> R;

    vector<int> r(N);
    for(int i = 0; i < N; i++) r[i] = 30 + i;

    // Precompute distances between balls
    vector<vector<double>> h(N, vector<double>(N, 0));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(i == j) continue;
            double sum_r = r[i] + r[j];
            double horiz = 2.0 * R - r[i] - r[j];
            double val = sum_r * sum_r - horiz * horiz;
            if(val <= 0) h[i][j] = 1e18; // infeasible
            else h[i][j] = sqrt(val);
        }
    }

    int full = (1 << N) - 1;
    // dp[mask][last] = min pipe length for subset mask, ending at ball last
    // Use double with large sentinel
    const double INF = 1e18;
    vector<vector<double>> dp(1 << N, vector<double>(N, INF));

    // Initialize with single balls
    for(int i = 0; i < N; i++) {
        dp[1 << i][i] = 2.0 * r[i];
    }

    for(int mask = 1; mask < (1 << N); mask++) {
        for(int last = 0; last < N; last++) {
            if(dp[mask][last] >= INF) continue;
            if(!(mask & (1 << last))) continue;

            for(int nxt = 0; nxt < N; nxt++) {
                if(mask & (1 << nxt)) continue;
                double new_len = dp[mask][last] - r[last] + h[last][nxt] + r[nxt];
                int nmask = mask | (1 << nxt);
                if(new_len < dp[nmask][nxt]) {
                    dp[nmask][nxt] = new_len;
                }
            }
        }
    }

    double ans = INF;
    for(int i = 0; i < N; i++) {
        ans = min(ans, dp[full][i]);
    }

    // Convert mm to micrometers and round
    long long result = (long long)round(ans * 1000.0);
    cout << result << "\n";

    return 0;
}
