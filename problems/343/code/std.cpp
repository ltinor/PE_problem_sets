#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long

// PE 343: Sum of f(k^3) for k=1..K
// f(m) = S-1 where S starts at m+1, repeatedly divide by smallest prime factor
// until S is prime. Then f = S-1.
//
// For k^3: S = k^3+1. We need smallest prime factor of numbers up to K^3+1.
// Precompute spf up to bound B, use Pollard's Rho for larger.

const int B = 2000000; // sieve bound for spf (2 million)
int spf[B + 2];

// gcd for unsigned
ull ugcd(ull a, ull b) {
    while (b) { ull t = a % b; a = b; b = t; }
    return a;
}

ull mul_mod(ull a, ull b, ull m) {
    return (__int128)a * b % m;
}

ull pow_mod(ull a, ull e, ull m) {
    ull r = 1;
    while (e) {
        if (e & 1) r = mul_mod(r, a, m);
        a = mul_mod(a, a, m);
        e >>= 1;
    }
    return r;
}

bool is_prime_ull(ull n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    ull d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }
    ull bases[] = {2, 3, 5, 7, 11, 13, 17};
    for (ull a : bases) {
        if (a >= n) continue;
        ull x = pow_mod(a, d, n);
        if (x == 1 || x == n-1) continue;
        bool composite = true;
        for (int r = 0; r < s-1; r++) {
            x = mul_mod(x, x, n);
            if (x == n-1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

ll pollard_rho(ll n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    while (true) {
        ll c = rand() % (n-1) + 1;
        auto f = [&](ll x) { return ((__int128)x * x + c) % n; };
        ll x = rand() % (n-1) + 1, y = x, d = 1;
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = (ll)ugcd(abs(x-y), n);
        }
        if (d != n) return d;
    }
}

ll spf_large(ll n) {
    // Find smallest prime factor of n (n may exceed sieve bound)
    // Trial division for small primes first
    for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n % p == 0) return p;
    }
    if (n < (ll)B) return spf[n];
    if (is_prime_ull(n)) return n;
    // Pollard's Rho for larger factors
    ll d = pollard_rho(n);
    return min(spf_large(d), spf_large(n/d));
}

void sieve_spf(int N) {
    vector<int> primes;
    for (int i = 2; i <= N; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || (ll)i * p > N) break;
            spf[i * p] = p;
        }
    }
}

ll f_of(ll m) {
    // Compute f(m) where m = k^3
    ll S = m + 1;
    while (S > 1) {
        if (is_prime_ull(S)) return S - 1;
        ll p;
        if (S < B) p = spf[S];
        else p = spf_large(S);
        S /= p;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    
    int K;
    cin >> K;
    
    // Sieve up to B (2 million) for fast lookups
    sieve_spf(B);
    
    ll ans = 0;
    for (int k = 1; k <= K; k++) {
        ll m = (ll)k * k * k;
        ans += f_of(m);
    }
    
    cout << ans << "\n";
    return 0;
}
