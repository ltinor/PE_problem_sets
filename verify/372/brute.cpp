#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll M, N;
    cin >> M >> N;

    ll ans = 0;
    for (ll x = M + 1; x <= N; x++) {
        for (ll y = M + 1; y <= N; y++) {
            ll val = (y * y) / (x * x);
            if (val & 1) ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}
