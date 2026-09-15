#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll MOD=1000000000;
void dfs(int sum,ll cur,ll&total){if(sum==0){total=(total+cur)%MOD;return;}for(int d=1;d<=9&&d<=sum;d++)dfs(sum-d,(cur*10+d)%MOD,total);}
int main(){int n;cin>>n;ll t=0;dfs(n,0,t);cout<<t<<"\n";return 0;}
