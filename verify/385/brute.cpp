#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int main(){ll n;cin>>n;ll ans=0;
for(ll x1=-n;x1<=n;x1++)for(ll y1=-n;y1<=n;y1++)
for(ll x2=-n;x2<=n;x2++)for(ll y2=-n;y2<=n;y2++){
if(x1==x2&&y1==y2)continue;
for(ll x3=-n;x3<=n;x3++)for(ll y3=-n;y3<=n;y3++){
if((x3==x1&&y3==y1)||(x3==x2&&y3==y2))continue;
ll cr=(x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);if(cr==0)continue;
ll sx=x1+x2+x3,sy=y1+y2+y3;if(sx||sy)continue;
ll ds=x1*x2+y1*y2+x2*x3+y2*y3+x3*x1+y3*y1;if(ds!=-39)continue;
ans+=llabs(cr);}}}
cout<<ans/2<<"\n";return 0;}
