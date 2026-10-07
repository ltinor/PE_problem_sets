#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Count odd triplets [n,k,f(n,k)] with n <= N
// Solution: n must be ≡ 1 (mod 4), and for such n, count = 2^{popcount(n)-1}
// Equivalently: answer = sum_{m=0}^{(N-1)/4} 2^{popcount(m)}

// Digit DP: sum of 2^{popcount(x)} for x in [0, M]
ll solve(ll M) {
    if (M < 0) return 0;
    
    // Binary representation of M
    vector<int> bits;
    ll tmp = M;
    while (tmp) { bits.push_back(tmp & 1); tmp >>= 1; }
    reverse(bits.begin(), bits.end());
    int L = bits.size();
    if (L == 0) return 1; // M = 0, only x = 0, 2^0 = 1
    
    // dp[pos][tight] = sum of 2^{popcount} for remaining suffix
    // We'll use memoization
    vector<vector<ll>> memo(L + 1, vector<ll>(2, -1));
    
    function<ll(int, bool)> dfs = [&](int pos, bool tight) -> ll {
        if (pos == L) return 1; // popcount=0 so far → 2^0 = 1
        if (memo[pos][tight] != -1) return memo[pos][tight];
        
        int limit = tight ? bits[pos] : 1;
        ll res = 0;
        for (int d = 0; d <= limit; d++) {
            bool ntight = tight && (d == limit);
            ll sub = dfs(pos + 1, ntight);
            if (d == 1) sub *= 2; // multiply by 2 for each set bit
            res += sub;
        }
        return memo[pos][tight] = res;
    };
    
    return dfs(0, true);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    // M = (N-1)/4
    ll M = (N >= 1) ? (N - 1) / 4 : -1;
    ll ans = solve(M);
    
    // But wait: the formula gives sum_{m=0}^{M} 2^{popcount(m)}
    // For m=0, n=1, count=2^{0}=1. That's correct.
    // For m=1, n=5, popcount(1)=1, 2^1=2. Correct.
    
    cout << ans << "\n";
    return 0;
}
