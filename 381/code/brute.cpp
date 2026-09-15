#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll modpow(ll a,ll e,ll m){ll r=1;while(e){if(e&1)r=r*a%m;a=a*a%m;e>>=1;}return r;}
ll inv(ll a,ll p){return modpow(a,p-2,p);}
ll S(ll p){ll s=0,f=1;for(ll k=1;k<=p-5;k++)f=f*k%p;s=f;for(ll k=4;k>=1;k--){f=f*(p-k)%p;s=(s+f)%p;}return s;}
int main(){ll L,R;cin>>L>>R;vector<bool> pr(R+1,1);pr[0]=pr[1]=0;
for(ll i=2;i*i<=R;i++)if(pr[i])for(ll j=i*i;j<=R;j+=i)pr[j]=0;
ll t=0;for(ll p=max(L,5LL);p<R;p++)if(pr[p])t+=S(p);cout<<t<<"\n";return 0;}
