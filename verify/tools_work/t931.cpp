#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u128 = __uint128_t;
const ll MOD = 715827883LL;
ll TN;
ll L;
ll t2mod(ll x){ ll a=x%MOD,b=(x+1)%MOD; return (u128)a*b%MOD*((MOD+1)/2)%MOD; }
ll E(ll x, ll p){ ll r=t2mod(x); ll sub=(u128)(p%MOD)*t2mod(x/p)%MOD; return (r-sub+MOD)%MOD; }
int main(){
    cin >> TN; L = (ll)sqrtl((long double)TN);
    while ((L+1)*(L+1) <= TN) L++;
    while (L*L > TN) L--;
    ll sq = L;
    vector<ll> vals;
    for (ll i=1;i<=sq;i++){ vals.push_back(i); vals.push_back(TN/i); }
    sort(vals.begin(), vals.end()); vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = vals.size();
    auto idx=[&](ll v)->int{ return v<=sq ? (int)v-1 : (int)(m-(size_t)(TN/v)); };
    vector<ll> pi(m), sp(m);
    for (int i=0;i<m;i++){ ll v=vals[i]; pi[i]=(v-1)%MOD; sp[i]=(t2mod(v)-1+MOD)%MOD; }
    for (ll p=2;p<=sq;p++){
        if (pi[idx(p)]==pi[idx(p-1)]) continue;
        for (int i=m-1;i>=0;i--){
            ll v=vals[i]; if (v<p*p) break;
            int j=idx(v/p);
            pi[i]=(pi[i]-(pi[j]-pi[idx(p-1)])%MOD+MOD)%MOD;
            ll sub=(u128)(p%MOD)*((sp[j]-sp[idx(p-1)]+MOD)%MOD)%MOD;
            sp[i]=(sp[i]-sub+MOD)%MOD;
        }
    }
    // DEBUG
    cerr << "pi table:"; for (int i=1;i<=12 && i<m;i++) cerr << " pi(" << vals[i] << ")=" << pi[idx(vals[i])]; cerr << endl;
    cerr << "pi(10)=" << pi[idx(10)] << " pi(11)=" << pi[idx(11)] << " pi(100)=" << pi[idx(100)] << endl;
    cerr << "S(10)=" << sp[idx(10)] << " S(11)=" << sp[idx(11)] << " S(100)=" << sp[idx(100)] << endl;
    ll ans=0;
    vector<char> comp(L+1,0); vector<ll> pl;
    for (ll i=2;i<=L;i++){ if(!comp[i]){ pl.push_back(i); for(ll j=i*i;j<=L;j+=i) comp[j]=1; } }
    for (ll p: pl) ans=(ans+(u128)((p-2+MOD)%MOD)*E(TN/p,p))%MOD;
    ll xmax = TN/(L+1);
    for (ll X=1;X<=xmax;X++){
        ll lo = max(TN/(X+1), L), hi = TN/X;
        if (hi <= L) continue;
        ll cnt=(pi[idx(hi)]-pi[idx(lo)]%MOD+MOD)%MOD;
        ll s=(sp[idx(hi)]-sp[idx(lo)]%MOD+MOD)%MOD;
        ll term=(s-2*cnt%MOD+MOD)%MOD;
        ans=(ans+(u128)t2mod(X)*term)%MOD;
    }
    for (ll p: pl){
        u128 pk=(u128)p*p; ll pa1=p;
        while (pk <= (u128)TN){
            ll c=((u128)(p-1)%MOD*pa1%MOD - 1 + MOD)%MOD;
            ans=(ans+(u128)c*E(TN/(ll)pk,p))%MOD;
            pk*=p; pa1=(u128)pa1*p%MOD;
        }
    }
    cout << ans << endl;
}
