#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE443 brute: same direct computation, for verification of small N

ll my_gcd(ll a, ll b) { return b ? my_gcd(b, a % b) : a; }

ll g_direct(ll N) {
    ll g = 13;
    for (ll n = 5; n <= N; n++) {
        g += my_gcd(n, g);
    }
    return g;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    cout << g_direct(N) << "\n";
}
