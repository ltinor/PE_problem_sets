#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 282: Ackermann function A(m,n) mod M
// For adaptation: given m (0≤m≤3), n (0≤n≤1e9), M (1≤M≤1e9), compute A(m,n) mod M
// PE answer: sum_{n=0}^{6} A(n,n) mod 14^8 = 1098988351

ll mod_pow(ll a, ll e, ll mod) {
    if (mod == 1) return 0;
    ll res = 1;
    a %= mod;
    while (e) {
        if (e & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        e >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m;
    ll n, M;
    cin >> m >> n >> M;
    
    ll ans;
    if (m == 0) {
        ans = (n + 1) % M;
    } else if (m == 1) {
        ans = (n + 2) % M;
    } else if (m == 2) {
        ans = (2 * n + 3) % M;
    } else if (m == 3) {
        // A(3,n) = 2^(n+3) - 3
        ll pow2 = mod_pow(2, n + 3, M);
        ans = (pow2 - 3) % M;
        if (ans < 0) ans += M;
    } else {
        ans = 0; // m≥4 not supported in this adaptation
    }
    
    cout << ans << "\n";
}
