#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Sum of C(N, K) mod p*q*r for primes p<q<r in (L, R)
// PE: N=10^18, K=10^9, L=1000, R=5000
// Answer: 162619462356610313

// Use Lucas theorem for C(n,k) mod p, then CRT to combine mod p*q*r
// Lucas: C(n,k) mod p = ∏ C(n_i, k_i) mod p where n_i, k_i are base-p digits

ll modpow(ll a, ll e, ll mod) {
    ll r = 1;
    while (e) { if (e&1) r = r*a%mod; a = a*a%mod; e >>= 1; }
    return r;
}

// Precompute factorials mod p
vector<ll> fact, inv_fact;
void precompute_fact(ll p) {
    fact.resize(p);
    inv_fact.resize(p);
    fact[0] = 1;
    for (int i = 1; i < p; i++) fact[i] = fact[i-1] * i % p;
    inv_fact[p-1] = modpow(fact[p-1], p-2, p);
    for (int i = p-2; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % p;
}

ll nCr_mod_p(ll n, ll k, ll p) {
    if (k < 0 || k > n) return 0;
    // Lucas theorem
    ll res = 1;
    while (n > 0 || k > 0) {
        ll ni = n % p;
        ll ki = k % p;
        if (ki > ni) return 0;
        res = res * fact[ni] % p * inv_fact[ki] % p * inv_fact[ni - ki] % p;
        n /= p;
        k /= p;
    }
    return res;
}

// Extended Euclidean algorithm
ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll crt(ll a1, ll m1, ll a2, ll m2) {
    ll x, y;
    ext_gcd(m1, m2, x, y);
    ll m = m1 * m2;
    ll res = (a1 * m2 % m * y % m + a2 * m1 % m * x % m) % m;
    return (res + m) % m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N, K, L, R;
    cin >> N >> K >> L >> R;
    
    // Generate primes in (L, R)
    vector<bool> is_prime(R + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= R; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= R; j += i)
                is_prime[j] = false;
        }
    }
    
    vector<ll> primes;
    for (ll i = L + 1; i < R; i++)
        if (is_prime[i]) primes.push_back(i);
    
    ll total = 0;
    
    // Iterate over all triples p<q<r
    for (size_t i = 0; i < primes.size(); i++) {
        ll p = primes[i];
        precompute_fact(p);
        ll cp = nCr_mod_p(N, K, p);
        
        for (size_t j = i + 1; j < primes.size(); j++) {
            ll q = primes[j];
            precompute_fact(q);
            ll cq = nCr_mod_p(N, K, q);
            
            for (size_t k = j + 1; k < primes.size(); k++) {
                ll r = primes[k];
                precompute_fact(r);
                ll cr = nCr_mod_p(N, K, r);
                
                // CRT for mod p*q*r
                ll m = p * q * r;
                ll a12 = crt(cp, p, cq, q);
                ll a = crt(a12, p * q, cr, r);
                
                total += a;
            }
        }
    }
    
    cout << total << "\n";
    return 0;
}
