#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

const ll MOD = 982451653;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll N;
    cin >> N;

    // Brute force DP for verification (small N <= 60)
    // Uses __int128 for product comparison
    vector<i128> dp(N+1, 0);
    vector<ll> cnt(N+1, 0);
    dp[0] = 1;
    for (ll part = 1; part <= N; part++) {
        for (ll s = N; s >= part; s--) {
            if (dp[s-part] > 0) {
                i128 val = dp[s-part] * part;
                if (val > dp[s]) {
                    dp[s] = val;
                    cnt[s] = cnt[s-part] + 1;
                }
            }
        }
    }

    ll ans = 0;
    for (ll n = 1; n <= N; n++) {
        ans = (ans + (ll)(dp[n] % MOD) * (cnt[n] % MOD)) % MOD;
    }
    cout << ans << "\n";
    return 0;
}
