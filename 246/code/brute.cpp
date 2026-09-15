#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: explicit angle computation for small grids
// For small D values, the bounding ellipse is small enough
// that brute force point-by-point checking is feasible.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;
    cin >> D;

    const double cx = 3000.0, cy = 1500.0;
    const double a = 7500.0;
    const double b = 2500.0 * sqrt(5.0);
    const double a2 = a * a;
    const double b2 = b * b;

    double half = D * M_PI / 360.0;
    double t2 = tan(half) * tan(half);

    double factor = 1.0 + 1.0 / t2;
    double bound_a = a * sqrt(factor);
    double bound_b = b * sqrt(factor);

    ll x_min = (ll)ceil(cx - bound_a);
    ll x_max = (ll)floor(cx + bound_a);
    ll y_min = (ll)ceil(cy - bound_b);
    ll y_max = (ll)floor(cy + bound_b);

    ll ans = 0;

    for (ll y = y_min; y <= y_max; y++) {
        for (ll x = x_min; x <= x_max; x++) {
            double dx = x - cx;
            double dy = y - cy;

            // Check outside original ellipse
            double orig = dx*dx/a2 + dy*dy/b2;
            if (orig <= 1.0) continue;

            // Check angle condition
            double lhs = a2*dy*dy + b2*dx*dx;
            if (lhs < a2*b2 * factor) {
                ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
