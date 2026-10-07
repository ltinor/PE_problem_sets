#include <bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: enumerate all lenticular holes for small N.
// A, B = centers (lattice), P, Q = intersection points (lattice).
// For each hole: |P-A|=|Q-A|=r1, |P-B|=|Q-B|=r2, lens interior has no lattice point.

int main(int argc, char** argv) {
    ll N = 10;
    if (argc > 1) N = atoll(argv[1]);
    // bound for centers: distance <= N from chord points, chord points within N of centers
    // enumerate centers A in [-N, N]^2

    // offsets with a given squared length
    vector<vector<pair<ll,ll>>> off(N*N + 1);
    for (ll dx = -N; dx <= N; dx++)
        for (ll dy = -N; dy <= N; dy++) {
            ll m = dx*dx + dy*dy;
            if (m >= 1 && m <= N*N) off[m].push_back({dx, dy});
        }

    set<pair<ll,ll>> ans;

    for (ll ax = -N; ax <= N; ax++)
    for (ll ay = -N; ay <= N; ay++) {
        // enumerate P, Q on circle centered A with squared radius m
        for (ll m = 1; m <= N*N; m++) {
            auto &O = off[m];
            int sz = O.size();
            for (int i = 0; i < sz; i++) {
                ll px = ax + O[i].first, py = ay + O[i].second;
                for (int j = i+1; j < sz; j++) {
                    ll qx = ax + O[j].first, qy = ay + O[j].second;
                    // chord u = Q - P
                    ll ux = qx - px, uy = qy - py;
                    // primitive perpendicular v = (-uy/g, ux/g)
                    ll g = std::gcd((unsigned long long)llabs(ux), (unsigned long long)llabs(uy));
                    ll vx = -uy/g, vy = ux/g;
                    // B = A + t*v, t != 0, need |P - B|^2 <= N^2
                    // |P-B|^2 = |(px-ax,py-ay) - t*v|^2 = m - 2t*(O[i].v) + t^2 |v|^2
                    ll vv = vx*vx + vy*vy; // |v|^2
                    ll dot = O[i].first*vx + O[i].second*vy; // O[i] . v
                    // iterate t
                    ll r2sq_max = N*N;
                    // find t range where m - 2 t dot + t^2 vv <= r2sq_max
                    // iterate t: |t|*|v| = |AB| <= r1 + r2 <= 2N, |v|>=1 => |t| <= 2N
                    for (ll t = -2*N; t <= 2*N; t++) {
                        if (t == 0) continue;
                        ll r2sq = m - 2*t*dot + t*t*vv;
                        if (r2sq < 1 || r2sq > r2sq_max) continue;
                        ll bx = ax + t*vx, by = ay + t*vy;
                        // B must be a lattice point (yes, since v integer). B != A.
                        // Empty lens check: no lattice point Y with |Y-A|^2 < m and |Y-B|^2 < r2sq
                        bool empty = true;
                        // candidate Y: within radius sqrt(m) of A
                        ll R = (ll)sqrt((double)m) + 1;
                        for (ll yx = ax - R; yx <= ax + R && empty; yx++)
                        for (ll yy = ay - R; yy <= ay + R && empty; yy++) {
                            ll da = (yx-ax)*(yx-ax) + (yy-ay)*(yy-ay);
                            if (da >= m) continue; // not strictly inside circle A
                            ll db = (yx-bx)*(yx-bx) + (yy-by)*(yy-by);
                            if (db < r2sq) empty = false; // strictly inside both -> interior lattice point
                        }
                        if (empty) {
                            ans.insert({min(m, r2sq), max(m, r2sq)});
                        }
                    }
                }
            }
        }
    }

    cout << ans.size() << "\n";
    return 0;
}
