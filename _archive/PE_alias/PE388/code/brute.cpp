#include<bits/stdc++.h>
using namespace std;
#define ll long long
// Brute: D(N) counts distinct direction vectors from (0,0,0) to (a,b,c)
// = sum over gcd triples. Use inclusion-exclusion.
int main() {
    ll N; cin >> N;
    ll ans = 0;
    vector<ll> mu(N+1, 1);
    vector<bool> isp(N+1, true);
    for (ll i=2; i<=N; i++) {
        if (isp[i]) {
            for (ll j=i; j<=N; j+=i) {
                if (j%(i*i)==0) mu[j]=0;
                else mu[j]=-mu[j];
                isp[j] = (j==i);
            }
        }
    }
    for (ll d=1; d<=N; d++) {
        if (mu[d]==0) continue;
        ll k = N/d;
        ll cnt = (k+1)*(k+1)*(k+1) - 1; // (k+1)^3 points minus origin
        ans += mu[d] * cnt;
    }
    cout << ans << "\n";
}
