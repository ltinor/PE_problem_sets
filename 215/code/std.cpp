#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 215: Crack-free Walls
// Original: W(32,10) = 806844323190414
// Adapted: parameterized W, H; W ≤ 40, H ≤ 20
// Algorithm: DP over row patterns (bitmask of gap positions)

// Generate all gap masks for a row of width W using 2×1 and 3×1 bricks
void gen_patterns(int W, int pos, ll mask, vector<ll>& patterns) {
    if (pos == W) {
        patterns.push_back(mask);
        return;
    }
    if (pos > W) return;
    // Place 2×1 brick
    if (pos + 2 <= W) {
        int new_pos = pos + 2;
        ll new_mask = mask;
        if (new_pos < W) new_mask |= (1LL << new_pos);
        gen_patterns(W, new_pos, new_mask, patterns);
    }
    // Place 3×1 brick
    if (pos + 3 <= W) {
        int new_pos = pos + 3;
        ll new_mask = mask;
        if (new_pos < W) new_mask |= (1LL << new_pos);
        gen_patterns(W, new_pos, new_mask, patterns);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int W, H;
    cin >> W >> H;

    // Generate all valid row patterns
    vector<ll> patterns;
    gen_patterns(W, 0, 0, patterns);

    int P = patterns.size();

    // Build compatibility matrix
    vector<vector<int>> compat(P);
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < P; j++) {
            if ((patterns[i] & patterns[j]) == 0) {
                compat[i].push_back(j);
            }
        }
    }

    // DP: dp[pattern] for current height
    vector<ll> dp(P, 1); // height 1: all patterns valid

    for (int h = 2; h <= H; h++) {
        vector<ll> ndp(P, 0);
        for (int i = 0; i < P; i++) {
            if (dp[i] == 0) continue;
            for (int j : compat[i]) {
                ndp[j] += dp[i];
            }
        }
        dp = std::move(ndp);
    }

    ll ans = 0;
    for (int i = 0; i < P; i++) {
        ans += dp[i];
    }

    cout << ans << "\n";
}
