#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Miller-Rabin deterministic for 64-bit
ll mul(ll a, ll b, ll mod) {
    return (__int128)a * b % mod;
}

ll mpow(ll a, ll e, ll mod) {
    ll r = 1;
    while (e) {
        if (e & 1) r = mul(r, a, mod);
        a = mul(a, a, mod);
        e >>= 1;
    }
    return r;
}

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d >>= 1; s++; }
    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (a >= n) continue;
        ll x = mpow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (int r = 1; r < s; r++) {
            x = mul(x, x, n);
            if (x == n - 1) { ok = true; break; }
        }
        if (!ok) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;
    for (ll n = 1; ; n++) {
        ll p = 2 * n * n + 2 * n + 1;
        if (p >= N) break;
        if (is_prime(p)) ans++;
    }

    cout << ans << "\n";
    return 0;
}
