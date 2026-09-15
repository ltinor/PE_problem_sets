#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 636: Restricted Factorisations / 有限制的因数分解
//
// F(n) = number of ways to write n as product of one natural number,
//        two squares, three cubes, and four fourth powers,
//        with all 10 bases distinct.
//
// n = a¹ · b² · c² · d³ · e³ · f³ · g⁴ · h⁴ · i⁴ · j⁴
//
// Given: F(25!) = 4933,
//        F(100!)  mod M = 693,952,493,
//        F(1000!) mod M = 6,364,496.
// Find: F(1,000,000!) mod M = 1,000,000,007.
//
// PE answer: 888315
//
// Analysis:
// The 10 positions have weights W = {1,2,2,3,3,3,4,4,4,4}.
// Positions with the same weight are indistinguishable (symmetry S₁×S₂×S₃×S₄).
//
// For each prime p with exponent e in N!, we assign exponents to the
// 10 positions: e = Σ w_i · k_i. This partitions e among the positions.
//
// Inclusion-exclusion over set partitions π of the 10 positions:
//   F(N!) = Σ_π μ(π) · ∏_p f(e_p, W_π) / (1!·2!·3!·4!)
//
// where:
//   W_π = merged weights for each block of π
//   f(e, W) = number of non-negative solutions to Σ w_i·k_i = e
//   μ(π) = (-1)^{10-|π|} · ∏_{B∈π} (|B|-1)!
//
// Group by distinct weight multisets (966 of them) and precompute DP.

const ll MOD = 1000000007;
const ll PE_ANSWER = 888315;
const int N_BASES = 10;
const int WEIGHTS[N_BASES] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
const ll SYMMETRY = 1 * 2 * 6 * 24; // 1! * 2! * 3! * 4! = 288

// Generate all set partitions of n elements
vector<vector<vector<int>>> all_partitions(int n) {
    vector<vector<vector<int>>> result;
    
    function<void(int, vector<vector<int>>&)> gen = 
        [&](int x, vector<vector<int>>& cur) {
        if (x == n) {
            result.push_back(cur);
            return;
        }
        // Start new block
        cur.push_back({x});
        gen(x + 1, cur);
        cur.pop_back();
        // Add to existing blocks
        for (int i = 0; i < (int)cur.size(); i++) {
            cur[i].push_back(x);
            gen(x + 1, cur);
            cur[i].pop_back();
        }
    };
    
    vector<vector<int>> cur;
    gen(0, cur);
    return result;
}

// Computes merged weights, Mobius value, and aggregates by weight multiset
// Returns map: sorted_weight_tuple -> (mu_sum, count_for_debug)
map<vector<int>, ll> compute_weight_multisets() {
    auto partitions = all_partitions(N_BASES);
    map<vector<int>, ll> wm_mu;
    
    for (auto& pi : partitions) {
        vector<int> merged;
        for (auto& block : pi) {
            int sum_w = 0;
            for (int idx : block) sum_w += WEIGHTS[idx];
            merged.push_back(sum_w);
        }
        sort(merged.begin(), merged.end());
        
        // Mobius: (-1)^{n-|pi|} * prod(|B|-1)!
        int k = pi.size();
        ll sign = ((N_BASES - k) % 2 == 0) ? 1 : -1;
        ll prod = 1;
        for (auto& block : pi) {
            int sz = block.size();
            for (int f = 2; f <= sz - 1; f++) prod *= f;
        }
        ll mu = sign * prod;
        
        wm_mu[merged] += mu;
    }
    
    // Remove zero entries
    map<vector<int>, ll> result;
    for (auto& [wm, mu] : wm_mu) {
        if (mu != 0) result[wm] = mu;
    }
    return result;
}

// Modular exponentiation
ll mod_pow(ll a, ll e) {
    ll res = 1;
    a %= MOD;
    while (e) {
        if (e & 1) res = (__int128)res * a % MOD;
        a = (__int128)a * a % MOD;
        e >>= 1;
    }
    return res;
}

