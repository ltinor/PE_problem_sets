#include<bits/stdc++.h>
using namespace std;
using ll=long long;
ll ggg(ll a,ll b){return b?ggg(b,a%b):a;}
int main(){ll N;cin>>N;ll ans=0;
for(ll x=1;x<=N;x++)for(ll y=x;y<=N;y++)if(x*y/ggg(x,y)<=N)ans++;
cout<<ans<<"\n";return 0;}
