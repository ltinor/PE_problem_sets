#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Brute force O(R^4): enumerate all subtriangles
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R;
    cin >> R;

    int total = R * (R + 1) / 2;

    ll t = 0;
    vector<vector<ll>> tri(R);
    for (int i = 0; i < R; i++) {
        tri[i].resize(i + 1);
        for (int j = 0; j <= i; j++) {
            t = (615949LL * t + 797807) % (1 << 20);
            tri[i][j] = t - (1 << 19);
        }
    }

    ll ans = LLONG_MAX;

    // Enumerate all sub-triangles
    for (int i = 0; i < R; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 0; i + k < R; k++) {
                int row = i + k;
                int col_end = j + k;
                if (col_end > row) break;
                ll sum = 0;
                for (int r = i; r <= row; r++) {
                    for (int c = j; c <= j + (r - i); c++) {
                        sum += tri[r][c];
                    }
                }
                ans = min(ans, sum);
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
