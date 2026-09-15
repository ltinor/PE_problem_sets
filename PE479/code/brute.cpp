#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Brute force for PE479: compute S(n) for small n
// using the derived formula S(n) = Σ (1-k^2)^p

const ll MOD = 1000000007LL;

ll modpow(ll a, ll b) {
    ll r = 1;
    while (b) {
        if (b & 1) r = (i128)r * a % MOD;
        a = (i128)a * a % MOD;
        b >>= 1;
    }
    return r;
}

ll modinv(ll a) {
    return modpow(a, MOD - 2);
}

int main() {
    ll n; cin >> n;

    // Direct computation of S(n) from definition
    // S(n) = Σ_{k=1}^n Σ_{p=1}^n (1-k^2)^p
    // Geometric series: r(r^n - 1)/(r-1) where r = 1-k^2
    ll total = 0;
    for (ll k = 1; k <= n; k++) {
        ll k2 = (i128)k * k % MOD;
        ll r = (1 - k2 + MOD) % MOD;
        // r = 0 when k=1 (since 1-1=0)
        ll num = r * (modpow(r, n) - 1 + MOD) % MOD;
        ll den = (r - 1 + MOD) % MOD;
        ll term = num * modinv(den) % MOD;
        total = (total + term) % MOD;
    }
    cout << total << "\n";
}
