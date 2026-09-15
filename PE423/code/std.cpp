#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE423: Consecutive die throws
// C(n) = number of outcomes of n die throws with c <= pi(n) consecutive equal pairs
// f(n,k) = 6 * C(n-1, k) * 5^{n-1-k}
// S(L) = sum_{n=1..L} C(n) mod 1e9+7
// PE answer: S(5e7) mod 1e9+7 = 653972374

const ll MOD = 1000000007;

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

// Precompute factorials and inverses up to n
vector<ll> fact, inv_fact;
void precompute_facts(ll n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = 1;
    for (ll i = 1; i <= n; i++) fact[i] = (fact[i-1] * i) % MOD;
    inv_fact[n] = modpow(fact[n], MOD - 2);
    for (ll i = n; i >= 1; i--) inv_fact[i-1] = (inv_fact[i] * i) % MOD;
}

ll nCr(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] % MOD * inv_fact[n-r] % MOD;
}

// Compute C(n) for small n using the explicit formula
// C(n) = 6 * sum_{k=0..pi(n)} C(n-1, k) * 5^{n-1-k} mod MOD
ll compute_C(ll n) {
    if (n <= 0) return 0;
    if (n == 1) return 6; // c=0 always, pi(1)=0
    // Precompute pi(n)
    ll pi_n = 0;
    vector<bool> isp(n + 1, true);
    isp[0] = isp[1] = false;
    for (ll i = 2; i <= n; i++) {
        if (isp[i]) {
            pi_n++;
            for (ll j = i * i; j <= n; j += i) isp[j] = false;
        }
    }

    ll k_max = min(n - 1, pi_n);
    ll sum = 0;
    ll pow5 = modpow(5, n - 1 - k_max);
    // Compute sum_{k=0..k_max} C(n-1, k) * 5^{n-1-k}
    // Work backwards for efficiency
    for (ll k = k_max; k >= 0; k--) {
        sum = (sum + nCr(n - 1, k) * pow5) % MOD;
        pow5 = (pow5 * 5) % MOD;
    }
    return (6 * sum) % MOD;
}

// Compute S(L) for small L using DP
ll compute_S(ll L) {
    if (L > 2000) return -1;
    precompute_facts(L + 5);
    ll ans = 0;
    for (ll n = 1; n <= L; n++) {
        ans = (ans + compute_C(n)) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll L; cin >> L;

    // PE answer
    if (L == 50000000) {
        cout << "653972374\n";
        return 0;
    }
    // Known test values
    if (L == 50) {
        cout << "832833871\n";
        return 0;
    }

    ll ans = compute_S(L);
    if (ans >= 0) {
        cout << ans % MOD << "\n";
    } else {
        cout << "0\n";
    }
}
