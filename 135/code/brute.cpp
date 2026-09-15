#include<bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, K;
    cin >> M >> K;

    // Brute force: enumerate x, y, z arithmetic progression
    // x = y + d, z = y - d (z > 0)
    // n = x^2 - y^2 - z^2 = y(4d - y)
    // Enumerate y and d, same as std
    // But simpler: enumerate all arithmetic progressions

    vector<int> cnt(M, 0);

    // For arithmetic progression: x = y + d, z = y - d
    // y is the middle term, d is the difference
    // We need z > 0 => y > d
    for (int y = 1; y < M; y++) {
        for (int d = 1; d < y; d++) {
            // x = y + d, z = y - d
            ll n = (ll)(y + d) * (y + d) - (ll)y * y - (ll)(y - d) * (y - d);
            // n = y(4d - y), which is same as above but n > 0 requires 4d > y
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
