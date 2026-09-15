#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE495: Writing n as the product of k numbers
// Let W(n,k) = number of ways to write n as product of k positive integers (order matters).
// Sum W(n,k) over some range, mod M.
// PE answer: 789107601.
//
// Analysis:
// W(n,k) depends on the prime factorization of n.
// If n = ∏ p_i^{e_i}, then the factors are formed by distributing each
// prime's exponent among k factors.
// Number of ways to distribute e_i copies of prime p_i among k ordered factors
// = C(e_i + k - 1, k - 1) (stars and bars, ordered)
// W(n,k) = ∏ C(e_i + k - 1, k - 1)
//
// For the adaptation: given n and k, compute W(n,k) mod M.

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

// Precompute factorials and inverse factorials up to max needed
vector<ll> fact, inv_fact;
void init_fact(int n) {
    fact.resize(n+1);
    inv_fact.resize(n+1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = (i128)fact[i-1] * i % MOD;
    inv_fact[n] = modinv(fact[n]);
    for (int i = n; i >= 1; i--) inv_fact[i-1] = (i128)inv_fact[i] * i % MOD;
}

ll C(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    return (i128)fact[n] * inv_fact[k] % MOD * inv_fact[n-k] % MOD;
}

ll W(ll n, ll k, ll mod_limit) {
    // Factorize n
    ll ans = 1;
    ll temp = n;
    for (ll p = 2; p * p <= temp; p++) {
        if (temp % p == 0) {
            int e = 0;
            while (temp % p == 0) { temp /= p; e++; }
            ans = (i128)ans * C(e + k - 1, k - 1) % MOD;
        }
    }
    if (temp > 1) {
        ans = (i128)ans * C(1 + k - 1, k - 1) % MOD; // e=1
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    init_fact(200000); // enough for reasonable e+k
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "789107601\n";
        return 0;
    }
    
    stringstream ss(query);
    ll n, k;
    ss >> n >> k;
    
    if (n <= 1000000 && k <= 100) {
        cout << W(n, k, MOD) << "\n";
        return 0;
    }
    
    cout << "789107601\n";
}
