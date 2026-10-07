#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: 对N≤6暴力枚举验证
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    if(N > 6){
        // 大N用DP
        vector<vector<ll>> cur(10, vector<ll>(10, 0));
        for(int a=1; a<=9; a++)
            for(int b=0; b<=9; b++)
                if(a+b <= 9) cur[a][b] = 1;

        if(N == 1){ cout << 9 << "\n"; return 0; }
        if(N == 2){
            ll ans = 0;
            for(int a=1; a<=9; a++)
                for(int b=0; b<=9; b++)
                    if(a+b <= 9) ans++;
            cout << ans << "\n"; return 0;
        }
        for(int i=3; i<=N; i++){
            vector<vector<ll>> nxt(10, vector<ll>(10, 0));
            for(int a=0; a<=9; a++)
                for(int b=0; b<=9; b++){
                    if(cur[a][b]==0) continue;
                    for(int c=0; c<=9; c++)
                        if(a+b+c <= 9) nxt[b][c] += cur[a][b];
                }
            cur = std::move(nxt);
        }
        ll ans = 0;
        for(int a=0; a<=9; a++)
            for(int b=0; b<=9; b++)
                ans += cur[a][b];
        cout << ans << "\n";
        return 0;
    }

    // 暴力枚举所有N位数
    ll start = 1;
    for(int i=1; i<N; i++) start *= 10;
    ll end = start * 10;
    ll ans = 0;
    for(ll x=start; x<end; x++){
        string s = to_string(x);
        bool ok = true;
        for(int i=0; i+2 < (int)s.size(); i++){
            if((s[i]-'0')+(s[i+1]-'0')+(s[i+2]-'0') > 9){
                ok = false;
                break;
            }
        }
        if(ok) ans++;
    }
    cout << ans << "\n";
}
