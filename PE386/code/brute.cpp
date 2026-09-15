#include<bits/stdc++.h>
using namespace std;
#define ll long long
// Brute: N(n) = omega(n) (number of distinct prime factors)
int main() {
    ll n; cin >> n;
    vector<ll> omega(n+1, 0);
    for (ll i=2; i<=n; i++) {
        if (omega[i]==0) {
            for (ll j=i; j<=n; j+=i) omega[j]++;
        }
    }
    ll ans=0;
    for (ll i=1; i<=n; i++) ans += omega[i];
    cout << ans << "\n";
}
