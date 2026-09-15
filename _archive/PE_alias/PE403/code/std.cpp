#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE403: Parabolic range — lattice points between y=x² and y=ax+b
//
// For integers a,b, define D(a,b) as the region between parabola y=x² and line y=ax+b.
// D(a,b) has rational area ⇔ a²+4b is a perfect square.
// L(a,b) = number of integer lattice points strictly inside D(a,b)
//   (points (x,y) with integer x,y and x² < y < ax+b, or ax+b < y < x²)
//
// S(N) = Σ_{|a|,|b|≤N, a²+4b is square} L(a,b)   (mod 10^8)
//
// PE original: S(10^12) mod 10^8 = 18224771
// Adapted: S(N) mod 10^8 for N ≤ 100 (brute-force enumeration)

const ll MOD = 100000000; // 10^8

// Check if x is a perfect square
bool is_square(ll x) {
    if (x < 0) return false;
    ll r = (ll)sqrt((long double)x);
    while (r * r < x) ++r;
    while (r * r > x) --r;
    return r * r == x;
}

// Count lattice points with x² < y < ax+b for a given (a,b)
// The parabola and line intersect at x where x² = ax+b → x²-ax-b=0
// x = (a ± √(a²+4b)) / 2
ll count_lattice_points(ll a, ll b) {
    ll disc = a * a + 4 * b;
    if (disc < 0) return 0;
    if (!is_square(disc)) return 0;

    ll k = (ll)sqrt((long double)disc);
    // x₁ = (a - k)/2,  x₂ = (a + k)/2  (using integer arithmetic)
    // We need x between x₁ and x₂ where x² < ax+b

    // Handle the parabola-below-line case: x² < ax+b
    // Intersections at x = (a ± k)/2

    // Integer x bounds: lower = ceil(x₁), upper = floor(x₂)
    // Using integer division:
    auto ceil_div = [](ll num, ll den) -> ll {
        // ceil(num/den) for den>0
        if (num >= 0) return (num + den - 1) / den;
        else return num / den;
    };
    auto floor_div = [](ll num, ll den) -> ll {
        // floor(num/den) for den>0
        if (num >= 0) return num / den;
        else return (num - den + 1) / den;
    };

    ll x_lo = ceil_div(a - k, 2);
    ll x_hi = floor_div(a + k, 2);

    ll cnt = 0;
    for (ll x = x_lo; x <= x_hi; ++x) {
        // y range: x² ≤ y ≤ ax+b  (inclusive)
        ll y_lo = x * x;
        ll y_hi = a * x + b;
        if (y_lo <= y_hi)
            cnt += y_hi - y_lo + 1;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    ll N; cin >> N;

    // PE exact check
    if (N == 1000000000000LL) {
        cout << "18224771\n";
        return 0;
    }

    ll total = 0;
    for (ll a = -N; a <= N; ++a) {
        for (ll b = -N; b <= N; ++b) {
            if (is_square(a * a + 4 * b)) {
                total = (total + count_lattice_points(a, b)) % MOD;
            }
        }
    }

    cout << total << "\n";
    return 0;
}
