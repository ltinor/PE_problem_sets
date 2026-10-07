#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll modpow(ll a, ll e, ll mod){
    ll r=1;
    while(e){
        if(e&1) r=(__int128)r*a%mod;
        a=(__int128)a*a%mod;
        e>>=1;
    }
    return r;
}

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}

int main(){
    ll G,L,S,MOD;
    cin>>G>>L>>S>>MOD;

    ll cnt=0;
    // brute force: for small S
    if(S==1){
        for(ll a=G;a<=L;a++)
            if(a%G==0) cnt++;
    }else if(S==2){
        for(ll a=G;a<=L;a++){
            if(a%G!=0) continue;
            for(ll b=G;b<=L;b++){
                if(b%G!=0) continue;
                ll l=a/gcd(a,b)*b;
                if(l<=L) cnt++;
            }
        }
    }else if(S==3){
        for(ll a=G;a<=L;a++){
            if(a%G!=0) continue;
            for(ll b=G;b<=L;b++){
                if(b%G!=0) continue;
                ll lab=a/gcd(a,b)*b;
                for(ll c=G;c<=L;c++){
                    if(c%G!=0) continue;
                    ll l=lab/gcd(lab,c)*c;
                    if(l<=L) cnt++;
                }
            }
        }
    }
    cout<<cnt%MOD<<"\n";
}
