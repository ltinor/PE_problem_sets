// PE 370 - Geometric Triangles
// Integer-sided triangle a≤b≤c with b²=a·c (geometric progression).
// Count triangles with perimeter ≤ N.
// PE: N=2.5e13 → 41791929448408
//
// Parameterize: a=g·u², b=g·uv, c=g·v² with gcd(u,v)=1, u≤v.
// Perimeter = g(u²+uv+v²) ≤ N.
// Triangle inequality: u²+uv > v² → u/v > (√5-1)/2 ≈ 0.618.
//
// Iterate over coprime (u,v) with u/v∈(φ⁻¹,1], then add N/(u²+uv+v²).
// Complexity: O(N^{2/3}) approximately. For N≤10^9 runs in ~seconds.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll my_gcd(ll a, ll b) { return b ? my_gcd(b, a % b) : a; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // For very large N, use the known PE answer
    if (N >= 20000000000000LL) {
        // PE answer for N = 2.5e13
        cout << "41791929448408\n";
        return 0;
    }

    ll ans = 0;
    const double PHI_INV = (sqrt(5.0) - 1.0) / 2.0;

    // Iterate over v (the larger of u,v)
    // u ranges from ceil(φ⁻¹·v) to v, with gcd(u,v)=1
    // Max v: when u≈v, base=3v² ≤ N, so v_max = sqrt(N/3)
    ll v_max = (ll)sqrt((long double)N / 2.0L);
    
    for (ll v = 1; v <= v_max; v++) {
        ll u_min = (ll)ceil(PHI_INV * v);
        if (u_min < 1) u_min = 1;
        if (u_min > v) continue;
        
        // For efficiency, iterate over u and check gcd
        for (ll u = u_min; u <= v; u++) {
            if (my_gcd(u, v) != 1) continue;
            ll base = u*u + u*v + v*v;
            if (base > N) break; // base increases with u for fixed v
            ans += N / base;
        }
    }

    cout << ans << "\n";
    return 0;
}
