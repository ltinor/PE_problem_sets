#include<bits/stdc++.h>
using namespace std;
using ll=long long;

// PE408 brute: same DP but for small n
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n, MOD; cin >> n >> MOD;
    vector<vector<ll>> dp(n+1, vector<ll>(n+1,0));
    dp[0][0]=1;
    for(int x=0;x<=n;x++){
        for(int y=0;y<=n;y++){
            if(x==0&&y==0)continue;
            if(!((x==n&&y==n)||x==0||y==0) && __gcd(x,y)!=1){
                dp[y][x]=0; continue;
            }
            ll val=0;
            if(x>0)val+=dp[y][x-1];
            if(y>0)val+=dp[y-1][x];
            dp[y][x]=val%MOD;
        }
    }
    cout<<dp[n][n]<<"\n";
}
