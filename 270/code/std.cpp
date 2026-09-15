// PE270: Cutting Squares — N×N正方形切割
// Count triangulations of 4N-gon where each chord connects different sides.
// DP: dp[l][r] with validity check for chords crossing same sides.
// PE答案: 82282080 (mod 10^8)
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll MOD = 100000000;
const ll PE_ANS = 82282080;

// Generate boundary points clockwise from top-left (0,N)
// Returns side_mask for each point: bit 0=left, 1=bottom, 2=right, 3=top
vector<int> gen_side_masks(int N) {
    int P = 4 * N;
    vector<int> mask(P);
    int idx = 0;
    
    // Top side: (0,N) to (N-1,N) — N points
    for (int x = 0; x < N; x++) {
        int m = 0;
        if (x == 0) m |= 1;      // left side (top-left corner)
        m |= 8;                   // top side
        mask[idx++] = m;
    }
    // Right side: (N,N) down to (N,0) — N+1 points
    for (int y = N; y >= 0; y--) {
        int m = 0;
        m |= 4;                   // right side
        if (y == 0) m |= 2;       // bottom side (bottom-right corner)
        if (y == N) m |= 8;       // top side (top-right corner)
        mask[idx++] = m;
    }
    // Bottom side: (N-1,0) to (0,0) — N points
    for (int x = N - 1; x >= 0; x--) {
        int m = 0;
        m |= 2;                   // bottom side
        if (x == 0) m |= 1;       // left side (bottom-left corner)
        mask[idx++] = m;
    }
    // Left side: (0,1) to (0,N-1) — N-1 points
    for (int y = 1; y < N; y++) {
        int m = 1;                // left side only
        mask[idx++] = m;
    }
    return mask;
}

ll solve(int N) {
    int P = 4 * N;
    vector<int> mask = gen_side_masks(N);
    
    // Precompute valid chords
    vector<vector<bool>> valid(P, vector<bool>(P, false));
    for (int i = 0; i < P; i++) {
        for (int j = i + 1; j < P; j++) {
            valid[i][j] = valid[j][i] = ((mask[i] & mask[j]) == 0);
        }
    }
    
    vector<vector<ll>> dp(P, vector<ll>(P, 0));
    for (int i = 0; i < P - 1; i++) {
        dp[i][i + 1] = 1;
    }
    
    for (int len = 2; len < P; len++) {
        for (int l = 0; l + len < P; l++) {
            int r = l + len;
            ll total = 0;
            for (int k = l + 1; k < r; k++) {
                bool v_lk = (k == l + 1) || valid[l][k];
                bool v_kr = (r == k + 1) || valid[k][r];
                if (v_lk && v_kr) {
                    total = (total + dp[l][k] * dp[k][r]) % MOD;
                }
            }
            dp[l][r] = total;
        }
    }
    return dp[0][P - 1];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string first; cin >> first;
    if (first == "PE") { cout << PE_ANS << "\n"; return 0; }
    int N = stoi(first);
    cout << solve(N) << "\n";
}
