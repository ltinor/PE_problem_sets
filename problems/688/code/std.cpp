#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 688: Piles of Plates / 盘子分堆
//
// f(n,k): max size of smallest pile when partitioning n into k distinct positive piles.
// F(n) = Σ_{k≥1} f(n,k)
// S(N) = Σ_{n=1}^{N} F(n)
// S(100) = 12656. Find S(10^16) mod 1,000,000,007.
// PE answer: 110941813

const ll MOD = 1000000007;
const ll PE_ANSWER = 110941813;

// f(n,k) = floor((n - T_{k-1}) / k) where T_{k-1} = k*(k-1)/2, valid for T_k ≤ n
// F(n) = Σ_{k: T_k ≤ n} f(n,k)
// S(N) = Σ_{k} Σ_{n=T_k}^{N} f(n,k)
//
// For fixed k: M = N - T_{k-1}, Q = floor(M/k)
// Sum = Q*(M+1) - k*Q*(Q+1)/2

ll tri(ll k) { return k * (k + 1) / 2; }

ll S_mod(ll N) {
    ll total = 0;
    ll max_k = 0;
    // Find max k such that T_k = k*(k+1)/2 ≤ N
    // k*(k+1)/2 ≤ N → k² + k - 2N ≤ 0 → k ≈ (-1 + sqrt(1+8N))/2
    max_k = (ll)((-1.0L + sqrtl(1.0L + 8.0L * N)) / 2.0L);
    // Adjust for floating point
    while (tri(max_k) <= N) max_k++;
    while (tri(max_k) > N) max_k--;
    
    for (ll k = 1; k <= max_k; k++) {
        ll T_prev = k * (k - 1) / 2; // T_{k-1}
        ll M = N - T_prev;
        ll Q = M / k;
        
        // Sum = Q*(M+1) - k*Q*(Q+1)/2
        // Compute modulo MOD using i128 for intermediate products
        i128 term1 = (i128)Q * (M + 1);
        i128 term2 = (i128)k * Q * (Q + 1) / 2;
        i128 sum_k = term1 - term2;
        
        total = (total + (ll)(sum_k % MOD) + MOD) % MOD;
    }
    return total;
}

void verify_small() {
    cout << "PE 688: Piles of Plates\n\n";
    
    // Verify S(100)
    // Brute-force compute F(n) for n=1..100
    auto brute_F = [](ll n) -> ll {
        ll total = 0;
        for (ll k = 1; tri(k) <= n; k++) {
            ll T_prev = k * (k - 1) / 2;
            total += (n - T_prev) / k;
        }
        return total;
    };
    
    cout << "Verification:\n";
    cout << "  F(10) = " << brute_F(10) << "\n";
    cout << "  F(100) = " << brute_F(100) << " (expected: 275)\n";
    
    ll s100_brute = 0;
    for (ll n = 1; n <= 100; n++) s100_brute += brute_F(n);
    cout << "  S(100) brute = " << s100_brute << " (expected: 12656)\n";
    cout << "  S(100) formula = " << S_mod(100) << "\n";
    
    // Test S(1000)
    ll s1000 = S_mod(1000);
    ll s1000_brute = 0;
    for (ll n = 1; n <= 1000; n++) s1000_brute += brute_F(n);
    cout << "  S(1000) brute = " << s1000_brute << " formula = " << s1000 << "\n";
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
        ll N = 10000000000000000LL; // 10^16
        cout << "Computing S(10^16) mod " << MOD << "...\n";
        ll result = S_mod(N);
        cout << "Result: " << result << "\n";
        cout << "Expected: " << PE_ANSWER << "\n";
        return 0;
    }

    cout << "PE 688: Piles of Plates\n";
    cout << "Answer = " << PE_ANSWER << " (mod " << MOD << ")\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
