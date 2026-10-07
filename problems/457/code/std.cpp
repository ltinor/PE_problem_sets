#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 457: A polynomial modulo the square of a prime
// f(n) = n^2 - 3n - 1
// R(p) = smallest positive n with f(n) ≡ 0 (mod p^2), or 0 if none
// SR(L) = sum_{p ≤ L} R(p), p prime
// Find SR(10^7)

// Modular exponentiation
ll mod_pow(ll a, ll e, ll m) {
    ll r = 1;
    a %= m;
    while (e) {
        if (e & 1) r = (__int128)r * a % m;
        a = (__int128)a * a % m;
        e >>= 1;
    }
    return r;
}

// Extended Euclidean
ll egcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll g = egcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

ll mod_inv(ll a, ll m) {
    ll x, y;
    egcd(a, m, x, y);
    return (x % m + m) % m;
}

// Tonelli-Shanks: sqrt of n modulo odd prime p
ll tonelli_shanks(ll n, ll p) {
    if (n == 0) return 0;
    if (mod_pow(n, (p - 1) / 2, p) != 1) return -1; // no sqrt
    
    if (p % 4 == 3) {
        return mod_pow(n, (p + 1) / 4, p);
    }
    
    // p ≡ 1 mod 4
    ll Q = p - 1, S = 0;
    while (Q % 2 == 0) { Q /= 2; S++; }
    
    // Find quadratic non-residue z
    ll z = 2;
    while (mod_pow(z, (p - 1) / 2, p) != p - 1) z++;
    
    ll M = S;
    ll c = mod_pow(z, Q, p);
    ll t = mod_pow(n, Q, p);
    ll R = mod_pow(n, (Q + 1) / 2, p);
    
    while (t != 1) {
        // Find smallest i such that t^(2^i) ≡ 1 mod p
        ll i = 1;
        ll t2i = (__int128)t * t % p;
        while (t2i != 1) {
            t2i = (__int128)t2i * t2i % p;
            i++;
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll L;
    cin >> L;
    
    // Sieve primes up to L
    vector<bool> is_prime(L + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= L; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= L; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    ll total = 0;
    
    for (ll p = 2; p <= L; p++) {
        if (!is_prime[p]) continue;
        
        // Special case p = 13: discriminant = 0 mod p
        if (p == 13) {
            // f(n) = n^2 - 3n - 1 ≡ (n-8)^2 (mod 13)
            // f(8) = 39, not divisible by 169, so no solution
            continue;
        }
        
        // Special case p = 2
        if (p == 2) {
            // n^2 - 3n - 1 ≡ n^2 + n + 1 (mod 4) ≡ 0 mod 4, no solution
            continue;
        }
        
        // Compute Legendre symbol (13/p)
        if (mod_pow(13, (p - 1) / 2, p) != 1) {
            continue; // 13 is not a quadratic residue mod p
        }
        
        // Find sqrt(13) mod p
        ll s = tonelli_shanks(13, p);
        if (s < 0) continue; // shouldn't happen
        
        ll inv2 = (p + 1) / 2; // inverse of 2 mod p (works for odd p)
        
        // Two solutions mod p: n ≡ (3 ± s) * inv2 (mod p)
        ll n1 = ((3 + s) % p + p) % p;
        n1 = (__int128)n1 * inv2 % p;
        
        ll n2 = ((3 - s) % p + p) % p;
        n2 = (__int128)n2 * inv2 % p;
        
        ll pp = p * p;
        
        // Hensel lifting for n1
        ll fn1 = ((__int128)n1 * n1 - 3LL * n1 - 1) % pp;
        fn1 = (fn1 + pp) % pp;
        // f'(n1) = 2*n1 - 3 mod p
        ll fprime1 = ((2LL * n1 - 3) % p + p) % p;
        ll inv_fp1 = mod_inv(fprime1, pp);
        ll lift1 = (n1 - (__int128)fn1 * inv_fp1 % pp + pp) % pp;
        
        // Hensel lifting for n2
        ll fn2 = ((__int128)n2 * n2 - 3LL * n2 - 1) % pp;
        fn2 = (fn2 + pp) % pp;
        ll fprime2 = ((2LL * n2 - 3) % p + p) % p;
        ll inv_fp2 = mod_inv(fprime2, pp);
        ll lift2 = (n2 - (__int128)fn2 * inv_fp2 % pp + pp) % pp;
        
        // Need smallest positive n modulo p^2
        if (lift1 == 0) lift1 = pp;
        if (lift2 == 0) lift2 = pp;
        ll r_p = min(lift1, lift2);
        
        total += r_p;
    }
    
    cout << total << "\n";
    return 0;
}
