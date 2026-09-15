#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 164: 参数化N，求N位数中任意连续三位和≤9的个数
// DP[i][a][b] = 前i位，末两位为ab的方案数

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // dp[a][b] = 末两位为ab的方案数
    vector<vector<ll>> dp(10, vector<ll>(10, 0));

    // 初始化：第一位（非零）
    for(int a=1; a<=9; a++){
        // 第二位可以是0-9，只要 a+0+b≤9 → b≤9-a
        dp[0][a] = 1; // 实际上第一位用a表示，第二位还没定
    }

    // 重新构建：dp_i[a][b] 表示已处理i位（i≥2），末两位是ab
    // 当i=2时：第一位d1∈[1,9]，第二位d2∈[0,9]，满足d1+d2≤9
    vector<vector<ll>> cur(10, vector<ll>(10, 0));
    for(int a=1; a<=9; a++){
        for(int b=0; b<=9; b++){
            if(a + b <= 9){
                cur[a][b] = 1;
            }
        }
    }

    if(N == 1){
        // 1位数：1-9都满足（没有连续三位）
        cout << 9 << "\n";
        return 0;
    }
    if(N == 2){
        ll ans = 0;
        for(int a=1; a<=9; a++)
            for(int b=0; b<=9; b++)
                if(a + b <= 9) ans++;
        cout << ans << "\n";
        return 0;
    }

    for(int i=3; i<=N; i++){
        vector<vector<ll>> nxt(10, vector<ll>(10, 0));
        for(int a=0; a<=9; a++){
            for(int b=0; b<=9; b++){
                if(cur[a][b] == 0) continue;
                for(int c=0; c<=9; c++){
                    if(a + b + c <= 9){
                        nxt[b][c] += cur[a][b];
                    }
                }
            }
        }
        cur = std::move(nxt);
    }

    ll ans = 0;
    for(int a=0; a<=9; a++)
        for(int b=0; b<=9; b++)
            ans += cur[a][b];

    cout << ans << "\n";
}
