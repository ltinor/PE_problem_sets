#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Simple brute: compute S(p) for small primes
ll modpow(ll a, ll b, ll m) {
    ll r = 1;
    while (b) { if (b&1) r=r*a%m; a=a*a%m; b>>=1; }
    return r;
}

int main() {
    ll n;
    cin >> n;
    ll ans = 0;
    vector<bool> isp(n+1, true);
    isp[0]=isp[1]=false;
    for (ll i=2; i*i<=n; i++)
        if (isp[i])
            for (ll j=i*i; j<=n; j+=i) isp[j]=false;

    for (ll p=5; p<n; p++) {
        if (!isp[p]) continue;
        ll f = 1;
        for (ll k=1; k<=5; k++) {
            ll x = 1;
            for (ll j=2; j<=p-k; j++) x = x*j % p;
            f = (f + x) % p;
        }
        ans += f;
    }
    cout << ans << "\n";
}
