#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: compute C(N,K) directly and factorize
// Only works for very small N (e.g., N <= 30)
// Used for verification against std on small inputs

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll binom_brute(ll N, ll K) {
    if (K > N - K) K = N - K;
    vector<ll> num, den;
    for (ll i = 0; i < K; i++) {
        num.push_back(N - i);
        den.push_back(i + 1);
    }
    for (ll j = 0; j < (ll)den.size(); j++) {
        for (ll i = 0; i < (ll)num.size(); i++) {
            ll g = gcd(num[i], den[j]);
            if (g > 1) {
                num[i] /= g;
                den[j] /= g;
                if (den[j] == 1) break;
            }
        }
    }
    ll res = 1;
    for (ll x : num) res *= x;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, K;
    cin >> N >> K;

    ll val = binom_brute(N, K);

    // Factorize
    ll ans = 0;
    ll tmp = val;
    for (ll p = 2; p * p <= tmp; p++) {
        while (tmp % p == 0) {
            ans += p;
            tmp /= p;
        }
    }
    if (tmp > 1) ans += tmp;

    cout << ans << "\n";
    return 0;
}
