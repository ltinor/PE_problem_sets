#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 760: Summing over bitwise operators / 位运算求和
//
// g(m,n) = (m⊕n)+(m∨n)+(m∧n) = 2*(m∨n)
// G(N) = 2 * Σ_{n=0}^{N} Σ_{k=0}^{n} (k OR (n-k))
//
// For each bit b, count pairs where bit is set in k OR (n-k)
// = total pairs - pairs where both k and n-k have bit b = 0
//
// O(log N) per bit using closed-form formulas.

const ll MOD = 1000000007LL;

// Count pairs where both k and n-k have bit b = 0
i128 count_both_zero(ll N, int b) {
    ll B = 1LL << b;
    ll M = 2 * B;
    
    // For bits where B > N, all pairs have bit 0
    if (B > N) {
        return (i128)(N + 1) * (N + 2) / 2;
    }
    
    ll Q = N / M;
    ll R = N % M;
    
    // sum of count_i(r) for r = 0..limit
    auto sum_count = [&](ll limit) -> i128 {
        if (limit < 0) return 0;
        if (limit >= M) limit = M - 1;
        
        if (limit < B) {
            return (i128)(limit + 1) * (limit + 2) / 2;
        } else {
            // 0 to B-1: B(B+1)/2
            i128 first = (i128)B * (B + 1) / 2;
            // B to limit: Σ (2B-1-r) = Σ t where t = 2B-1-r
            ll lo = 2 * B - 1 - limit; // smallest t
            ll hi = B - 1;              // largest t
            ll cnt = hi - lo + 1;
            i128 second = (i128)(lo + hi) * cnt / 2;
            return first + second;
        }
    };
    
    i128 sum_all = (i128)B * B;  // Σ_{r=0}^{M-1} count_i(r) = B^2
    i128 sum_rem = sum_count(R);
    
    return (i128)Q * (Q + 1) / 2 * sum_all + (i128)(Q + 1) * sum_rem;
}

ll solve_G(ll N) {
    i128 total_pairs = (i128)(N + 1) * (N + 2) / 2;
    ll total_mod = total_pairs % MOD;
    
    ll ans = 0;
    int max_bits = 0;
    while ((1LL << max_bits) <= N) max_bits++;
    max_bits++; // one extra for safety
    
    for (int b = 0; b < max_bits; b++) {
        ll B = 1LL << b;
        i128 both_zero = count_both_zero(N, b);
        i128 bit_one = total_pairs - both_zero;
        ll contrib = (ll)(bit_one % MOD) * (B % MOD) % MOD;
        ans = (ans + contrib) % MOD;
    }
    
    ans = ans * 2 % MOD;
    return ans;
}

ll brute_G(ll N) {
    ll total = 0;
    for (ll n = 0; n <= N; n++) {
        for (ll k = 0; k <= n; k++) {
            ll m = n - k;
            ll g = (k ^ m) + (k | m) + (k & m);
            total += g;
        }
    }
    return total;
}

void verify_small() {
    cout << "PE 760: Summing over bitwise operators / 位运算求和\n\n";
    
    cout << "Verification:\n";
    for (ll N : {0, 1, 2, 3, 5, 10, 20, 50, 100}) {
        ll dp = solve_G(N);
        ll br = brute_G(N);
        cout << "  G(" << setw(3) << N << ") = " << setw(10) << dp 
             << " (brute: " << setw(10) << br << ") "
             << (dp == br ? "✓" : "✗") << "\n";
    }
    
    cout << "\nKnown values:\n";
    cout << "  G(10) = " << solve_G(10) << " (expected 754)\n";
    cout << "  G(100) = " << solve_G(100) << " (expected 583766)\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        ll ans = solve_G(1000000000000000000LL);
        cout << ans << "\n";
        return 0;
    }
    
    if (query == "verify") {
        verify_small();
        return 0;
    }
    
    if (query == "compute") {
        cout << "Computing G(10^18) mod 1e9+7...\n";
        ll ans = solve_G(1000000000000000000LL);
        cout << "G(10^18) mod 1e9+7 = " << ans << "\n";
        return 0;
    }
    
    cout << "PE 760: Summing over bitwise operators\n";
    cout << "G(10^18) mod 1e9+7 = " << solve_G(1000000000000000000LL) << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks, 'compute' to recalc.\n";
    return 0;
}
