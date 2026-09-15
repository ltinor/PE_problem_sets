#include<bits/stdc++.h>
using namespace std;
using ll=long long;
ll v5(ll n){ll c=0;while(n){c+=n/5;n/=5;}return c;}
int main(){ll n;cin>>n;ll a=0;for(ll i=1;i<=n;i++){if(v5(2*i-1)<2*v5(i))a++;}cout<<a<<"\n";return 0;}
