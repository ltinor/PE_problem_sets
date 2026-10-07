#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll mygcd(ll a, ll b) {
    return b == 0 ? a : mygcd(b, a % b);
}

// Check if a^2 + b^2 + a*b is a perfect square
bool check_120(ll a, ll b, ll &side) {
    ll val = a * a + b * b + a * b;
    ll r = (ll)sqrt((long double)val);
    while ((r + 1) * (r + 1) <= val) r++;
    while (r * r > val) r--;
    if (r * r == val) {
        side = r;
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll M;
    cin >> M;

    // Torricelli triangles: p^2+q^2+pq = a^2, q^2+r^2+qr = b^2, r^2+p^2+rp = c^2
    // where a,b,c are side lengths and p,q,r are distances from Torricelli point.
    // p+q+r is the sum we want.

    // Standard approach: enumerate p, q, find r such that all conditions hold.
    // Use set to collect distinct values of p+q+r.

    unordered_set<ll> sums;

    for (ll p = 1; p <= M; p++) {
        // q from p to M-p (to avoid duplicates, ensure p <= q <= r)
        for (ll q = p; q <= M - p; q++) {
            ll a;
            if (!check_120(p, q, a)) continue;

            // Now we need r such that:
            // q^2 + r^2 + qr = b^2 (square)
            // r^2 + p^2 + rp = c^2 (square)
            // and p+q+r <= M, r >= q

            // From law of cosines: r satisfies quadratic equation
            // For equation q^2+r^2+qr = b^2 and p^2+r^2+pr = c^2:
            // Subtract: (q^2+r^2+qr) - (p^2+r^2+pr) = b^2 - c^2
            // q^2 - p^2 + r(q-p) = b^2 - c^2
            // Not directly helpful.

            // Better: use the parametric form.
            // Known parametrization for 120-degree triangles:
            // If (u,v,w) solves u^2+v^2+uv = w^2,
            // then we can generate all triples via:
            // u = m^2 - n^2, v = 2mn + n^2, w = m^2 + mn + n^2
            // or similar forms.

            // For practical enumeration with M up to 120000,
            // we can brute force r for each (p,q).

            ll max_r = M - p - q;
            if (max_r < q) break;

            for (ll r = q; r <= max_r; r++) {
                ll b, c;
                if (check_120(q, r, b) && check_120(r, p, c)) {
                    ll sum = p + q + r;
                    if (sums.find(sum) == sums.end()) {
                        sums.insert(sum);
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (ll s : sums) ans += s;
    cout << ans << "\n";

    return 0;
}
