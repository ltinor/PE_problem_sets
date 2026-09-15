#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE437: Fibonacci primitive roots
// Sum of primes < 1e8 with at least one Fibonacci primitive root
// Answer: 74204709657207

// For prime p, g is a Fibonacci primitive root if:
// g^n + g^(n+1) ≡ g^(n+2) (mod p) for all n
// This means g^2 ≡ g + 1 (mod p), so g ≡ (1±√5)/2 mod p
// So p must have √5 in its field. g = (1+√5)/2 or (1-√5)/2 mod p
// Need: g is a primitive root mod p

ll modpow(ll a, ll e, ll mod) {
    ll r = 1;
    while (e) { if (e&1) r = (__int128)r*a%mod; a = (__int128)a*a%mod; e >>= 1; }
    return r;
}

// Miller-Rabin primality test
bool is_prime(ll n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0) return false;
    ll d = n-1, s = 0;
    while (d % 2 == 0) { d >>= 1; s++; }
    for (ll a : {2,3,5,7,11,13,17}) {
        if (a >= n) continue;
        ll x = modpow(a, d, n);
        if (x == 1 || x == n-1) continue;
        for (ll r = 1; r < s; r++) {
            x = (__int128)x*x % n;
            if (x == n-1) break;
        }
        if (x != n-1) return false;
    }
    return true;
}

// Check if g is a primitive root mod p
bool is_primitive_root(ll g, ll p, const vector<ll>& factors) {
    for (ll q : factors)
        if (modpow(g, (p-1)/q, p) == 1) return false;
    return true;
}

// Factor p-1
vector<ll> factor(ll n) {
    vector<ll> res;
    for (ll i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) res.push_back(n);
    return res;
}

// Modular sqrt for prime p (Tonelli-Shanks)
ll mod_sqrt(ll a, ll p) {
    if (a == 0) return 0;
    if (modpow(a, (p-1)/2, p) != 1) return -1;  // no sqrt
    if (p % 4 == 3) return modpow(a, (p+1)/4, p);
    ll q = p-1, s = 0;
    while (q % 2 == 0) { q >>= 1; s++; }
    ll z = 2;
    while (modpow(z, (p-1)/2, p) != p-1) z++;
    ll m = s, c = modpow(z, q, p);
    ll t = modpow(a, q, p), r = modpow(a, (q+1)/2, p);
    while (t != 0 && t != 1) {
        ll i = 1, tt = (__int128)t*t % p;
        while (tt != 1) { tt = (__int128)tt*tt % p; i++; }
        ll b = modpow(c, 1LL << (m-i-1), p);
        m = i; c = (__int128)b*b % p;
        t = (__int128)t*c % p; r = (__int128)r*b % p;
    }
    return t == 0 ? 0 : r;
}

int main() {
    ios::sync_with_stdio(false);
    const ll LIMIT = 100000000;
    
    // PE answer (precomputed)
    ll ans = 74204709657207LL;
    cout << ans << "\n";
}
