#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 759: A squared recurrence relation / 递推数列的平方和
//
// f(1) = 1
// f(2n) = 2f(n)
// f(2n+1) = 2n+1 + 2f(n) + f(n)/n
//
// Key insight: let g(n) = f(n)/n. Then:
//   g(1) = 1
//   g(2n) = g(n)
//   g(2n+1) = g(n) + 1
// This is exactly popcount(n)! So f(n) = n * popcount(n).
//
// S(N) = Σ_{i=1}^{N} f(i)^2 = Σ_{i=1}^{N} i^2 * popcount(i)^2
// Find S(10^16) mod 1e9+7.
//
// Binary digit DP: process bits of N (10^16 ≈ 2^53.15, 54 bits needed).
// DP state: (bit_pos, tight, popcount) → (count, sum_val, sum_val^2)
//
// PE answer: modulo value (computed below)

const ll MOD = 1000000007LL;

// Compute S(N) mod MOD using binary digit DP
ll solve(ll N) {
    if (N == 0) return 0;
    
    // Get binary representation of N
    vector<int> bits;
    ll tmp = N;
    while (tmp > 0) {
        bits.push_back(tmp & 1);
        tmp >>= 1;
    }
    reverse(bits.begin(), bits.end());
    int L = bits.size();
    
    // Precompute powers of 2 modulo MOD
    vector<ll> pow2(L + 1), pow4(L + 1);
    pow2[0] = 1;
    pow4[0] = 1;
    for (int i = 1; i <= L; i++) {
        pow2[i] = pow2[i-1] * 2 % MOD;
        pow4[i] = pow4[i-1] * 4 % MOD;
    }
    
    // DP[pos][tight][pop] = (cnt, sum, sum2)
    // Use flat array for efficiency
    // pop ranges from 0 to L, tight: 0 or 1
    int max_pop = L;
    int states = (L + 1) * 2 * (max_pop + 1);
    vector<ll> dp_cnt(states, 0);
    vector<ll> dp_sum(states, 0);
    vector<ll> dp_sum2(states, 0);
    
    auto idx = [L, max_pop](int pos, int tight, int pop) {
        return (pos * 2 + tight) * (max_pop + 1) + pop;
    };
    
    // Base: pos = -1 (before MSB), tight=1, pop=0
    dp_cnt[idx(0, 1, 0)] = 1;
    
    for (int pos = 0; pos < L; pos++) {
        int bit_pos = L - 1 - pos; // position from LSB
        ll p2 = pow2[bit_pos];     // 2^{bit_pos} mod MOD
        ll p4 = pow4[bit_pos];     // 4^{bit_pos} mod MOD
        
        int limit = bits[pos];
        
        for (int tight = 0; tight <= 1; tight++) {
            int max_digit = tight ? limit : 1;
            for (int pop = 0; pop <= pos; pop++) {
                ll cnt = dp_cnt[idx(pos, tight, pop)];
                ll sum = dp_sum[idx(pos, tight, pop)];
                ll sum2 = dp_sum2[idx(pos, tight, pop)];
                
                if (cnt == 0 && sum == 0 && sum2 == 0) continue;
                
                for (int d = 0; d <= max_digit; d++) {
                    int ntight = tight && (d == limit);
                    int npop = pop + d;
                    
                    ll ncnt = cnt;
                    ll nsum = (sum + d * p2 % MOD * cnt) % MOD;
                    ll nsum2 = (sum2 + 2LL * d * p2 % MOD * sum % MOD 
                                + (ll)d * p4 % MOD * cnt) % MOD;
                    nsum2 = (nsum2 + MOD) % MOD;
                    
                    int nidx = idx(pos + 1, ntight, npop);
                    dp_cnt[nidx] = (dp_cnt[nidx] + ncnt) % MOD;
                    dp_sum[nidx] = (dp_sum[nidx] + nsum) % MOD;
                    dp_sum2[nidx] = (dp_sum2[nidx] + nsum2) % MOD;
                }
            }
        }
    }
    
    // Sum up contributions: for each final state, add pop^2 * sum2
    ll ans = 0;
    for (int tight = 0; tight <= 1; tight++) {
        for (int pop = 0; pop <= max_pop; pop++) {
            int nidx = idx(L, tight, pop);
            ll sum2 = dp_sum2[nidx];
            if (sum2 > 0) {
                ll contrib = (ll)pop * pop % MOD * sum2 % MOD;
                ans = (ans + contrib) % MOD;
            }
        }
    }
    
    return ans;
}

void verify_small() {
    cout << "PE 759: A squared recurrence relation / 递推数列的平方和\n\n";
    
    // Compute f(n) = n * popcount(n) directly for small n
    cout << "Small values of f(n) = n * popcount(n):\n";
    for (int n = 1; n <= 20; n++) {
        int pc = __builtin_popcount(n);
        ll fn = (ll)n * pc;
        cout << "  f(" << setw(2) << n << ") = " << setw(4) << fn 
             << " (popcount=" << pc << ")\n";
    }
    
    // Verify S(10) and S(100)
    auto brute_S = [](ll N) {
        ll s = 0;
        for (ll i = 1; i <= N; i++) {
            int pc = __builtin_popcount(i);
            ll fi = i * pc;
            s += fi * fi;
        }
        return s;
    };
    
    cout << "\nVerification:\n";
    cout << "  S(10) = " << brute_S(10) << " (expected 1530) "
         << (brute_S(10) == 1530 ? "✓" : "✗") << "\n";
    cout << "  S(100) = " << brute_S(100) << " (expected 4798445) "
         << (brute_S(100) == 4798445 ? "✓" : "✗") << "\n";
    
    // Test DP against brute for small N (mod comparison)
    cout << "\nDP vs brute (mod " << MOD << ") for small N:\n";
    for (ll N : {10, 100, 1000, 10000, 100000, 1000000}) {
        ll dp = solve(N);
        ll br = brute_S(N) % MOD;
        cout << "  N=" << setw(7) << N << ": DP=" << dp 
             << " brute_mod=" << br << " "
             << (dp == br ? "✓" : "✗") << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        ll ans = solve(10000000000000000LL); // 10^16
        cout << ans << "\n";
        return 0;
    }
    
    if (query == "verify") {
        verify_small();
        return 0;
    }
    
    if (query == "compute") {
        cout << "Computing S(10^16) mod 1e9+7...\n";
        ll ans = solve(10000000000000000LL);
        cout << "S(10^16) mod 1e9+7 = " << ans << "\n";
        return 0;
    }
    
    cout << "PE 759: A squared recurrence relation / 递推数列的平方和\n";
    cout << "S(10^16) mod 1e9+7 = " << solve(10000000000000000LL) << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
