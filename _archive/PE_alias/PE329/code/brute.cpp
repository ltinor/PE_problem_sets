#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE329 brute: same algorithm as std but verifies correctness

typedef __int128 i128;
i128 gcd(i128 a,i128 b){while(b){i128 t=b;b=a%b;a=t;}return a;}

vector<bool> sieve(ll n){
    vector<bool> p(n+1,true); p[0]=p[1]=false;
    for(ll i=2;i*i<=n;i++) if(p[i]) for(ll j=i*i;j<=n;j+=i) p[j]=false;
    return p;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll N; string S; cin>>N>>S;
    ll T=S.size();
    auto isp=sieve(N);
    vector<vector<i128>> dp(N+1,vector<i128>(T+1,0));
    for(ll pos=1;pos<=N;pos++) dp[pos][0]=1;
    for(ll t=0;t<T;t++){
        char target=S[t];
        for(ll pos=1;pos<=N;pos++){
            if(dp[pos][t]==0) continue;
            i128 croak= (target=='P') ? (isp[pos]?2:1) : (isp[pos]?1:2);
            vector<ll> nxt;
            if(pos==1) nxt={2}; else if(pos==N) nxt={(ll)(N-1)}; else nxt={(ll)(pos-1),(ll)(pos+1)};
            for(ll np:nxt){
                i128 jd=(nxt.size()==1)?1:2;
                dp[np][t+1]+=dp[pos][t]*croak*2/jd;
            }
        }
    }
    i128 num=0; for(ll pos=1;pos<=N;pos++) num+=dp[pos][T];
    i128 den=N; for(ll t=0;t<T;t++) den*=6;
    i128 g=gcd(num,den); num/=g; den/=g;
    auto pr=[](i128 x){if(!x){cout<<"0";return;}string s;while(x){s=char('0'+(int)(x%10))+s;x/=10;}cout<<s;};
    pr(num); cout<<"/"; pr(den); cout<<"\n";
}
