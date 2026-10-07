#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_pal(ll x){
    string s = to_string(x);
    for(int i=0;i<(int)s.size()/2;i++)
        if(s[i]!=s[s.size()-1-i]) return false;
    return true;
}

int main(){
    ll K, W;
    cin >> K >> W;

    const ll MAX_VAL = 100000000; // for brute
    map<ll,int> cnt;
    for(ll a=2;a*a<=MAX_VAL;a++){
        for(ll b=2;b*b*b<=MAX_VAL;b++){
            ll val=a*a+b*b*b;
            if(val<=MAX_VAL) cnt[val]++;
            else break;
        }
    }
    vector<ll> res;
    for(auto &p:cnt)
        if(p.second==W && is_pal(p.first))
            res.push_back(p.first);
    sort(res.begin(),res.end());
    ll ans=0;
    for(int i=0;i<min((ll)res.size(),K);i++)
        ans+=res[i];
    cout<<ans<<"\n";
}
