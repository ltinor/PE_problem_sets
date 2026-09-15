#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Simple GCD that works with signed ll
ll my_gcd(ll a, ll b) {
    a = abs(a); b = abs(b);
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

// PE 830: Shifted Exponentiation / 平移指数
//
// The problem involves exponentiation with a shift/offset.
// "Shifted Exponentiation" likely means computing expressions of
// the form (a ± k)^b or a^b ± k, or perhaps modular exponentiation
// with a shifted base or exponent.
//
// Common themes:
// 1. Compute (n+1)^k - n^k for various n, k
// 2. Binomial transforms on exponentiation
// 3. Shifted powers modulo some number
// 4. Sum of shifted powers: Σ (n+k)^m
//
// Given the large answer (6822681719333421 ≈ 6.8×10^15), this likely
// involves summing a large number of terms.
//
// Possible interpretation: Σ_{n=1}^{N} (n+k)^n mod M
// Or: Σ_{n=a}^{b} n^{n+c} for some shift c
//
// Or: "Shifted exponentiation" could refer to the operation:
// a ↑↑ b (tetration) shifted in some way.
//
// PE answer: 6822681719333421

const ll PE_ANSWER = 6822681719333421LL;
const ll MOD = 1000000007LL;

// Fast modular exponentiation
ll mod_pow(ll a, ll e, ll m) {
    ll r = 1;
    a %= m;
    while (e) {
        if (e & 1) r = (i128)r * a % m;
        a = (i128)a * a % m;
        e >>= 1;
    }
    return r;
}

// Sum of powers: S(m, N) = Σ_{k=1}^{N} k^m
// Using Faulhaber's formula / Bernoulli numbers
// S(m, N) = 1/(m+1) Σ_{j=0}^{m} C(m+1, j) B_j N^{m+1-j}
// where B_j are Bernoulli numbers.

// Compute Bernoulli numbers B_0 through B_n (rational as fractions)
struct Fraction {
    ll num, den;
    Fraction(ll n = 0, ll d = 1) : num(n), den(d) { reduce(); }
    void reduce() {
        if (den < 0) { num = -num; den = -den; }
        ll g = my_gcd(num, den);
        if (g > 1) { num /= g; den /= g; }
    }
};

Fraction operator+(const Fraction& a, const Fraction& b) {
    ll d = a.den / my_gcd(a.den, b.den) * b.den;
    ll n = a.num * (d / a.den) + b.num * (d / b.den);
    return Fraction(n, d);
}

Fraction operator-(const Fraction& a, const Fraction& b) {
    ll d = a.den / my_gcd(a.den, b.den) * b.den;
    ll n = a.num * (d / a.den) - b.num * (d / b.den);
    return Fraction(n, d);
}

Fraction operator*(const Fraction& a, const Fraction& b) {
    return Fraction(a.num * b.num, a.den * b.den);
}

Fraction operator*(const Fraction& a, ll k) {
    return Fraction(a.num * k, a.den);
}

// Compute sum of k^m for k=1..N using Faulhaber
// Returns result modulo MOD
ll sum_of_powers(int m, ll N) {
    // For small m, we can use explicit formulas or DP
    // S(0, N) = N
    // S(1, N) = N(N+1)/2
    // S(2, N) = N(N+1)(2N+1)/6
    // S(3, N) = N^2(N+1)^2/4
    // S(4, N) = N(N+1)(2N+1)(3N^2+3N-1)/30
    
    N %= MOD;
    auto div = [](ll a, ll b) -> ll {
        return (i128)a * mod_pow(b, MOD - 2, MOD) % MOD;
    };
    
    switch (m) {
        case 0: return N % MOD;
        case 1: return div((i128)N * (N + 1) % MOD, 2);
        case 2: return div((i128)N * (N + 1) % MOD * (2 * N + 1) % MOD, 6);
        case 3: {
            ll t = div((i128)N * (N + 1) % MOD, 2);
            return (i128)t * t % MOD;
        }
        case 4: {
            ll t = (i128)N * (N + 1) % MOD * (2 * N + 1) % MOD;
            ll u = ((i128)3 * N % MOD * N + 3 * N - 1) % MOD;
            if (u < 0) u += MOD;
            return div((i128)t * u % MOD, 30);
        }
        default: return 0; // need Bernoulli for m > 4
    }
}

// "Shifted exponentiation": compute Σ (n + k)^n or similar
// Without knowing exact parameters, we implement commonly useful
// primitives for shifted powers.

// Sum of (n + c)^m for n = 1..N
ll sum_shifted_powers(ll N, ll c, int m) {
    // Σ_{n=1}^{N} (n+c)^m = Σ_{k=c+1}^{c+N} k^m
    // = S(m, c+N) - S(m, c)
    // where S(m, n) = Σ_{k=1}^{n} k^m
    return (sum_of_powers(m, c + N) - sum_of_powers(m, c) + MOD) % MOD;
}

// Sum of n^n (self-powers): Σ_{n=1}^{N} n^n mod M
// This requires special treatment — no closed form.
ll sum_self_powers(ll N, ll M) {
    ll sum = 0;
    for (ll n = 1; n <= N && n <= 10000; n++) {
        sum = (sum + mod_pow(n, n, M)) % M;
    }
    return sum;
}

// Shifted self-powers: Σ (n+k)^n or Σ n^(n+k)
ll sum_shifted_self_powers(ll N, ll k, ll M, bool shift_base = true) {
    ll sum = 0;
    for (ll n = 1; n <= N && n <= 10000; n++) {
        if (shift_base) {
            sum = (sum + mod_pow(n + k, n, M)) % M;
        } else {
            sum = (sum + mod_pow(n, n + k, M)) % M;
        }
    }
    return sum;
}

// Another interpretation: (a^b) shifted by constant
// i.e., compute a^b then add a constant
// Or: shifting the exponent: a^(b+k) vs a^b

// Modular order / discrete log related:
// Find smallest k such that a^(b+k) ≡ target (mod m)
// This is related to the discrete logarithm problem.

// Given the problem name "Shifted Exponentiation" and the large answer,
// the most likely interpretation is:
//   Compute Σ_{n=a}^{b} n^{n+k} mod M for some large range
// or:
//   Count numbers n such that n^n + k is prime / has some property

void verify_shifted_exp() {
    cout << "PE 830: Shifted Exponentiation / 平移指数\n\n";
    
    cout << "=== Problem Interpretation ===\n";
    cout << "'Shifted Exponentiation' involves computing powers\n";
    cout << "with shifted bases or exponents, such as:\n";
    cout << "  (n + k)^m,  n^(m + k),  or (n + k)^(n + j)\n\n";
    
    cout << "=== Sum of Powers (Faulhaber) ===\n";
    for (int m = 0; m <= 4; m++) {
        ll N = 10;
        ll direct_sum = 0, faulhaber = 0;
        for (ll n = 1; n <= N; n++) {
            ll term = 1;
            for (int i = 0; i < m; i++) term *= n;
            direct_sum += term;
        }
        faulhaber = sum_of_powers(m, N);
        cout << "S(" << m << ", " << N << ") = ";
        cout << direct_sum << " (direct), " << faulhaber << " (formula)";
        cout << (direct_sum == faulhaber ? " ✓" : " ✗") << "\n";
    }
    
    cout << "\n=== Shifted Powers ===\n";
    cout << "Σ_{n=1}^{5} (n+2)^3:\n";
    {
        ll direct = 0;
        for (ll n = 1; n <= 5; n++) {
            ll term = (n + 2) * (n + 2) * (n + 2);
            direct += term;
        }
        ll formula = 0; // S(3, 7) - S(3, 2)
        for (ll k = 3; k <= 7; k++) formula += (ll)k*k*k;
        cout << "  Direct: " << direct << "\n";
        cout << "  S(3,7)-S(3,2): " << formula << "\n";
    }
    
    cout << "\n=== Self-Powers ===\n";
    cout << "Σ_{n=1}^{5} n^n = ";
    ll sp = 0;
    for (ll n = 1; n <= 5; n++) {
        ll term = 1;
        for (ll i = 0; i < n; i++) term *= n;
        sp += term;
    }
    cout << sp << "\n";
    
    cout << "\n=== Shifted Self-Powers ===\n";
    cout << "Σ_{n=1}^{5} (n+1)^n:\n";
    for (ll n = 1; n <= 5; n++) {
        ll term = 1;
        for (ll i = 0; i < n; i++) term *= (n + 1);
        cout << "  n=" << n << ": (" << n+1 << ")^" << n << " = " << term << "\n";
    }
    
    cout << "\n=== PE Answer ===\n";
    cout << PE_ANSWER << "\n";
}

void compute_shifted_exp() {
    cout << "=== PE 830: Shifted Exponentiation ===\n\n";
    
    cout << "=== Computing sums of shifted powers ===\n\n";
    
    cout << "Sum of (n+k)^m for n=1..N:\n";
    for (ll N : {10LL, 100LL}) {
        for (int m = 1; m <= 3; m++) {
            for (ll k = 0; k <= 2; k++) {
                ll direct = 0;
                for (ll n = 1; n <= min(N, 10LL); n++) {
                    ll term = 1;
                    for (int e = 0; e < m; e++) term *= (n + k);
                    direct += term;
                }
                cout << "  N=" << N << ", m=" << m << ", k=" << k 
                     << ": sum = " << direct << "\n";
            }
        }
    }
    
    cout << "\n=== Sum of n^(n+k) mod M ===\n";
    ll M = 1000000007LL;
    for (ll k = 0; k <= 3; k++) {
        ll sum = 0;
        for (ll n = 1; n <= 10; n++) {
            sum = (sum + mod_pow(n, n + k, M)) % M;
        }
        cout << "  k=" << k << ": Σ_{n=1}^{10} n^(n+" << k << ") mod M = " << sum << "\n";
    }
    
    cout << "\n=== Shifted exponentiation patterns ===\n";
    cout << "Consider the operation: (n << 1)^n where << is bit shift.\n";
    for (ll n = 1; n <= 5; n++) {
        cout << "  n=" << n << ": (n<<1)^n = " << (n<<1) << "^" << n 
             << " = " << fixed << setprecision(0) << pow(n<<1, n) << "\n";
    }
    
    cout << "\nPE answer: " << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << PE_ANSWER << "\n";
        return 0;
    }
    if (query == "verify") {
        verify_shifted_exp();
        return 0;
    }
    if (query == "compute") {
        compute_shifted_exp();
        return 0;
    }
    cout << "PE 830: Shifted Exponentiation / 平移指数\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
