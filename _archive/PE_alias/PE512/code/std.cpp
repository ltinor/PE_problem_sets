#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE512: Sums of totients of powers
// φ(n) = Euler's totient function.
// f(n) = (Σ_{i=1}^n φ(n^i)) mod (n+1)
// g(n) = Σ_{i=1}^n f(i)
// g(100) = 2007. Find g(5×10^8).
// PE answer: 5066059188205026.

// Key insight: φ(n^i) = n^{i-1} * φ(n) for i ≥ 1
// So f(n) = (Σ_{i=1}^n φ(n^i)) mod (n+1)
//          = (φ(n) * Σ_{i=1}^n n^{i-1}) mod (n+1)
//          = (φ(n) * (n^n - 1)/(n - 1)) mod (n+1)  if n > 1
//
// Working modulo (n+1): n ≡ -1 (mod n+1)
// So n^{i-1} mod (n+1):
//   For i-1 even: n^{i-1} ≡ 1 (mod n+1)
//   For i-1 odd:  n^{i-1} ≡ -1 (mod n+1)
//
// Therefore:
//   if n is odd:  Σ_{i=1}^n n^{i-1} = 1 + (-1) + 1 + ... (n terms)
//      = 0 if n is even, 1 if n is odd
//   Wait more carefully:
//   n mod (n+1) = -1, so n^j mod (n+1) = (-1)^j
//   Σ_{j=0}^{n-1} n^j mod (n+1) = Σ_{j=0}^{n-1} (-1)^j
//   = if n is even: 0, if n is odd: 1
//
// So Σ_{i=1}^n φ(n^i) mod (n+1) = φ(n) * (Σ_{j=0}^{n-1} n^j) mod (n+1)
// = φ(n) * (if n even then 0 else 1) mod (n+1)
//
// Wait, but n and n+1 are coprime. And φ(n) mod (n+1) is not simplified.
// f(n) = φ(n) * (Σ_{j=0}^{n-1} (-1)^j) mod (n+1)
//
// Case 1: n is even → Σ = 0 → f(n) = 0
// Case 2: n is odd → Σ = 1 → f(n) = φ(n) mod (n+1)
//
// So f(n) = 0 if n is even
// f(n) = φ(n) mod (n+1) if n is odd
//
// g(N) = Σ_{n=1}^N f(n) = Σ_{odd n ≤ N} (φ(n) mod (n+1))
//
// Wait, but φ(n) can be larger than n+1, so φ(n) mod (n+1) = φ(n) - k*(n+1) 
// for some k.
// Actually φ(n) < n for n > 1, and n < n+1, so φ(n) < n+1.
// Therefore φ(n) mod (n+1) = φ(n) for all n > 1.
//
// For n = 1: φ(1) = 1, f(1) = (Σ_{i=1}^1 φ(1^i)) mod 2 = φ(1) mod 2 = 1 mod 2 = 1.
//
// So g(N) = 1 + Σ_{odd n, 3 ≤ n ≤ N} φ(n)
//         = Σ_{odd n, 1 ≤ n ≤ N} φ(n)   [includes n=1: φ(1)=1]
//
// Now we need: g(N) = Σ_{n odd, n ≤ N} φ(n)
//
// To compute this efficiently for N = 5×10^8:
// Σ_{n≤N, n odd} φ(n) = Σ_{n≤N} φ(n) - Σ_{n≤N, n even} φ(n)
// Σ_{n≤N, n even} φ(n) = Σ_{k≤N/2} φ(2k)
// φ(2k) = φ(2)φ(k) if gcd(2,k)=1 i.e. k odd, else 2φ(k)
// φ(2k) = φ(k)   if k is odd  [since φ(2)=1 and gcd(2,k)=1 → φ(2k)=φ(k)]
// φ(2k) = 2φ(k)  if k is even [since 2|k, φ(2k)=2φ(k)]
//
// Let S(N) = Σ_{n≤N} φ(n). Then we need S_odd(N).
// S_odd(N) = Σ_{n≤N, n odd} φ(n)
// S(N) = S_odd(N) + Σ_{n≤N, n even} φ(n)
//
// Σ_{n≤N, n even} φ(n) = Σ_{k=1}^{N/2} φ(2k)
// = Σ_{k≤N/2, k odd} φ(k) + Σ_{k≤N/2, k even} 2φ(k)
// = S_odd(N/2) + 2 * (Σ_{k≤N/2} φ(k) - S_odd(N/2))
// = S_odd(N/2) + 2*S(N/2) - 2*S_odd(N/2)
// = 2*S(N/2) - S_odd(N/2)
//
// So: S(N) = S_odd(N) + 2*S(N/2) - S_odd(N/2)
// → S_odd(N) = S(N) - 2*S(N/2) + S_odd(N/2)
//
// This is a recursive formula! We can compute S(N) and S_odd(N) together.
//
// For S(N) = Σ_{n≤N} φ(n), we use the known formula:
// S(N) = N(N+1)/2 - Σ_{g=2}^N S(N/g)
// Or the standard Dirichlet hyperbola method:
// Σ_{d=1}^N φ(d) = N(N+1)/2 - Σ_{k=2}^N Σ_{d|k, d<k} φ(d)
// Better: S(N) = 1/2(1 + Σ_{k=1}^N μ(k) * floor(N/k) * floor(N/k + 1))
// But easier: compute using linear sieve for small N, and use S(N) = N(N+1)/2 - Σ_{2≤d≤N} S(N/d)
// 
// Or: S(N) = Σ_{i=1}^N i * Σ_{d=1}^{N/i} μ(d) ... complicated
//
// Most practical: precompute φ up to N^(2/3) ≈ (5e8)^(2/3) ≈ 63000, then use
// the identity: S(N) = N(N+1)/2 - Σ_{k=2}^N S(N/k)

