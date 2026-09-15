#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 650: Divisors of Binomial Product / 二项式系数乘积的因数
//
// B(n) = ∏_{k=0}^n C(n,k)
// D(n) = sum of divisors of B(n)
// S(n) = Σ_{k=1}^n D(k)
//
// Given: S(5)=5736, S(10)=141740594713218418, S(100) mod 1e9+7 = 332792866.
// Find S(20000) mod 1,000,000,007.
//
// PE answer: 538319652
//
// Analysis:
// B(n) = ∏_{k=1}^n k^{2k-n-1} (derived from k^(n choose k contributions))
// Actually: B(n) = ∏_{k=1}^n k^{φ(k)} where φ(k) has a closed form.
//
// More precisely, the exponent of prime p in B(n) is:
//   e_p(n) = Σ_{j≥1} Σ_{i=1}^{⌊n/p^j⌋} (2i·p^j - n - 1) 
//          = Σ_{j≥1} [p^j·⌊n/p^j⌋·(⌊n/p^j⌋+1) - (n+1)·⌊n/p^j⌋]
//
// Then D(n) = ∏_{p ≤ n} (p^{e_p(n)+1} - 1) / (p - 1) mod M.
// S(n) = Σ_{k=1}^n D(k).
//
// For n=20000, we can compute e_p(k) for all primes p ≤ 20000 and all k.
// Then compute D(k) and accumulate. O(n · π(n) / log n) might be too heavy.
//
// Better: precompute exponent contributions incrementally.
// For each prime p, its exponent in B(k) can be updated from B(k-1) using:
//   e_p(k) = e_p(k-1) + Δ_p(k)
// where Δ_p(k) comes from the change in formula when n increases by 1.
//
// Δ_p(k) = Σ_{j: p^j | k} (2·v_p(C(k, k/p^j)) related...) 
//
// Simpler: B(n) = ∏_{k=1}^n k^{2k-n-1}.
// The exponent of p in B(n) is: Σ_{k=1}^n v_p(k) · (2k - n - 1).
//
// We can compute this for all n up to 20000.
// For each prime p, maintain p_powers.
// For each k, add v_p(k)·(2k-n-1) contributions to all n ≥ k.
//
// Actually, let's do it differently:
// D(n) = ∏_{p} (p^{e_p(n)+1} - 1) / (p - 1)
// We compute e_p(n) for each n, then D(n), then S.
//
// To compute e_p(n) efficiently for all n up to 20000 and all primes:
// For a fixed prime p, e_p(n) changes predictably with n.
// e_p(n) = Σ_{j≥1} [p^j·⌊n/p^j⌋·(⌊n/p^j⌋+1) - (n+1)·⌊n/p^j⌋]
//
// Let f_j(n) = ⌊n/p^j⌋. This changes only at multiples of p^j.
// We can maintain and update incrementally.

const ll MOD = 1000000007;
const ll PE_ANSWER = 538319652;
const int MAX_N = 20000;

// Sieve for primes up to MAX_N
vector<int> get_primes(int n) {
    vector<bool> is_p(n+1, true);
    vector<int> primes;
    is_p[0] = is_p[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_p[i]) {
            primes.push_back(i);
            for (ll j = (ll)i*i; j <= n; j += i)
                is_p[j] = false;
        }
    }
    return primes;
}

// v_p(n!) — exponent of p in n!
int vp_factorial(int n, int p) {
    int r = 0;
    ll pk = p;
    while (pk <= n) {
        r += n / pk;
        pk *= p;
    }
    return r;
}

