#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Project Euler 295 - Lenticular holes (reduced data, real algorithm).
//
// Characterization (derived):
// Translate so one center A = (0,0). Let u=(ux,uy) be the primitive direction of
// the line through the two centers (B = lambda*u, lambda in Z\{0}), and
// n=(uy,-ux) the perpendicular primitive vector. Write a lattice point as
// X = x*u + y*n (a similarity with factor |u|). The two intersection points are
// P=(alpha,beta), Q=(alpha,-beta).
//
// For P,Q to be lattice points (with |u|^2 = ux^2+uy^2):
//   * |u|^2 odd  -> alpha,beta in Z; then (alpha,0) is a lattice point strictly
//                    inside the lens, so no empty hole exists.
//   * |u|^2 even -> alpha,beta both in Z or both in Z+1/2. An empty lens forces
//                    alpha in Z+1/2 and beta = +-1/2.
// Hence only u with both coordinates odd contribute. With alpha=k+1/2 (k in Z),
// beta=+-1/2, j = k-lambda:
//   r1^2 = M*(2k^2+2k+1),  r2^2 = M*(2j^2+2j+1),  M = |u|^2/2.
//
// A candidate is valid iff the lens (intersection of the two disks) contains no
// lattice point X in Z^2 with |X|^2 < r1^2 and |X-B|^2 < r2^2. This emptiness is
// checked by direct (bounded) enumeration, which is fine for the reduced N range.
//
// L(N) = number of distinct (min(r1^2,r2^2), max(r1^2,r2^2)) with max <= N^2.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;
    ll N2 = N * N;

    set<pair<ll, ll>> ans;

    for (ll ux = 1; ux <= 2 * N; ux += 2) {
        for (ll uy = 1; uy <= 2 * N; uy += 2) {
            if (std::gcd(ux, uy) != 1) continue;
            ll u2 = ux * ux + uy * uy; // |u|^2 (== 2 mod 4)
            if (u2 > 4 * N2) break;
            ll M = u2 / 2;

            ll lim = N2 / M;
            ll kmax = 0;
            while (2 * (kmax + 1) * (kmax + 1) + 2 * (kmax + 1) + 1 <= lim)
                kmax++;

            for (ll k = -kmax - 1; k <= kmax; k++) {
                ll s1 = M * (2 * k * k + 2 * k + 1);
                if (s1 > N2) continue;
                ll r1 = (ll)sqrt((double)s1);
                while (r1 * r1 < s1) r1++;
                while (r1 * r1 > s1) r1--;

                for (ll j = -kmax - 1; j <= kmax; j++) {
                    ll s2 = M * (2 * j * j + 2 * j + 1);
                    if (s2 > N2) continue;
                    ll lambda = k - j;
                    if (lambda == 0) continue;
                    ll bx = lambda * ux, by = lambda * uy;

                    // emptiness check over Z^2 in the bounding box of disk A
                    bool empty = true;
                    for (ll Xx = -r1; Xx <= r1 && empty; Xx++) {
                        ll rem = s1 - Xx * Xx;
                        if (rem < 0) continue;
                        ll yb = (ll)sqrt((double)rem);
                        for (ll Xy = -yb; Xy <= yb && empty; Xy++) {
                            if (Xx * Xx + Xy * Xy >= s1) continue;
                            ll dx = Xx - bx, dy = Xy - by;
                            if (dx * dx + dy * dy < s2) empty = false;
                        }
                    }

                    if (empty) {
                        ll lo = min(s1, s2);
                        ll hi = max(s1, s2);
                        if (hi <= N2) ans.insert({lo, hi});
                    }
                }
            }
        }
    }

    cout << ans.size() << "\n";
    return 0;
}
