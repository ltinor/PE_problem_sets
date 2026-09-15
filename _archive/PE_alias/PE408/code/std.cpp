#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE408: Admissible paths through a grid
// Path from (0,0) to (n,n) using right/up steps.
// A point (x,y) is admissible if gcd(x,y) = 1 (x,y > 0)
// Plus (0,0) and (n,n) always admissible, and axes points (x,0) and (0,y) always admissible.
// Count number of admissible paths modulo MOD.
// PE answer: 299742733 (possibly for some n with MOD=10^9+7 or MOD=10^9+9)

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    ll n, MOD;
    cin >> n >> MOD;
    
    // DP[y][x] — number of paths to (x,y)
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, 0));
    dp[0][0] = 1;
    
    for (int x = 0; x <= n; x++) {
        for (int y = 0; y <= n; y++) {
            if (x == 0 && y == 0) continue;
            
            // Check admissibility
            if ((x == n && y == n) || x == 0 || y == 0) {
                // Always admissible
            } else if (gcd(x, y) != 1) {
                dp[y][x] = 0;
                continue;
            }
            
            ll val = 0;
            if (x > 0) val += dp[y][x-1];
            if (y > 0) val += dp[y-1][x];
            dp[y][x] = val % MOD;
        }
    }
    
    cout << dp[n][n] << "\n";
}
