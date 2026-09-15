#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Brute force for PE477: compute F(N) via DP for small N.
// This is O(N^2) and works for N up to ~2000.

const ll MOD = 1000000007LL;

int main() {
    ll N; cin >> N;

    // Generate sequence
    vector<ll> S(N+1);
    S[1] = 0;
    for (ll i = 1; i < N; i++) {
        i128 val = (i128)S[i] * S[i] + 45;
        S[i+1] = (ll)(val % MOD);
    }

    // DP
    vector<vector<ll>> dp(N+2, vector<ll>(N+2, 0));
    vector<ll> pref(N+1, 0);
    for (ll i = 1; i <= N; i++) pref[i] = pref[i-1] + S[i];

    auto sum = [&](ll l, ll r) { return pref[r] - pref[l-1]; };

    for (ll len = 1; len <= N; len++) {
        for (ll l = 1; l + len - 1 <= N; l++) {
            ll r = l + len - 1;
            if (len == 1) {
                dp[l][r] = S[l];
            } else {
                ll left = S[l] + sum(l+1, r) - dp[l+1][r];
                ll right = S[r] + sum(l, r-1) - dp[l][r-1];
                dp[l][r] = max(left, right);
            }
        }
    }
    cout << dp[1][N] << "\n";
}
