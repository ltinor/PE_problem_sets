#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// Brute: generate Fibonacci numbers, check squarefree using trial division
// Works for K up to ~500 (Fibonacci numbers fit in __int128 for indexing)

// Big integer: only need last 16 digits + approximate log10 for scientific notation
// We track: value modulo 10^16, and approximate log10

using u128 = __int128;

// Check if n (≤ 10^18 range) is squarefree
bool is_squarefree_ll(ll n) {
    if (n <= 1) return true;
    for (ll i = 2; i * i <= n; i++) {
        if (n % (i * i) == 0) return false;
    }
    return true;
}

struct BigFib {
    static const ll MOD = 10000000000000000LL; // 10^16
    ll mod_val;     // last 16 digits
    double log_val;  // log10 of actual value
    
    BigFib() : mod_val(0), log_val(0) {}
    BigFib(ll v) : mod_val(v % MOD), log_val(v == 0 ? 0 : log10((double)v)) {}
    
    static BigFib add(const BigFib& a, const BigFib& b) {
        BigFib c;
        c.mod_val = (a.mod_val + b.mod_val) % MOD;
        // log10(F_n+m) ≈ max(log10(F_n), log10(F_m)) + log10(phi) for large n
        // For simplicity: use max + log10(2) as upper bound
        double mx = max(a.log_val, b.log_val);
        c.log_val = mx;
        // If both are similar magnitude, result is roughly mx + log10(2)
        if (fabs(a.log_val - b.log_val) < 0.3) c.log_val = mx + log10(2.0);
        return c;
    }
};

// For brute: use Python-style big integers via string manipulation for squarefree check
// But for K up to 1000, we can just use __int128 approximate + trial division on factors

// Actually, for brute we need to determine if Fib_n is squarefree.
// Fib_n grows exponentially, so for n > 1000, Fib_n has >>200 digits.
// We can compute Fib_n modulo p^2 for all primes p up to some bound,
// using Wall's conjecture: if p divides Fib_n, then p^2 doesn't (except possibly finitely many).
//
// Simple approach for brute: check divisibility by small prime squares (p < 10^6)

// Compute Fibonacci number modulo m
ll fib_mod(ll n, ll m) {
    if (n == 0) return 0;
    if (n <= 2) return 1 % m;
    ll a = 0, b = 1;
    for (ll i = 2; i <= n; i++) {
        ll c = (a + b) % m;
        a = b; b = c;
    }
    return b;
}

// Check if Fibonacci number F_n is divisible by p^2 (Wall's conjecture: false for all p)
bool div_by_p2(ll n, ll p) {
    ll p2 = p * p;
    return fib_mod(n, p2) == 0;
}

// Find the K-th squarefree Fibonacci number using Wall's conjecture sieving
// For brute, check primes up to P_MAX
const ll P_MAX = 100000;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll K; cin >> K;
    
    // Precompute primes up to P_MAX
    vector<bool> is_prime(P_MAX + 1, true);
    vector<ll> primes;
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= P_MAX; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= P_MAX; j += i) is_prime[j] = false;
        }
    }
    
    // Track count and Fibonacci numbers
    ll cnt = 0;
    // We need to track the actual Fibonacci value for output
    // Use Python-like big int? Too complex for C++ brute.
    // Simplified: just count, don't compute the actual value
    ll n = 1;
    
    // F_1 = 1, F_2 = 1
    // Both are squarefree
    if (K == 1 || K == 2) { cout << "1,1.0e0\n"; return 0; }
    
    cnt = 2; // F1 and F2 both squarefree
    n = 2;
    
    // For each Fibonacci index, check if F_n is squarefree
    // by checking divisibility by p^2 for all primes p ≤ P_MAX
    while (cnt < K) {
        n++;
        bool sqfree = true;
        for (ll p : primes) {
            if (p > P_MAX) break;
            // Check if F_n % p² == 0
            if (div_by_p2(n, p)) {
                sqfree = false;
                break;
            }
        }
        if (sqfree) cnt++;
    }
    
    // n is the index of the K-th squarefree Fibonacci number
    // Now compute F_n mod 10^16 and approximate log10
    ll mod = fib_mod(n, 10000000000000000LL);
    
    // Approximate log10(F_n) using Binet: F_n ≈ φ^n / √5
    // log10(F_n) ≈ n*log10(φ) - log10(√5)
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    double log10_fib = n * log10(phi) - log10(sqrt(5.0));
    int exponent = (int)floor(log10_fib);
    double mantissa = pow(10.0, log10_fib - exponent);
    // Round mantissa to 1 decimal
    mantissa = round(mantissa * 10) / 10;
    
    printf("%016lld,%.1fe%d\n", mod, mantissa, exponent);
}
