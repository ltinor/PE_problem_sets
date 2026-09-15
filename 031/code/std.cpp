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

    vector<int128> dp(n + 1, 0);
    dp[0] = 1;

    for(int i = 0; i < C; i++){
        int coin = COINS[i];
        for(int j = coin; j <= n; j++){
            dp[j] += dp[j - coin];
        }
    }

    print128(dp[n]);
    cout << "\n";
}