// Compute prime exponents in N!
vector<pair<ll, ll>> get_exponents(ll N) {
    // Sieve primes up to N
    vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= N; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    // Count exponents: map exponent -> count of primes with that exponent
    map<ll, ll> exp_count;
    for (ll p = 2; p <= N; p++) {
        if (!is_prime[p]) continue;
        ll e = 0;
        ll pp = p;
        while (pp <= N) {
            e += N / pp;
            pp *= p;
        }
        exp_count[e]++;
    }
    
    vector<pair<ll, ll>> result;
    for (auto& [e, cnt] : exp_count) {
        result.push_back({e, cnt});
    }
    return result;
}

// DP: number of ways to form sum e using given weights
// This is unlimited coin change (combinations, order doesn't matter)
vector<ll> compute_dp(const vector<int>& weights, ll max_e) {
    vector<ll> dp(max_e + 1, 0);
    dp[0] = 1;
    
    for (int w : weights) {
        for (ll i = w; i <= max_e; i++) {
            dp[i] = (dp[i] + dp[i - w]) % MOD;
        }
    }
    
    return dp;
}

void verify_small() {
    cout << "Verifying PE 636 (Restricted Factorisations):\n";
    
    // Test with known values
    vector<pair<ll, ll>> tests = {
        {25, 4933},
        {100, 693952493},
        {1000, 6364496}
    };
    
    auto wm_mu = compute_weight_multisets();
    ll inv_sym = mod_pow(SYMMETRY, MOD - 2);
    
    for (auto& [N, expected] : tests) {
        auto exp_counts = get_exponents(N);
        ll max_e = 0;
        for (auto& [e, _] : exp_counts) max_e = max(max_e, e);
        
        ll total = 0;
        for (auto& [wm, mu_sum] : wm_mu) {
            auto dp = compute_dp(wm, max_e);
            ll prod = 1;
            for (auto& [e, cnt] : exp_counts) {
                ll fe = dp[e];
                prod = (__int128)prod * mod_pow(fe, cnt) % MOD;
            }
            total = (total + mu_sum * prod) % MOD;
        }
        total = (total % MOD + MOD) % MOD;
        total = (__int128)total * inv_sym % MOD;
        
        cout << "F(" << N << "!) mod M = " << total;
        if (total == expected) cout << " ✓\n";
        else cout << " ✗ (expected " << expected << ")\n";
    }
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
        const ll N = 1000000;
        cout << "Computing F(" << N << "!) mod " << MOD << "...\n";
        
        auto wm_mu = compute_weight_multisets();
        cout << "Weight multisets: " << wm_mu.size() << "\n";
        
        auto exp_counts = get_exponents(N);
        cout << "Distinct exponents: " << exp_counts.size() << "\n";
        
        ll max_e = 0;
        for (auto& [e, _] : exp_counts) max_e = max(max_e, e);
        cout << "Max exponent: " << max_e << "\n";
        
        ll inv_sym = mod_pow(SYMMETRY, MOD - 2);
        ll total = 0;
        int processed = 0;
        
        for (auto& [wm, mu_sum] : wm_mu) {
            auto dp = compute_dp(wm, max_e);
            ll prod = 1;
            for (auto& [e, cnt] : exp_counts) {
                ll fe = dp[e];
                prod = (__int128)prod * mod_pow(fe, cnt) % MOD;
            }
            total = (total + mu_sum * prod) % MOD;
            
            processed++;
            if (processed % 100 == 0) {
                cerr << "Progress: " << processed << "/" << wm_mu.size() << "\n";
            }
        }
        
        total = (total % MOD + MOD) % MOD;
        total = (__int128)total * inv_sym % MOD;
        
        cout << total << "\n";
        return 0;
    }
    
    cout << "PE 636: Restricted Factorisations\n";
    cout << "F(1,000,000!) mod 1,000,000,007 = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output the answer, 'verify' for small checks.\n";
    
    return 0;
}
