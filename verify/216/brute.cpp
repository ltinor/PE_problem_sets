#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: use Miller-Rabin for small N

ll mul_mod(ll a, ll b, ll mod) {
    return (__int128)a * b % mod;
}

ll pow_mod(ll a, ll e, ll mod) {
    ll res = 1;
    a %= mod;
    while (e) {
        if (e & 1) res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return res;
}

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }
    vector<ll> bases = {2, 3, 5, 7, 11, 13, 17};
    for (ll a : bases) {
        if (a >= n) continue;
        ll x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;
    
    // Brute can only handle small N
    if (N > 50000) { cout << "0\n"; return 0; }
    
    ll ans = 0;
    for (int n = 2; n <= N; n++) {
        ll tn = 2LL * n * n - 1;
        if (is_prime(tn)) ans++;
    }
    cout << ans << "\n";
}
