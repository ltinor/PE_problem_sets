#include<bits/stdc++.h>
using namespace std;
using ll=long long;
ll divs(ll n){ll t=n*(n+1)/2,c=0;for(ll i=1;i*i<=t;i++){if(t%i==0){c++;if(i*i!=t)c++;}}return c;}
int main(){int n;cin>>n;vector<ll>dT(n+1);
for(int i=1;i<=n;i++)dT[i]=divs(i);
ll ans=0;for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)for(int k=j+1;k<=n;k++)if(dT[i]>dT[j]&&dT[j]>dT[k])ans++;
cout<<ans<<"\n";return 0;}
