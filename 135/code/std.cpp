#include<bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, K;
    cin >> M >> K;

    // n = x^2 - y^2 - z^2 where x, y, z are arithmetic progression
    // y = middle term, d = difference
    // x = y + d, z = y - d
    // n = (y+d)^2 - y^2 - (y-d)^2 = y(4d - y)
    // n > 0 requires 4d > y
    // Count solutions per n

    vector<int> cnt(M, 0);

    // Enumerate y from 1 to M-1
    for (int y = 1; y < M; y++) {
        // Constraints: d < y (for z = y-d > 0), and 4d > y (for n > 0)
        // Also n = y(4d-y) < M => 4d < M/y + y
        int min_d = y / 4 + 1;  // smallest d with 4d > y
        if (min_d >= y) continue;  // no valid d
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
        if (cnt[n] == K) ans++;
    }

    cout << ans << "\n";
    return 0;
}
