#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE333: Special Partitions
// Valid partition: sum of 2^i*3^j terms, no term divides another
// In grid (i,j): term A divides B iff i_A <= i_B AND j_A <= j_B
// Antichain in product order: when sorted by i increasing, j strictly decreasing
//
// DP: process rows (i=0..max_i). For each row, either skip or pick one term.
// State: (sum, max_allowed_j). max_allowed_j = upper bound on next j.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    // Generate all 2^i*3^j <= N
    vector<pair<int,int>> terms; // (i, j, value)
    vector<tuple<int,int,int>> term_list;
    
    for (int i = 0; (1LL << i) <= N; i++) {
        ll p2 = 1LL << i;
        for (int j = 0; p2 <= N; j++) {
            ll val = p2;
            if (val > N) break;
            term_list.push_back({i, j, (int)val});
            p2 *= 3;
        }
    }
    
    int max_i = 0;
    for (auto [i, j, v] : term_list) max_i = max(max_i, i);
    
    // Group terms by i
    vector<vector<pair<int,int>>> terms_by_i(max_i + 1);
    for (auto [i, j, v] : term_list) {
        terms_by_i[i].push_back({j, v});
    }
    
    // For each row, sort by j
    for (auto& row : terms_by_i) {
        sort(row.begin(), row.end());
    }
    
    // DP: dp[sum] = number of valid partitions with that sum
    // But we need to enforce the antichain constraint
    // Process rows from high i to low i, or use 2D DP
    // 
    // Better approach: DP over grid
    // f[i][j_bound][s] = #ways considering rows 0..i, with restriction that
    // any future term must have j < j_bound
    
    int max_j = 0;
    for (auto [i, j, v] : term_list) max_j = max(max_j, j);
    
    // Use 2D DP rolling: dp[j_bound][sum]
    int SZ = max_j + 2;
    vector<vector<ll>> dp(SZ, vector<ll>(N + 1, 0));
    dp[SZ - 1][0] = 1;  // j_bound = max_j+1 means unrestricted
    
    for (int i = 0; i <= max_i; i++) {
        vector<vector<ll>> ndp(SZ, vector<ll>(N + 1, 0));
        
        for (int jb = 0; jb < SZ; jb++) {
            for (int s = 0; s <= N; s++) {
                if (dp[jb][s] == 0) continue;
                
                // Option 1: skip row i entirely
                ndp[jb][s] += dp[jb][s];
                
                // Option 2: pick one term from row i with j < jb
                for (auto [j, val] : terms_by_i[i]) {
                    if (j >= jb) break;
                    if (s + val <= N) {
                        ndp[j][s + val] += dp[jb][s];
                    }
                }
            }
        }
        
        dp = move(ndp);
    }
    
    // Now dp[jb][n] = number of valid partitions of n
    // We need P(n) = sum over all jb of dp[jb][n]
    // Actually the last row has absorbed all choices; P(n) = sum_{jb} dp[jb][n]
    
    vector<ll> P(N + 1, 0);
    for (int jb = 0; jb < SZ; jb++) {
        for (int n = 1; n <= N; n++) {
            P[n] += dp[jb][n];
        }
    }
    
    // Find all primes q < N with P(q) == 1
    // Sieve
    vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= N; p++) {
        if (is_prime[p]) {
            for (int m = p * p; m <= N; m += p) is_prime[m] = false;
        }
    }
    
    ll ans = 0;
    for (int q = 2; q < N; q++) {
        if (is_prime[q] && P[q] == 1) {
            ans += q;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
