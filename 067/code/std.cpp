#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R;
    cin >> R;
    vector<vector<int>> a(R, vector<int>(R));
    for(int i = 0; i < R; i++){
        for(int j = 0; j <= i; j++){
            cin >> a[i][j];
        }
    }

    // 自底向上 DP
    vector<vector<int>> dp(R, vector<int>(R));
    for(int j = 0; j < R; j++){
        dp[R-1][j] = a[R-1][j];
    }
    for(int i = R-2; i >= 0; i--){
        for(int j = 0; j <= i; j++){
            dp[i][j] = a[i][j] + max(dp[i+1][j], dp[i+1][j+1]);
        }
    }

    cout << dp[0][0] << "\n";
    return 0;
}
