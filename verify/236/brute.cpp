#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 236: Luxury Hampers - brute
// For small test cases, enumerate all possible (x_i, y_i) for all products
// and check both conditions directly

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<ll> a(5), b(5);
    for (int i = 0; i < 5; i++) cin >> a[i] >> b[i];

    ll sum_a = 0, sum_b = 0;
    for (int i = 0; i < 5; i++) { sum_a += a[i]; sum_b += b[i]; }

    // Brute force over small ranges only
    // Check all possible (x_i, y_i) combinations directly
    // Only works for tiny inputs (a_i, b_i <= 10)

    struct State { ll x[5], y[5]; };
    vector<pair<ll,ll>> valid;

    // Enumerate possible m from product 0
    for (ll x0 = 1; x0 <= a[0]; x0++) {
        for (ll y0 = 1; y0 <= b[0]; y0++) {
            // m = y0*a0/(x0*b0)
            if (y0 * a[0] <= x0 * b[0]) continue; // m <= 1
            ll p = y0 * a[0];
            ll q_val = x0 * b[0];
            ll g = std::gcd(p, q_val);
            p /= g; q_val /= g;

            // Check other products have matching ratios
            bool ok = true;
            ll xi[5] = {}, yi[5] = {};
            xi[0] = x0; yi[0] = y0;

            for (int i = 1; i < 5 && ok; i++) {
                // Need yi/xi = p*b_i/(q_val*a_i)
                // yi * a_i * q_val = xi * b_i * p
                ok = false;
                for (ll x = 1; x <= a[i] && !ok; x++) {
                    for (ll y = 1; y <= b[i] && !ok; y++) {
                        if (y * a[i] * q_val == x * b[i] * p) {
                            xi[i] = x; yi[i] = y;
                            ok = true;
                        }
                    }
                }
            }
            if (!ok) continue;

            // Check overall condition
            ll sx = 0, sy = 0;
            for (int i = 0; i < 5; i++) { sx += xi[i]; sy += yi[i]; }
            if ((__int128)sx * sum_b * q_val == (__int128)sy * sum_a * p) {
                ll g2 = std::gcd(p, q_val);
                valid.push_back({p/g2, q_val/g2});
            }
        }
    }

    sort(valid.begin(), valid.end(), [](auto& x, auto& y) {
        return (__int128)x.first * y.second > (__int128)y.first * x.second;
    });

    if (!valid.empty()) {
        cout << valid[0].first << "/" << valid[0].second << "\n";
    }
    return 0;
}
