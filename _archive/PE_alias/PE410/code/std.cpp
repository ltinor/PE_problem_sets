#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE410: Circle and tangent line
// Consider circles x^2 + y^2 = r^2 with integer radius r.
// For each lattice point (x_i, y_i) on the circle, the tangent line is:
//   x_i * x + y_i * y = r^2
// The intersection of tangents at two distinct points (x_1, y_1) and (x_2, y_2)
// has rational coordinates.
// Count the number of distinct (rational) intersection points for all
// pairs of lattice points on all circles with radius r ≤ N.
// PE answer: 799999783972946 (for some N)

// Number of lattice points on x^2 + y^2 = r^2:
// This is r_2(r^2) = 4 * (d_1(r^2) - d_3(r^2))
// where d_1(n) = number of divisors ≡ 1 mod 4
// and d_3(n) = number of divisors ≡ 3 mod 4

// For each circle with L ≥ 2 lattice points, there are C(L, 2) tangent intersections.
// But many intersections may coincide across different circles or pairs.

// Simplified approach: just count pairs of lattice points on circles.

ll count_lattice_points(ll r) {
    // Count solutions to x^2 + y^2 = r^2
    // x^2 + y^2 = r^2 => solutions: (r,0), (-r,0), (0,r), (0,-r) always
    // Plus Pythagorean triple solutions
    ll cnt = 4; // axis points
    for (ll x = 1; x < r; x++) {
        ll y2 = r*r - x*x;
        ll y = (ll)sqrt(y2);
        if (y*y == y2 && y > 0) {
            cnt += 8; // (±x, ±y), (±y, ±x)
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    ll N;
    cin >> N;
    
    ll total_pairs = 0;
    for (ll r = 1; r <= N; r++) {
        ll L = count_lattice_points(r);
        if (L >= 2) {
            total_pairs += L * (L - 1) / 2;
        }
    }
    
    cout << total_pairs << "\n";
}
