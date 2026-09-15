#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE468 brute: direct computation of F(n) for tiny n
ll S_B(ll x, int B) {
    ll res = 1;
    for (ll p = 2; p <= B; p++) {
        if (p * p > x && p > B) break;
        while (x % p == 0) {
            res *= p;
            x /= p;
        }
    }
    return res;
}

ll C(int n, int r) {
    if (r < 0 || r > n) return 0;
    r = min(r, n-r);
    ll res = 1;
    for (int i = 1; i <= r; i++) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

int main() {
    int n; cin >> n;
    ll ans = 0;
    for (int r = 0; r <= n; r++) {
        ll val = C(n, r);
        for (int B = 1; B <= n; B++) {
            ans += S_B(val, B);
        }
    }
    cout << ans << "\n";
}
