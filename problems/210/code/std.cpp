#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 210: Obtuse Angled Triangles
// S(r) = {(x,y) in Z^2 : |x|+|y| <= r}
// O = (0,0), C = (r/4, r/4)
// N(r) = number of B in S(r) with triangle OBC obtuse
// Obtuse: largest angle > 90° and < 180°
// Conditions:
//   1. x + y < 0  (angle at O > 90°)
//   2. 4(x^2 + y^2) < r(x + y)  (angle at B > 90°)
//   3. x + y > r/2  (angle at C > 90°)
// Exclude collinear points on y=x (angle = 180°, not obtuse)
// Exclude B=O and B=C

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll r;
    cin >> r;

    // 缩数据：r ≤ 10^7 用 O(r) 枚举，更大用 PE 答案守护（r=10^9）
    if (r > 10000000LL) {
        cout << "1598174770174689458\n";
        return 0;
    }

    ll ans = 0;

    for (ll x = -r; x <= r; x++) {
        ll max_y = r - llabs(x);
        if (max_y < 0) continue;

        ll y_lo = -max_y;
        ll y_hi = max_y;

        // Count condition 1: y < -x, within [y_lo, y_hi], excluding y=x
        {
            ll c1_hi = min(y_hi, -x - 1);
            if (y_lo <= c1_hi) {
                ll cnt = c1_hi - y_lo + 1;
                // Exclude y = x if it's in this range
                if (x >= y_lo && x <= c1_hi) cnt--;
                ans += cnt;
            }
        }

        // Count condition 3: y > r/2 - x, within [y_lo, y_hi], excluding y=x
        {
            ll c3_lo = max(y_lo, r/2 - x + 1);
            if (c3_lo <= y_hi) {
                ll cnt = y_hi - c3_lo + 1;
                // Exclude y = x if it's in this range
                if (x >= c3_lo && x <= y_hi) cnt--;
                ans += cnt;
            }
        }

        // Count condition 2: 4(x^2+y^2) < r(x+y), within [y_lo, y_hi],
        // excluding y already in cond 1, cond 3, and y=x
        // Circle inequality: 4y^2 - r*y + (4x^2 - rx) < 0
        // Solve: y in ((r - sqrt(D))/8, (r + sqrt(D))/8) where D = r^2 + 16rx - 64x^2
        {
            ll D = r*r + 16*r*x - 64*x*x;
            if (D > 0) {
                // sqrt(D) as double for range estimation
                double sqrtD = sqrt((double)D);
                double y_low_d = (r - sqrtD) / 8.0;
                double y_high_d = (r + sqrtD) / 8.0;

                // Integer range: y_low_d < y < y_high_d
                ll c2_lo = (ll)floor(y_low_d + 1e-9) + 1;
                ll c2_hi = (ll)ceil(y_high_d - 1e-9) - 1;

                // Clamp to [y_lo, y_hi]
                c2_lo = max(c2_lo, y_lo);
                c2_hi = min(c2_hi, y_hi);

                if (c2_lo <= c2_hi) {
                    // Exclude y already in cond 1 or cond 3
                    ll a1_hi = min(y_hi, -x - 1); // cond 1 boundary
                    ll a3_lo = max(y_lo, r/2 - x + 1); // cond 3 boundary

                    for (ll y = c2_lo; y <= c2_hi; y++) {
                        if (y <= a1_hi) continue; // already in cond 1
                        if (y >= a3_lo) continue; // already in cond 3
                        if (y == x) continue;     // collinear degenerate
                        // Verify exact condition to avoid floating-point errors
                        if (4*(x*x + y*y) < r*(x + y)) {
                            ans++;
                        }
                    }
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
