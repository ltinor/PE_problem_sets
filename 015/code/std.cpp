#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MOD = 1e9 + 7;

ll modpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll C(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    ll num = 1, den = 1;
    for (ll i = 0; i < k; i++) {
        num = num * (n - i) % MOD;
        den = den * (i + 1) % MOD;
    }
    return num * modpow(den, MOD - 2) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        ll n, m;
        cin >> n >> m;
        cout << C(n + m, m) << "\n";
    }
}
