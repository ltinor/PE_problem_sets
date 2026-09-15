#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: compute C(N,K) directly (using Python-style big integers not available in C++)
// Instead, use prime factorization to compute C(N,K) mod m for small N,K
// For small parameters, compute C(N,K) exactly using __int128 or by computing mod m

// Compute C(n,k) using multiplicative formula with division
ll nCr_mod(ll n, ll k, ll mod) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    
    // Use prime factorization approach to avoid division issues
    // Or use __int128 for small n,k
    __int128 res = 1;
    for (ll i = 1; i <= k; i++) {
        res = res * (n - i + 1) / i;
    }
    return (ll)(res % mod);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N, K, L, R;
    cin >> N >> K >> L >> R;
    
    // Generate primes
    vector<bool> is_prime(R + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= R; i++) {
        if (is_prime[i])
            for (ll j = i * i; j <= R; j += i)
                is_prime[j] = false;
    }
    
    vector<ll> primes;
    for (ll i = L + 1; i < R; i++)
        if (is_prime[i]) primes.push_back(i);
    
    ll total = 0;
    for (size_t i = 0; i < primes.size(); i++) {
        for (size_t j = i + 1; j < primes.size(); j++) {
            for (size_t k = j + 1; k < primes.size(); k++) {
                ll p = primes[i], q = primes[j], r = primes[k];
                ll m = p * q * r;
                
                // Small verification: compute C(N,K) mod m
                ll val = nCr_mod(N, K, m);
                total += val;
            }
        }
    }
    
    cout << total << "\n";
    return 0;
}
