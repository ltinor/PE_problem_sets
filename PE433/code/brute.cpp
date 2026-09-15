#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE433 brute: compute S(N) by enumerating all pairs

ll E(ll x, ll y) {
    if (y > x) swap(x, y);
    ll steps = 0;
    while (y > 0) {
        steps++;
        ll t = x % y;
        x = y;
        y = t;
    }
    return steps;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    ll N; cin >> N;
    
    ll ans = 0;
    for (ll x = 1; x <= N; x++) {
        for (ll y = 1; y <= N; y++) {
            ans += E(x, y);
        }
    }
    cout << ans << "\n";
}
