#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 982451653;

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) { if (e & 1) r = r * a % MOD; a = a * a % MOD; e >>= 1; }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll N;
    cin >> N;

    ll K = 1;
    while (K * (K + 3) / 2 <= N) K++;
    K += 3;
    vector<ll> fact(K + 1), inv_fact(K + 1);
    fact[0] = 1;
    for (ll i = 1; i <= K; i++) fact[i] = fact[i-1] * i % MOD;
    inv_fact[K] = modpow(fact[K], MOD - 2);
    for (ll i = K; i >= 1; i--) inv_fact[i-1] = inv_fact[i] * i % MOD;

    ll ans = 0;

    // Handle n = 1..4 manually
    for (ll n = 1; n <= min(4LL, N); n++) ans = (ans + n) % MOD;

    for (ll k = 2; ; k++) {
        ll base = k * (k + 3) / 2;
        if (base > N) break;

        // r = 0..k
        ll limit = min(k, N - base);
        for (ll r = 0; r <= limit; r++) {
            ll prod = fact[k+1-r] * fact[k+2] % MOD * inv_fact[k+2-r] % MOD;
            ans = (ans + k * prod) % MOD;
        }

        // Gap value
        ll n_gap = base + k + 1;
        ll next_base = (k + 1) * (k + 4) / 2;
        if (n_gap <= N && n_gap < next_base) {
            ll gap_prod = fact[k+3] * modpow(2*k+4, MOD-2) % MOD;
            ans = (ans + k * gap_prod) % MOD;
        }
    }

    cout << ans << "\n";
    return 0;
}
