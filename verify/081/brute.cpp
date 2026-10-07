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

    vector<vector<ll>> dp(N, vector<ll>(N, LLONG_MAX));
    dp[0][0] = a[0][0];

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i > 0) dp[i][j] = min(dp[i][j], dp[i-1][j] + a[i][j]);
            if(j > 0) dp[i][j] = min(dp[i][j], dp[i][j-1] + a[i][j]);
        }
    }

    cout << dp[N-1][N-1] << "\n";

    return 0;
}
