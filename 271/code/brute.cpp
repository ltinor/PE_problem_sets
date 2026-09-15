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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    ll ans = 0;
    for (ll x = 2; x < N; x++) {
        if (mpow(x, 3, N) == 1) ans += x;
    }
    
    cout << ans << "\n";
    return 0;
}
