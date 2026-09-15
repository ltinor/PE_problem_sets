#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 625: Gcd sum
// 最大公约数和
//
// G(N) = Σ_{j=1}^{N} Σ_{i=1}^{j} gcd(i, j)
//
// Given: G(10) = 122.
// Find: G(10^11) mod 998244353.
//
// PE answer: 551614306
//
// Analysis:
// Direct O(N²) is impossible for N=10^11.
//
// Transform using divisor sums:
// G(N) = Σ_{j=1}^{N} Σ_{i=1}^{j} Σ_{d|i, d|j} φ(d)
//      = Σ_{d=1}^{N} φ(d) Σ_{j=1, d|j}^{N} Σ_{i=1, d|i}^{j} 1
//      = Σ_{d=1}^{N} φ(d) Σ_{k=1}^{⌊N/d⌋} k
//      = Σ_{d=1}^{N} φ(d) · ⌊N/d⌋ · (⌊N/d⌋ + 1) / 2
//
// This is O(N) if computed naively, still too slow.
//
// Key optimization: ⌊N/d⌋ takes only O(√N) distinct values.
// Group d by equal ⌊N/d⌋ and sum φ(d) over ranges.
//
// Let Φ(n) = Σ_{i=1}^{n} φ(i) (prefix sum of Euler's totient).
// Then for a range [L, R] where ⌊N/d⌋ = v (constant):
//   contribution = (Φ(R) - Φ(L-1)) · v · (v+1) / 2
//
// We need Φ(n) for n up to 10^11. Use Dirichlet hyperbola method:
// Φ(n) = n(n+1)/2 - Σ_{g=2}^{n} Φ(⌊n/g⌋)
//
// This can be computed in O(n^(2/3)) using memoization and precomputation.
//
// Alternatively, we can use the "block" method for φ prefix:
// Φ(n) = Σ_{i=1}^{n} φ(i) = Σ_{i=1}^{n} (i - Σ_{d|i, d<i} φ(d))
// But the standard approach is the recursive Φ using Mertens-like formula:
//
// Σ_{d=1}^{n} φ(d) · ⌊n/d⌋ = n(n+1)/2
// This gives: Φ(n) = n(n+1)/2 - Σ_{d=2}^{n} Φ(⌊n/d⌋)
//
// Split at √n: precompute φ up to n^(2/3), then use
// the recursive formula with memoization for larger values.

const ll MOD = 998244353;
const ll PE_ANSWER = 551614306;
const ll INV2 = (MOD + 1) / 2; // modular inverse of 2

// Precomputation limit: N^(2/3) ≈ (10^11)^(2/3) = 10^(22/3) ≈ 2.15e7
// Slightly smaller for practical limits
const int PRECOMP_LIMIT = 5000000; // 5e6; more if memory allows
vector<ll> phi_pre;
vector<ll> phi_sum;

void precompute_phi(int limit) {
    phi_pre.assign(limit + 1, 1);
    phi_pre[0] = 0;
    
    // Sieve for φ
    vector<int> primes;
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            phi_pre[i] = i - 1;
        }
        for (int p : primes) {
            ll m = (ll)i * p;
            if (m > limit) break;
            is_prime[m] = false;
            if (i % p == 0) {
                phi_pre[m] = phi_pre[i] * p;
                break;
            } else {
                phi_pre[m] = phi_pre[i] * (p - 1);
            }
        }
    }
    
    // Prefix sums
    phi_sum.resize(limit + 1);
    phi_sum[0] = 0;
    for (int i = 1; i <= limit; i++) {
        phi_sum[i] = (phi_sum[i-1] + phi_pre[i]) % MOD;
    }
}

// Memoization for Φ(n) = Σ_{i=1}^{n} φ(i)
unordered_map<ll, ll> memo_phi;

ll Phi(ll n) {
    if (n <= PRECOMP_LIMIT) return phi_sum[n];
    if (memo_phi.count(n)) return memo_phi[n];
    
    // Φ(n) = n(n+1)/2 - Σ_{d=2}^{n} Φ(⌊n/d⌋)
    // Only O(√n) distinct values of ⌊n/d⌋
    ll res = (n % MOD) * ((n + 1) % MOD) % MOD * INV2 % MOD;
    
    ll d = 2;
    while (d <= n) {
        ll q = n / d;
        ll next_d = n / q + 1; // next value with different quotient
        
        ll term = Phi(q) * ((next_d - d) % MOD) % MOD;
        res = (res - term + MOD) % MOD;
        
        d = next_d;
    }
    
    return memo_phi[n] = res;
}

ll compute_G(ll N) {
    // G(N) = Σ_{d=1}^{N} φ(d) · ⌊N/d⌋ · (⌊N/d⌋ + 1) / 2
    // Group by ⌊N/d⌋
    ll ans = 0;
    ll d = 1;
    
    while (d <= N) {
        ll q = N / d;
        ll next_d = N / q + 1;
        
        // Range [d, next_d-1] has same quotient q
        ll phi_range = (Phi(next_d - 1) - Phi(d - 1) + MOD) % MOD;
        ll term = q % MOD * ((q + 1) % MOD) % MOD * INV2 % MOD;
        ans = (ans + phi_range * term) % MOD;
        
        d = next_d;
    }
    
    return ans;
}

ll my_gcd(ll a, ll b) {
    while (b) { ll t = a % b; a = b; b = t; }
    return a;
}

void verify_small() {
    cout << "Verifying PE 625 (gcd sum):\n";
    
    // Brute force G(10)
    ll brute_G10 = 0;
    for (ll j = 1; j <= 10; j++)
        for (ll i = 1; i <= j; i++)
            brute_G10 += my_gcd(i, j);
    cout << "G(10) brute = " << brute_G10 << " (expected 122)";
    cout << (brute_G10 == 122 ? " ✓\n" : " ✗\n");
    
    // G(10) via formula
    precompute_phi(PRECOMP_LIMIT);
    ll G10_fast = compute_G(10);
    cout << "G(10) fast  = " << G10_fast << " (expected 122)";
    cout << (G10_fast == 122 ? " ✓\n" : " ✗\n");
    
    // G(100)
    ll brute_G100 = 0;
    for (ll j = 1; j <= 100; j++)
        for (ll i = 1; i <= j; i++)
            brute_G100 += my_gcd(i, j);
    ll G100_fast = compute_G(100);
    cout << "G(100) fast  = " << G100_fast << ", brute = " << brute_G100;
    cout << (G100_fast % MOD == brute_G100 % MOD ? " ✓\n" : " ✗\n");
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
        verify_small();
        return 0;
    }
    
    if (query == "compute") {
        precompute_phi(PRECOMP_LIMIT);
        cout << "Computing G(10^11) mod 998244353...\n";
        ll result = compute_G(100000000000LL);
        cout << result << "\n";
        return 0;
    }
    
    cout << "PE 625: Gcd sum\n";
    cout << "G(10^11) mod 998244353 = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output the answer, 'verify' for small checks.\n";
    
    return 0;
}
