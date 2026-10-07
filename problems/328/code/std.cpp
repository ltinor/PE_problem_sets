#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE328: Lowest-cost Search
// Hidden number in {1..n}. Each guess costs the guessed number.
// C(n) = worst-case optimal cost. Find Σ_{n=1}^{N} C(n).
// O(N³) DP, N ≤ 1200 for OJ time limit.

const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    vector<vector<ll>> dp(N+2, vector<ll>(N+2, 0));
    
    for (ll len = 2; len <= N; len++) {
        for (ll i = 1; i + len - 1 <= N; i++) {
            ll j = i + len - 1;
            dp[i][j] = INF;
            for (ll k = i; k <= j; k++) {
                ll cost = k + max(dp[i][k-1], dp[k+1][j]);
                if (cost < dp[i][j]) dp[i][j] = cost;
            }
        }
    }
    
    ll sum = 0;
    for (ll n = 1; n <= N; n++) sum += dp[1][n];
    cout << sum << "\n";
    return 0;
}
