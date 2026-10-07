#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 201 — Subsets with a unique sum
// S = {1^2, 2^2, ..., N^2}, choose K elements
// Find sum of subset sums that appear exactly once
// DP: dp[j][s] = number of ways (capped at 2)

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, K;
    cin >> N >> K;

    // Compute max possible sum: sum of largest K squares
    ll maxSum = 0;
    for(ll i = N; i > N-K; i--) maxSum += i*i;

    // dp[j][s] capped at 2
    vector<vector<char>> dp(K+1, vector<char>(maxSum+1, 0));
    dp[0][0] = 1;

    for(ll i = 1; i <= N; i++){
        ll v = i*i;
        for(ll j = K; j >= 1; j--){
            for(ll s = maxSum; s >= v; s--){
                if(dp[j-1][s-v]){
                    dp[j][s] = min(2, dp[j][s] + dp[j-1][s-v]);
                }
            }
        }
    }

    ll ans = 0;
    for(ll s = 1; s <= maxSum; s++){
        if(dp[K][s] == 1) ans += s;
    }
    cout << ans << "\n";
}
