#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){ll n;cin>>n;vector<ll> s={0,1,2,3};ll lm=min(n,20LL);
for(ll i=4;i<=lm;i++)s.push_back(s[i-1]+s[i-3]);
int m=s.size()-1;ll ans=0;
for(int mask=1;mask<(1<<m);mask++){ll sm=0,mx=0;
for(int i=0;i<m;i++)if(mask&(1<<i)){sm+=s[i+1];mx=max(mx,s[i+1]);}
if(mx<sm-mx)ans++;}
cout<<ans<<"\n";return 0;}