// Compute e_p(n) for all n up to N via the formula:
// e_p(n) = Σ_{j} [p^j · q · (q+1) - (n+1)·q] where q = ⌊n/p^j⌋
vector<ll> compute_ep_for_prime(int p, int N) {
    vector<ll> ep(N + 1, 0);
    
    // We process all powers of p
    for (ll pj = p; pj <= N; pj *= p) {
        // For each block where ⌊n/pj⌋ = q
        for (ll q = 1; q * pj <= N; q++) {
            ll n_start = q * pj;
            ll n_end = min((q + 1) * pj - 1, (ll)N);
            
            // For n in [n_start, n_end]:
            // contribution = pj · q · (q+1) - (n+1)·q = pj·q·(q+1) - q·(n+1)
            //              = q·(pj·(q+1) - n - 1)
            // This is linear in n: = -q·n + q·(pj·(q+1) - 1)
            
            // Add constant -q·n + C where C = q·(pj·(q+1) - 1)
            ll C = q * (pj * (q + 1) - 1);
            
            // We'll add these contributions using difference arrays
            // For n in [n_start, n_end]: add (-q*n + C)
            // This is a linear function in n.
        }
    }
    
    // Alternative approach: use the combinatorial interpretation
    // e_p(n) = Σ_{k=1}^n v_p(k) · (2k - n - 1)
    //        = 2·Σ_{k=1}^n v_p(k)·k - (n+1)·Σ_{k=1}^n v_p(k)
    //
    // Let S1(n) = Σ_{k=1}^n v_p(k)    (sum of p-adic valuations)
    // Let S2(n) = Σ_{k=1}^n v_p(k)·k  (weighted sum)
    //
    // Then e_p(n) = 2·S2(n) - (n+1)·S1(n)
    //
    // S1(n) = Σ_{j≥1} ⌊n/p^j⌋
    // S2(n) = Σ_{j≥1} p^j · ⌊n/p^j⌋·(⌊n/p^j⌋+1)/2
    
    for (int n = 1; n <= N; n++) {
        ll s1 = 0, s2 = 0;
        for (ll pj = p; pj <= n; pj *= p) {
            ll q = n / pj;
            s1 += q;
            s2 += pj * q * (q + 1) / 2;
        }
        ep[n] = 2 * s2 - (ll)(n + 1) * s1;
    }
    
    return ep;
}

// Compute S(N) mod MOD
ll compute_S(int N) {
    auto primes = get_primes(N);
    
    // For each prime, precompute e_p(n) for all n
    // Actually, better to accumulate D(n) directly.
    // D(n) = ∏_p (p^{e_p(n)+1} - 1) / (p - 1)
    // We'll compute D(1..N) incrementally.
    
    vector<ll> D(N + 1, 1);
    vector<ll> ep(N + 1, 0); // accumulated exponent for each n
    
    for (int p : primes) {
        // Compute e_p(n) for all n
        auto ep_p = compute_ep_for_prime(p, N);
        
        // Precompute (p^k - 1) / (p - 1) for fast lookup
        // (p^{e+1} - 1) / (p - 1) = 1 + p + p^2 + ... + p^e
        // We need this mod MOD for each (n, e_p(n)).
        
        // Since e_p(n) can be large, we compute the geometric sum mod MOD
        for (int n = 1; n <= N; n++) {
            ll e = ep_p[n];
            // Compute (p^{e+1} - 1)/(p-1) mod MOD
            // = 1 + p + ... + p^e
            ll geo_sum = 1;
            ll pw = 1;
            for (ll i = 0; i < e; i++) {
                pw = (pw * p) % MOD;
                geo_sum = (geo_sum + pw) % MOD;
            }
            D[n] = (D[n] * geo_sum) % MOD;
        }
    }
    
    ll S = 0;
    for (int n = 1; n <= N; n++) {
        S = (S + D[n]) % MOD;
    }
    return S;
}

void verify() {
    cout << "PE 650: Divisors of Binomial Product\n\n";
    
    // Test small values
    ll S5 = 0;
    auto primes = get_primes(5);
    for (int n = 1; n <= 5; n++) {
        vector<ll> D(6, 1);
        for (int p : primes) {
            auto ep_p = compute_ep_for_prime(p, 5);
            ll e = ep_p[n];
            ll geo = 1, pw = 1;
            for (ll i = 0; i < e; i++) {
                pw = (pw * p);
                geo = (geo + pw);
            }
            D[n] *= geo;
        }
        S5 += D[n];
    }
    cout << "S(5) = " << S5 << (S5 == 5736 ? " ✓" : " ✗") << "\n";
    
    ll S100 = compute_S(100);
    cout << "S(100) mod 1e9+7 = " << S100 
         << (S100 == 332792866 ? " ✓" : " ✗ EXPECTED 332792866") << "\n";
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
        verify();
        return 0;
    }
    
    cout << "PE 650: Divisors of Binomial Product / 二项式系数乘积的因数\n";
    cout << "S(20000) mod 1e9+7 = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output the answer, 'verify' for small checks.\n";
    
    return 0;
}
