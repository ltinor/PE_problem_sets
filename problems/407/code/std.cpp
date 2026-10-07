#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE407: Idempotents
// M(n) = max_{0<a<n, a^2≡a(mod n)} a
// Sum_{n=1..N} M(n)
// Key insight: for each n = u*v with gcd(u,v)=1:
//   idempotent a ≡ 1 (mod u), a ≡ 0 (mod v) is: a = v * modinv(v, u) % n
//   idempotent a ≡ 0 (mod u), a ≡ 1 (mod v) is: a = u * modinv(u, v) % n
// M(n) = max over all coprime factorizations of max of these two.
// Efficient: iterate over prime powers p^e, for each multiple n = p^e * m (gcd(m,p)=1)
//   compute a = m * modinv(m, p^e) % n and b = p^e * modinv(p^e, m) % n
//   M[n] = max(M[n], a, b)
// Sum M[1..N]
// PE answer for N=10^7: 39782849136421

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) { if (e & 1) r *= a; a *= a; e >>= 1; }
    return r;
}

ll modinv(ll a, ll m) {
    // a*x ≡ 1 (mod m), gcd(a,m)=1
    ll m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        ll q = a / m;
        ll t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    ll N;
    cin >> N;
    
    vector<ll> M(N + 1, 0);
    // M[1] = 0, for prime powers M[p^e] = 1
    // We'll handle all n > 1 through the iteration
    
    // Sieve: smallest prime factor
    vector<int> spf(N + 1);
    for (int i = 2; i <= N; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            if ((ll)i * i <= N) {
                for (int j = i * i; j <= N; j += i) {
                    if (spf[j] == 0) spf[j] = i;
                }
            }
        }
    }
    
    // For each n, extract all prime powers
    // and compute M[n]
    for (int n = 2; n <= N; n++) {
        // Get prime powers of n
        vector<ll> pps;
        int m = n;
        while (m > 1) {
            int p = spf[m];
            ll pk = 1;
            while (m % p == 0) {
                m /= p;
                pk *= p;
            }
            pps.push_back(pk);
        }
        
        if (pps.size() == 1) {
            // n is prime power: M[n] = 1
            M[n] = 1;
            continue;
        }
        
        ll best = 0;
        // For each non-trivial partition of prime powers
        int k = pps.size();
        for (int mask = 1; mask < (1 << k) - 1; mask++) {
            ll u = 1;
            for (int i = 0; i < k; i++) {
                if (mask & (1 << i)) u *= pps[i];
            }
            ll v = n / u;
            // a ≡ 1 (mod u), a ≡ 0 (mod v): a = v * modinv(v, u) % n
            ll a = (v % n) * modinv(v % u, u) % n;
            if (a > best) best = a;
            // a ≡ 0 (mod u), a ≡ 1 (mod v): a = u * modinv(u, v) % n
            ll b = (u % n) * modinv(u % v, v) % n;
            if (b > best) best = b;
        }
        M[n] = best;
    }
    
    ll total = 0;
    for (int n = 1; n <= N; n++) total += M[n];
    cout << total << "\n";
}
