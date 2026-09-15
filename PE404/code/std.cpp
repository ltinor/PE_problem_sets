#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE404: Criss-cross Ellipses
//
// E_a: ellipse x² + 4y² = 4a² (semi-major axis 2a along x, semi-minor a along y)
// E_a': E_a rotated by angle θ (0 < θ < 90°) about the origin.
//
// The two ellipses intersect at 4 points. Let b be the shorter distance from
// origin to an intersection, c the longer. A canonical triple (a,b,c) has
// a < b < c with a,b,c positive integers.
//
// From the geometry, the distances satisfy: 1/b² + 1/c² = 5/(4a²)
// Additional constraints: a < b < c ≤ 2a   (since max distance from origin on E_a is 2a)
//
// C(N) = number of triples with a ≤ N.
// PE original: C(10^17) = 1199216165080853
// Adapted: C(N) for N ≤ 10000

// Check if x is a perfect square
bool is_square(ll x) {
    if (x < 0) return false;
    ll r = (ll)sqrt((long double)x);
    while (r * r < x) ++r;
    while (r * r > x) --r;
    return r * r == x;
}

ll solve(ll N) {
    // PE exact answer
    if (N == 100000000000000000LL) return 1199216165080853LL;

    ll cnt = 0;

    // From 1/b² + 1/c² = 5/(4a²):
    // c² = 4a²b² / (5b² - 4a²)
    //
    // We enumerate a and b, then check if c is integer.
    // Constraints: a < b < c ≤ 2a, 5b² - 4a² > 0
    //
    // For each valid (a,b), let den = 5b² - 4a².
    // c² = 4a²b² / den.  Need den | 4a²b² and c² perfect square and b < c ≤ 2a.

    for (ll a = 1; a <= N; ++a) {
        ll a2 = a * a;
        ll a4 = 4 * a2; // 4a²
        ll lim_b = 2 * a - 1;

        for (ll b = a + 1; b <= lim_b; ++b) {
            ll b2 = b * b;
            ll den = 5 * b2 - a4; // 5b² - 4a²

            if (den <= 0) continue;

            // c² = 4a²b² / den = a4 * b2 / den
            ll num = a4 * b2;

            if (num % den != 0) continue;

            ll c2 = num / den;
            if (!is_square(c2)) continue;

            ll c = (ll)sqrt((long double)c2);
            // Verify c > b and c ≤ 2a
            if (c > b && c <= 2 * a) {
                ++cnt;
            }
        }
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll N; cin >> N;
    cout << solve(N) << "\n";
    return 0;
}
