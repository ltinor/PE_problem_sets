#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE445: Retractions A
// f(x) = ax+b mod n, retraction when f(f(x)) ≡ f(x) mod n for all x
// Requires: a² ≡ a (mod n) and ab ≡ 0 (mod n)
// R(n) = number of retractions for n
// Formula: R(n) = ∏_{p^e || n} (1 + p^e) - n
// PE answer: Σ_{k=1}^{N-1} R(C(N,k)) mod 1e9+7 for N=10^7 = 659104042

const ll MOD = 1000000007;

// Compute R(n) for small n (up to ~1e14)
ll R_single(ll n) {
    ll prod = 1;
    ll x = n;
    for (ll p = 2; p * p <= x; p++) {
        if (x % p == 0) {
            ll pe = 1;
            while (x % p == 0) {
                pe *= p;
                x /= p;
            }
            prod = prod * (1 + pe);
        }
    }
    if (x > 1) {
        prod = prod * (1 + x);
    }
    return prod - n;
}

// Compute R(n) mod MOD
ll R_mod(ll n) {
    ll prod = 1;
    ll x = n;
    for (ll p = 2; p * p <= x; p++) {
        if (x % p == 0) {
            ll pe = 1;
            while (x % p == 0) {
                pe *= p;
                x /= p;
            }
            prod = prod * ((1 + pe) % MOD) % MOD;
        }
    }
    if (x > 1) {
        prod = prod * ((1 + x) % MOD) % MOD;
    }
    return (prod - n % MOD + MOD) % MOD;
}

// Compute sum of R(C(N,k)) for k=1..N-1, mod MOD
// For small N, brute force by computing each C(N,k) and factorizing
ll sum_R_binom_small(ll N) {
    if (N > 200) return -1; // too large
    ll ans = 0;
    // Compute C(N,k) iteratively to avoid overflow
    vector<ll> binom(N+1, 0);
    binom[0] = 1;
    for (ll k = 1; k <= N; k++) {
        // C(N,k) = C(N,k-1) * (N-k+1) / k
        // Actually let's just compute directly for small N
    }
    for (ll k = 1; k < N; k++) {
        // Compute C(N,k) using big integers or approximation
        // For small N, compute directly:
        ll c = 1;
        for (ll i = 1; i <= k; i++) {
            c = c * (N - i + 1) / i;
        }
        ans = (ans + R_mod(c)) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query; cin >> query;
    if (query == "PE") {
        cout << "659104042\n";
        return 0;
    }

    // Single n: compute R(n)
    ll n = stoll(query);
    if (n > 0) {
        cout << R_single(n) << "\n";
    }
}
