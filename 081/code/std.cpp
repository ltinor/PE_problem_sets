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

    vector<vector<ll>> dp(N, vector<ll>(N, 0));
    dp[0][0] = a[0][0];

    // first row
    for(int j = 1; j < N; j++){
        dp[0][j] = dp[0][j-1] + a[0][j];
    }
    // first column
    for(int i = 1; i < N; i++){
        dp[i][0] = dp[i-1][0] + a[i][0];
    }

    for(int i = 1; i < N; i++){
        for(int j = 1; j < N; j++){
            dp[i][j] = a[i][j] + min(dp[i-1][j], dp[i][j-1]);
        }
    }

    cout << dp[N-1][N-1] << "\n";

    return 0;
}
