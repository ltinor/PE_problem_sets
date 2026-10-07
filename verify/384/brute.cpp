#include<bits/stdc++.h>
using namespace std;
using ll=long long;
ll a(ll n){ll c=0;while(n){if((n&3)==3)c++;n>>=1;}return c;}
int b(ll n){return (a(n)&1)?-1:1;}
int main(){ll L,R;cin>>L>>R;
vector<ll>F(50);F[0]=F[1]=1;for(int i=2;i<=46;i++)F[i]=F[i-1]+F[i-2];
ll SZ=5000000;vector<int>s(SZ+1);s[0]=1;for(ll i=1;i<=SZ;i++)s[i]=s[i-1]+b(i);
ll t=0;for(ll i=L;i<=R;i++){ll tg=F[i],nd=F[i-1];ll cnt=0;
for(ll j=0;j<=SZ;j++){if(s[j]==tg){cnt++;if(cnt==nd){t+=j;break;}}}}
cout<<t<<"\n";return 0;}
