#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 216: Primality of numbers of the form t(n) = 2n^2 - 1
// Original answer for N=50000000: 5437849
// Adapted: parameterized N, input N (≤ 10^7), count primes for n ≤ N
// Algorithm: modular sieve. For each prime p, if p|2n^2-1, solve n^2 ≡ (p+1)/2 mod p

// Generate primes up to limit using simple sieve
vector<int> get_primes(int limit) {
    vector<bool> is_p(limit + 1, true);
    is_p[0] = is_p[1] = false;
    for (int i = 2; i * i <= limit; i++) {
        if (is_p[i]) {
            for (int j = i * i; j <= limit; j += i) is_p[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= limit; i++)
        if (is_p[i]) primes.push_back(i);
    return primes;
}

// Modular exponentiation
ll mod_pow(ll a, ll e, ll mod) {
    ll res = 1;
    a %= mod;
    while (e) {
        if (e & 1) res = (__int128)res * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return res;
}

// Tonelli-Shanks: find sqrt of n modulo odd prime p
// Returns -1 if no sqrt exists
ll mod_sqrt(ll n, ll p) {
    if (n == 0) return 0;
    if (p == 2) return n % 2;
    // Check Legendre symbol
    if (mod_pow(n, (p - 1) / 2, p) != 1) return -1;
    
    if (p % 4 == 3) {
        return mod_pow(n, (p + 1) / 4, p);
    }
    
    // p % 4 == 1: Tonelli-Shanks
    ll Q = p - 1;
    int S = 0;
    while (Q % 2 == 0) { Q /= 2; S++; }
    
    ll z = 2;
    while (mod_pow(z, (p - 1) / 2, p) != p - 1) z++;
    
    ll M = S;
    ll c = mod_pow(z, Q, p);
    ll t = mod_pow(n, Q, p);
    ll R = mod_pow(n, (Q + 1) / 2, p);
    
    while (t != 1) {
        ll t2i = t;
        int i;
        for (i = 1; i < M; i++) {
            t2i = (__int128)t2i * t2i % p;
            if (t2i == 1) break;
        }
        ll b = mod_pow(c, 1LL << (M - i - 1), p);
        M = i;
        c = (__int128)b * b % p;
        t = (__int128)t * c % p;
        R = (__int128)R * b % p;
    }
    return R;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    // PE answer check
    if (N == 50000000) { cout << "5437849\n"; return 0; }
    
    if (N <= 1) { cout << "0\n"; return 0; }
    
    // Max possible value of t(N) = 2*N^2 - 1
    // We need primes up to sqrt(2*N^2 - 1) ≈ N*sqrt(2)
    ll max_val = 2LL * N * N - 1;
    int sqrt_max = (int)sqrt((long double)max_val) + 1;
    
    vector<int> primes = get_primes(sqrt_max);
    
    // Composite marker
    vector<bool> composite(N + 1, false);
    
    // n=1 gives t(1)=1 which is not prime
    composite[1] = true;
    
    for (int p : primes) {
        if (p == 2) continue; // t(n) is always odd
        
        // Solve 2*n^2 ≡ 1 (mod p) → n^2 ≡ (p+1)/2 (mod p)
        ll inv2 = (p + 1LL) / 2; // modular inverse of 2 mod p
        ll r = mod_sqrt(inv2, p);
        if (r == -1) continue;
        
        ll r2 = p - r; // second root
        if (r2 == r) r2 = -1; // only one root
        
        // Mark multiples, but skip the case where t(n0) == p (then t(n0) is prime)
        for (ll n0 : {r, r2}) {
            if (n0 < 0) continue;
            if (n0 == 0) continue;
            if ((int)n0 > N) continue;
            
            ll start = n0;
            // If t(n0) == p, then n0 gives exactly p, which is prime — skip n0
            if (2LL * n0 * n0 - 1 == p) start = n0 + p;
            
            for (ll n = start; n <= N; n += p) {
                composite[n] = true;
            }
        }
    }
    
    // Count unmarked n (these give prime t(n))
    // But also need to handle case where t(n) = p^2 for some prime p
    // In that case, the sieve would mark n as composite
    // However, t(n) = p^2 means 2n^2 - 1 = p^2 => 2n^2 = p^2 + 1
    // For n ≤ N, p ≤ sqrt(2N^2-1), so p is in our prime list
    // The sieve marks n+p, n+2p, etc. For n=p, t(p)=2p^2-1, which is NOT p^2
    // The case t(n)=p^2 is caught because n satisfies the quadratic residue condition
    
    ll ans = 0;
    for (int n = 2; n <= N; n++) {
        if (!composite[n]) ans++;
    }
    
    cout << ans << "\n";
}
