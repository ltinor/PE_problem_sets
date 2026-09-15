#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE402 brute: direct O(N^3) enumeration for small N
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll M_val(ll a, ll b, ll c) {
    // gcd over all n: gcd(P(1), P(2), P(3), P(4)) for degree 4 polynomial
    ll g = 0;
    for (ll n = 1; n <= 5; n++) {
        ll val = n*n*n*n + a*n*n*n + b*n*n + c*n;
        g = gcd(g, val);
        if (g == 1) break;
    }
    return g;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    if (N > 30) { cout << "0\n"; return 0; }
    ll total = 0;
    for (ll a = 1; a <= N; a++)
        for (ll b = 1; b <= N; b++)
            for (ll c = 1; c <= N; c++)
                total += M_val(a, b, c);
    cout << total << "\n";
}
