#include<bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    // n = x^2 - y^2 - z^2 where x, y, z are arithmetic progression
    // x = y+d, z = y-d, n = y(4d - y)
    // Count solutions per n, find n with exactly 1 solution

    vector<int> cnt(M, 0);

    for (int y = 1; y < M; y++) {
        int min_d = y / 4 + 1;  // smallest d with 4d > y
        if (min_d >= y) continue;
        ll yy = (ll)y * y;
        int max_d_val = min(y - 1, (int)((M - 1LL + yy) / (4LL * y)));
        for (int d = min_d; d <= max_d_val; d++) {
            ll n = (ll)y * (4LL * d - y);
            if (n > 0 && n < M) {
                cnt[n]++;
            }
        }
    }

    int ans = 0;
    for (int n = 1; n < M; n++) {
        if (cnt[n] == 1) ans++;
    }

    cout << ans << "\n";
    return 0;
}
