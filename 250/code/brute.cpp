#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, M;
    cin >> N >> M;

    // compute all values i^i mod M
    vector<ll> vals;
    for (ll i = 1; i <= N; i++) {
        ll val = 1, base = i % M, exp = i;
        while (exp > 0) {
            if (exp & 1) val = (val * base) % M;
            base = (base * base) % M;
            exp >>= 1;
        }
        vals.push_back(val);
    }

    ll ans = 0;
    int tot = 1 << N;
    for (int mask = 1; mask < tot; mask++) {
        ll sum = 0;
        for (int j = 0; j < N; j++) {
            if (mask & (1 << j)) {
                sum = (sum + vals[j]) % M;
            }
        }
        if (sum == 0) ans++;
    }
    cout << ans << "\n";
    return 0;
}
