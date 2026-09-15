#include<bits/stdc++.h>
using namespace std;

#define ll long long

ll mpow(ll a, ll e, ll m) {
    ll r = 1;
    while (e) {
        if (e & 1) r = (__int128)r * a % m;
        a = (__int128)a * a % m;
        e >>= 1;
    }
    return r;
}

ll C(ll n) {
    ll cnt = 0;
    for (ll x = 2; x < n; x++) {
        if (mpow(x, 3, n) == 1) cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N, K;
    cin >> N >> K;
    
    ll ans = 0;
    for (ll n = 1; n <= N; n++) {
        if (C(n) == K) ans += n;
    }
    
    cout << ans << "\n";
    return 0;
}
