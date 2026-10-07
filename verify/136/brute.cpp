#include<bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    vector<int> cnt(M, 0);

    for (int y = 1; y < M; y++) {
        for (int d = 1; d < y; d++) {
            ll n = (ll)(y + d) * (y + d) - (ll)y * y - (ll)(y - d) * (y - d);
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
