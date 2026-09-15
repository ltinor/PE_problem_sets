#include<bits/stdc++.h>
using namespace std;

const int COINS[] = {1, 2, 5, 10, 20, 50, 100, 200};
const int C = 8;

using int128 = __int128;

void print128(int128 x){
    if(x == 0){ cout << "0"; return; }
    string s;
    while(x > 0){
        s += char('0' + (x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Independent implementation using 2D DP (bottom-up)
    // dp[i][j] = ways using first i coins to make amount j
    vector<vector<int128>> dp(C + 1, vector<int128>(n + 1, 0));
    for(int i = 0; i <= C; i++) dp[i][0] = 1;

    for(int i = 1; i <= C; i++){
        int coin = COINS[i - 1];
        for(int j = 1; j <= n; j++){
            dp[i][j] = dp[i - 1][j];
            if(j >= coin){
                dp[i][j] += dp[i][j - coin];
            }
        }
    }

    print128(dp[C][n]);
    cout << "\n";
}
