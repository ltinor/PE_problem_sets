#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Ellipse: center (cx, cy) = (3000, 1500)
// a = 7500, b = 2500*sqrt(5)
// In local coords: x^2/a^2 + y^2/b^2 = 1
// Angle between tangents from (x0,y0):
// tan^2(theta/2) = a^2*b^2 / (a^2*y0^2 + b^2*x0^2 - a^2*b^2)
// Condition: theta > D degrees
// => tan^2(theta/2) > tan^2(D/2)
// => a^2*y0^2 + b^2*x0^2 < a^2*b^2 * (1 + 1/tan^2(D/2))

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;
    cin >> D;

    // Ellipse parameters
    const double cx = 3000.0, cy = 1500.0;
    const double a = 7500.0;
    const double b = 2500.0 * sqrt(5.0); // ≈ 5590.17
    const double a2 = a * a;
    const double b2 = b * b;
    const double a2b2 = a2 * b2;

    // tan^2(D/2 degrees)
    double half = D * M_PI / 360.0;
    double t = tan(half);
    double t2 = t * t;

    // Boundary: a^2*y'^2 + b^2*x'^2 < a^2*b^2 * (1 + 1/t2)
    // => x'^2/(a^2*(1+1/t2)) + y'^2/(b^2*(1+1/t2)) < 1
    double factor = 1.0 + 1.0 / t2;
    double bound_a = a * sqrt(factor);
    double bound_b = b * sqrt(factor);

    // Bounding box in global coords
    ll x_min = (ll)ceil(cx - bound_a);
    ll x_max = (ll)floor(cx + bound_a);
    ll y_min = (ll)ceil(cy - bound_b);
    ll y_max = (ll)floor(cy + bound_b);

    ll ans = 0;

    for (ll y = y_min; y <= y_max; y++) {
        double dy = y - cy;
        double dy2 = dy * dy;

        // Pre-compute x bounds for this y
        // Condition 1: outside original ellipse
        // x'^2/a^2 + y'^2/b^2 > 1 => x'^2 > a^2*(1 - y'^2/b^2)
        double orig_inner = a2 * (1.0 - dy2 / b2);
        double orig_x_min, orig_x_max;

        if (orig_inner < 0) {
            // All x are outside the original ellipse at this y
            orig_x_min = -1e18;
            orig_x_max = 1e18;
        } else {
            double orig_sqrt = sqrt(orig_inner);
            orig_x_min = -orig_sqrt;
            orig_x_max = orig_sqrt;
        }

        // Condition 2: inside boundary ellipse
        // a^2*y'^2 + b^2*x'^2 < a^2*b^2*(1+1/t2)
        double rhs = a2b2 * factor;
        double lhs_y = a2 * dy2;
        double bound_inner = (rhs - lhs_y) / b2;

        if (bound_inner <= 0) continue; // no x satisfies

        double bound_sqrt = sqrt(bound_inner);
        double bound_x_min = -bound_sqrt;
        double bound_x_max = bound_sqrt;

        // Valid x: outside original AND inside boundary
        // x' in (bound_x_min, bound_x_max) but NOT in [orig_x_min, orig_x_max]
        // So: (bound_x_min, orig_x_min) ∪ (orig_x_max, bound_x_max)

        // Global x ranges
        // Range 1: x in (cx + bound_x_min, cx + orig_x_min)
        if (bound_x_min < orig_x_min) {
            ll r1_l = (ll)ceil(cx + bound_x_min + 1e-9);
            ll r1_r = (ll)floor(cx + orig_x_min - 1e-9);
            r1_l = max(r1_l, x_min);
            r1_r = min(r1_r, x_max);
            if (r1_l <= r1_r) ans += r1_r - r1_l + 1;
        }

        // Range 2: x in (cx + orig_x_max, cx + bound_x_max)
        if (orig_x_max < bound_x_max) {
            ll r2_l = (ll)ceil(cx + orig_x_max + 1e-9);
            ll r2_r = (ll)floor(cx + bound_x_max - 1e-9);
            r2_l = max(r2_l, x_min);
            r2_r = min(r2_r, x_max);
            if (r2_l <= r2_r) ans += r2_r - r2_l + 1;
        }
    }

    cout << ans << "\n";
    return 0;
}
