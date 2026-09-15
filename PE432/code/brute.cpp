#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE432 brute: direct φ computation and sum

vector<ll> compute_phis(ll limit) {
    vector<ll> phi(limit + 1);
    iota(phi.begin(), phi.end(), 0);
    for (ll p = 2; p <= limit; p++) {
        if (phi[p] == p) {
            for (ll k = p; k <= limit; k += p) {
                phi[k] -= phi[k] / p;
            }
        }
    }
    return phi;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    ll n, m; cin >> n >> m;
    
    auto phi = compute_phis(n * m);
    ll ans = 0;
    for (ll i = 1; i <= m; i++) {
        ans += phi[n * i];
    }
    cout << ans << "\n";
}