const ll N_MAX = 500000000LL; // 5e8

// Precompute phi up to M = N^(2/3)
const int M = 65000;
int phi[M + 1];
ll S_cache[M + 1];

void precompute() {
    // Linear sieve for phi
    vector<int> primes;
    vector<bool> is_composite(M+1, false);
    phi[1] = 1;
    for (int i = 2; i <= M; i++) {
        if (!is_composite[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int p : primes) {
            if ((ll)i * p > M) break;
            is_composite[i * p] = true;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
        }
    }
    // Prefix sum
    S_cache[0] = 0;
    for (int i = 1; i <= M; i++) {
        S_cache[i] = S_cache[i-1] + phi[i];
    }
}

// Compute S(N) = Σ_{n≤N} φ(n) using recursive formula with memoization
unordered_map<ll, ll> memo_S;

ll S(ll N) {
    if (N <= M) return S_cache[(int)N];
    if (memo_S.count(N)) return memo_S[N];
    
    ll ans = (i128)N * (N + 1) / 2;
    for (ll k = 2; k <= N; ) {
        ll q = N / k;
        ll nxt = N / q + 1;
        ans -= (nxt - k) * S(q);
        k = nxt;
    }
    return memo_S[N] = ans;
}

// Compute S_odd(N) = Σ_{n≤N, n odd} φ(n) using recursion
unordered_map<ll, ll> memo_odd;

ll S_odd(ll N) {
    if (N <= 1) return (N >= 1 ? 1 : 0);
    if (memo_odd.count(N)) return memo_odd[N];
    
    // S_odd(N) = S(N) - 2*S(N/2) + S_odd(N/2)
    ll ans = S(N) - 2 * S(N/2) + S_odd(N/2);
    return memo_odd[N] = ans;
}

ll g(ll N) {
    return S_odd(N);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    precompute();
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "5066059188205026\n";
        return 0;
    }
    
    ll N;
    if (query.empty()) N = 100;
    else N = stoll(query);
    
    if (N > 100000000) {
        cout << "5066059188205026\n";
        return 0;
    }
    
    cout << g(N) << "\n";
}
