#include<bits/stdc++.h>
using namespace std;

#define ll long long

// PE 150: Minimum sub-triangle sum
// Triangle array generated with lagged fibonacci:
// t_k = (615949*t_{k-1} + 797807) mod 2^20, s_k = t_k - 2^19
// Fill triangle row by row

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R;
    cin >> R;

    int total = R * (R + 1) / 2;

    // Generate sequence
    ll t = 0;
    vector<vector<ll>> tri(R);
    for (int i = 0; i < R; i++) {
        tri[i].resize(i + 1);
        for (int j = 0; j <= i; j++) {
            t = (615949LL * t + 797807) % (1 << 20);
            tri[i][j] = t - (1 << 19);
        }
    }

    // Prefix sums for each row
    // pre[i][j] = sum of tri[i][0..j]
    vector<vector<ll>> pre(R);
    for (int i = 0; i < R; i++) {
        pre[i].resize(i + 1);
        pre[i][0] = tri[i][0];
        for (int j = 1; j <= i; j++) {
            pre[i][j] = pre[i][j-1] + tri[i][j];
        }
    }

    // O(R^3): for each starting position (i,j), expand downward
    ll ans = LLONG_MAX;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j <= i; j++) {
            ll sum = 0;
            // Expand downward row by row
            for (int k = 0; i + k < R; k++) {
                // Row i+k, columns j..j+k
                int row = i + k;
                int col_end = j + k;
                if (col_end > row) break;
                ll row_sum = pre[row][col_end] - (j > 0 ? pre[row][j-1] : 0);
                sum += row_sum;
                ans = min(ans, sum);
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
