#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 10000000000000000LL; // 10^16 for last 16 digits

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, M;
    cin >> N >> M;

    // DP: dp[r] = number of subsets with sum ≡ r (mod M)
    vector<ll> dp(M, 0);
    dp[0] = 1; // empty subset

    for (ll i = 1; i <= N; i++) {
        // compute i^i mod M using fast pow
        ll val = 1, base = i % M, exp = i;
        while (exp > 0) {
            if (exp & 1) val = (val * base) % M;
            base = (base * base) % M;
            exp >>= 1;
        }

        vector<ll> ndp = dp;
        for (int r = 0; r < M; r++) {
            int nr = (r + val) % M;
            ndp[nr] = (ndp[nr] + dp[r]) % MOD;
        }
        dp = move(ndp);
    }

    // exclude empty subset
    ll ans = (dp[0] - 1 + MOD) % MOD;
    cout << ans << "\n";
    return 0;
}
