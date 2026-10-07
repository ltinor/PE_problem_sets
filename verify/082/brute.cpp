#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<ll>> a(N, vector<ll>(N));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> a[i][j];
        }
    }

    // brute: same column-by-column DP
    vector<vector<ll>> dp(N, vector<ll>(N, 0));
    for(int i = 0; i < N; i++){
        dp[i][0] = a[i][0];
    }

    for(int j = 1; j < N; j++){
        for(int i = 0; i < N; i++){
            dp[i][j] = dp[i][j-1] + a[i][j];
        }
        for(int i = 1; i < N; i++){
            dp[i][j] = min(dp[i][j], dp[i-1][j] + a[i][j]);
        }
        for(int i = N - 2; i >= 0; i--){
            dp[i][j] = min(dp[i][j], dp[i+1][j] + a[i][j]);
        }
    }

    ll ans = LLONG_MAX;
    for(int i = 0; i < N; i++){
        ans = min(ans, dp[i][N-1]);
    }

    cout << ans << "\n";

    return 0;
}
