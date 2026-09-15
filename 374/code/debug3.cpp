#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;
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

    // Brute force for reference
    vector<i128> dp(N+1, 0);
    vector<ll> cnt(N+1, 0);
    dp[0] = 1;
    for (ll part = 1; part <= N; part++)
        for (ll s = N; s >= part; s--)
            if (dp[s-part] > 0) {
                i128 val = dp[s-part] * part;
                if (val > dp[s]) { dp[s] = val; cnt[s] = cnt[s-part] + 1; }
            }

    // Analytic formula
    ll K = 1;
    while (K * (K + 3) / 2 <= N) K++;
    K += 3;
    vector<ll> fact(K+1), inv_fact(K+1);
    fact[0] = 1;
    for (ll i = 1; i <= K; i++) fact[i] = fact[i-1] * i % MOD;
    inv_fact[K] = modpow(fact[K], MOD-2);
    for (ll i = K; i >= 1; i--) inv_fact[i-1] = inv_fact[i] * i % MOD;

    ll ans_anal = 0;
    for (ll k = 2; ; k++) { // start from k=2, handle 1-4 manually
        ll base = k * (k + 3) / 2;
        if (base > N) break;
        for (ll r = 0; r <= k; r++) {
            ll n = base + r;
            if (n > N) break;
            ll prod = fact[k+1-r] * fact[k+2] % MOD * inv_fact[k+2-r] % MOD;
            ans_anal = (ans_anal + k * prod) % MOD;
        }
        ll n_gap = base + k + 1;
        if (n_gap <= N && n_gap > base + k) { // gap exists only if n_gap < next_base
            ll next_base = (k+1)*(k+4)/2;
            if (n_gap < next_base) {
                ll gap_prod = fact[k+3] * modpow(2*k+4, MOD-2) % MOD;
                ans_anal = (ans_anal + k * gap_prod) % MOD;
            }
        }
    }
    // Handle n=1..4 manually: f(n)=n, m(n)=1, term=n
    for (ll n = 1; n <= min(4LL, N); n++)
        ans_anal = (ans_anal + n) % MOD;

    ll ans_brute = 0;
    for (ll n = 1; n <= N; n++)
        ans_brute = (ans_brute + (ll)(dp[n] % MOD) * (cnt[n] % MOD)) % MOD;

    // Compare per-n
    cout << "Brute: " << ans_brute << endl;
    cout << "Anal:  " << ans_anal << endl;
    if (ans_brute != ans_anal) {
        cout << "MISMATCH!" << endl;
        // Print per-n comparison
        for (ll n = 1; n <= N; n++) {
            ll bterm = (ll)(dp[n] % MOD) * (cnt[n] % MOD) % MOD;
            // Compute analytic per-n
            ll aterm = 0;
            // Find k for this n
            for (ll k = 2; ; k++) {
                ll base = k*(k+3)/2;
                if (base > n) break;
                if (n <= base + k) {
                    ll r = n - base;
                    aterm = k * fact[k+1-r] % MOD * fact[k+2] % MOD * inv_fact[k+2-r] % MOD;
                    break;
                }
                if (n == base + k + 1 && base + k + 1 < (k+1)*(k+4)/2) {
                    aterm = k * fact[k+3] % MOD * modpow(2*k+4, MOD-2) % MOD;
                    break;
                }
            }
            if (n <= 4) aterm = n;
            if (bterm != aterm) {
                cout << "n=" << n << " brute=" << bterm << " anal=" << aterm << " dp=" << (ll)dp[n] << " cnt=" << cnt[n] << endl;
            }
        }
    }
    return 0;
}
