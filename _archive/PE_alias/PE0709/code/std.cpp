#include <bits/stdc++.h>
using namespace std;
#define ll long long

// f(n) = number of packings of n bags
// f(0) = 1
// f(n) = (1/2) * sum_{k=0}^{n-1} C(n-1, k) * f(k) * f(n-1-k)  for n >= 1
// Mod M = 1020202009

const ll MOD = 1020202009;
const int N = 24680;

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<ll> f(N + 1);
    f[0] = 1;
    f[1] = 1;
    
    // Precompute factorials and inverse factorials for combinations
    vector<ll> fact(N + 1), invfact(N + 1);
    fact[0] = 1;
    for (int i = 1; i <= N; i++)
        fact[i] = fact[i-1] * i % MOD;
    invfact[N] = modpow(fact[N], MOD - 2);
    for (int i = N; i >= 1; i--)
        invfact[i-1] = invfact[i] * i % MOD;
    
    auto C = [&](int n, int k) -> ll {
        if (k < 0 || k > n) return 0;
        return fact[n] * invfact[k] % MOD * invfact[n-k] % MOD;
    };
    
    ll inv2 = modpow(2, MOD - 2);
    
    for (int n = 2; n <= N; n++) {
        ll sum = 0;
        for (int k = 0; k < n; k++) {
            sum = (sum + C(n-1, k) * f[k] % MOD * f[n-1-k]) % MOD;
        }
        f[n] = sum * inv2 % MOD;
    }
    
    cout << f[N] << "\n";
    return 0;
}
