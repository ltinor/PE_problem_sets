#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Generate all Pythagorean triples (w, leg, hyp) where hyp < LIMIT
// w is one leg, leg is the other leg, hyp is hypotenuse
// Store by w: for each w, list of (leg, hyp) pairs
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N; // x < y < N, count triplets

    // For each w, store legs
    vector<vector<pair<ll,ll>>> legs_by_w(N);

    // Generate primitive Pythagorean triples
    for (ll m = 2; m * m < N; m++) {
        for (ll n = 1; n < m; n++) {
            if ((m - n) % 2 == 0) continue;
            if (gcd(m, n) != 1) continue;

            ll w0 = m*m - n*n;
            ll a0 = 2*m*n;
            ll x0 = m*m + n*n;

            // Scale by k
            for (ll k = 1; k * x0 < N; k++) {
                ll w = k * w0;
                ll a = k * a0;
                ll x = k * x0;
                if (w < N && a < N) {
                    legs_by_w[w].push_back({a, x});
                }
            }

            // Also the swapped version: w = 2mn, a = m²-n²
            w0 = 2*m*n;
            a0 = m*m - n*n;
            for (ll k = 1; k * x0 < N; k++) {
                ll w = k * w0;
                ll a = k * a0;
                ll x = k * x0;
                if (w < N && a < N) {
                    legs_by_w[w].push_back({a, x});
                }
            }
        }
    }

    ll ans = 0;
    for (ll w = 1; w < N; w++) {
        auto& legs = legs_by_w[w];
        int sz = legs.size();
        if (sz < 2) continue;

        // For each pair of legs (a, x) and (b, y) with x < y
        for (int i = 0; i < sz; i++) {
            ll a = legs[i].first, x = legs[i].second;
            for (int j = 0; j < sz; j++) {
                if (i == j) continue;
                ll b = legs[j].first, y = legs[j].second;
                if (x >= y) continue; // ensure x < y

                // Check if h = a*b/(a+b) is integer
                if ((a * b) % (a + b) == 0) {
                    ans++;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
