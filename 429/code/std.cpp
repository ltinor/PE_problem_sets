#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE429: Sum of squares of unitary divisors of n!
// S(n) = sum of squares of unitary divisors of n
// Unitary divisor d: d|n and gcd(d, n/d) = 1
// For n = p1^a1 * p2^a2 * ..., unitary divisors are:
// product over i of (1 or pi^ai)
// S(n) = product over prime powers p^a || n of (1 + p^(2a))
// So S(n!) = product over primes p ≤ n of (1 + p^(2 * v_p(n!)))
// v_p(n!) = n/p + n/p^2 + n/p^3 + ...
// We need S(100000000!) mod 1000000009

const ll MOD = 1000000009LL;

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
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    ll N; cin >> N;
    
    // Sieve primes up to N
    vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= N; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= N; j += i)
                is_prime[j] = false;
        }
    }
    
    ll ans = 1;
    for (ll p = 2; p <= N; p++) {
        if (!is_prime[p]) continue;
        // v_p(N!) = sum_{k≥1} floor(N / p^k)
        ll exp = 0;
        ll pk = p;
        while (pk <= N) {
            exp += N / pk;
            if (pk > N / p) break; // prevent overflow
            pk *= p;
        }
        // contribution: 1 + p^(2*exp) mod MOD
        ll term = (1 + modpow(p % MOD, 2 * exp)) % MOD;
        ans = ans * term % MOD;
    }
    
    // PE verification: for N=100000000, answer should be 98792821
    cout << ans << "\n";
    return 0;
}
