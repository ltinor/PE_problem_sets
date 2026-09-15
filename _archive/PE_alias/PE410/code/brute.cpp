#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll count_lp(ll r){
    ll cnt=4;
    for(ll x=1;x<r;x++){
        ll y2=r*r-x*x, y=(ll)sqrt(y2);
        if(y*y==y2&&y>0) cnt+=8;
    }
    return cnt;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    ll N;cin>>N;
    ll total=0;
    for(ll r=1;r<=N;r++){
        ll L=count_lp(r);
        if(L>=2) total+=L*(L-1)/2;
    }
    cout<<total<<"\n";
}
