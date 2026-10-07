#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll sum(ll k){
    return k*(k+1)/2;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin>>n;

    ll k3=(n-1)/3;
    ll k5=(n-1)/5;
    ll k15=(n-1)/15;

    ll ans=3*sum(k3)+5*sum(k5)-15*sum(k15);

    cout<<ans<<"\n";
}