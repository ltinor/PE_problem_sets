#include<bits/stdc++.h>
using namespace std;
using ll=long long;

// PE409 brute: enumerate all subsets of {1..n}, count winning
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    ll n, MOD; cin>>n>>MOD;
    // DP over XOR values
    vector<ll> dp(1<<(64-__builtin_clzll(n)+1), 0); // use map instead
    unordered_map<ll,ll> mp;
    mp[0]=1;
    for(ll x=1;x<=n;x++){
        auto nmp=mp;
        for(auto&[v,c]:mp){
            nmp[v^x]=(nmp[v^x]+c)%MOD;
        }
        mp=move(nmp);
    }
    ll total=0;
    for(auto&[v,c]:mp) total=(total+c)%MOD;
    ll losing=mp[0];
    ll winning=(total-losing+MOD)%MOD;
    cout<<winning<<"\n";
}
