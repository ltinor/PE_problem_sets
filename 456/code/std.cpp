#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 456: Triangles containing the origin II
// C(n) = number of triangles with vertices in P_n containing origin in INTERIOR
//
// Approach:
// 1. Count all triangles NOT in an OPEN half-plane: total - non_contain_open
// 2. Subtract triangles where origin is on BOUNDARY (span = pi)
//    These occur when two points are opposite (angle diff = pi) and the
//    third point is between them. The origin lies on the edge connecting
//    the opposite pair.
//
// Formula: C(n) = C(m,3) - sum_i C(cnt_i,2) - boundary
// where cnt_i = points strictly within pi CCW of point i
// boundary = sum_i (opp_cnt[i] * cnt_i)
// opp_cnt[i] = number of points opposite to point i (cross=0, dot<0)

struct Point {
    ll x, y;
};

int quad(const Point &p) {
    if (p.x > 0 && p.y >= 0) return 0;
    if (p.x <= 0 && p.y > 0) return 1;
    if (p.x < 0 && p.y <= 0) return 2;
    return 3;
}

ll cross(const Point &p1, const Point &p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

ll dot(const Point &p1, const Point &p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

bool angle_less(const Point &p1, const Point &p2) {
    int q1 = quad(p1), q2 = quad(p2);
    if (q1 != q2) return q1 < q2;
    ll c = cross(p1, p2);
    if (c != 0) return c > 0;
    return dot(p1, p1) < dot(p2, p2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    const ll MOD_X = 32323, MOD_Y = 30103;
    const ll MUL_X = 1248, MUL_Y = 8421;
    const ll SUB_X = 16161, SUB_Y = 15051;

    vector<Point> pts;
    pts.reserve(n);

    ll px = 1, py = 1;
    for (ll i = 1; i <= n; i++) {
        px = (px * MUL_X) % MOD_X;
        py = (py * MUL_Y) % MOD_Y;
        ll x = px - SUB_X;
        ll y = py - SUB_Y;
        if (x == 0 && y == 0) continue;
        pts.push_back({x, y});
    }

    ll m = (ll)pts.size();
    if (m < 3) { cout << "0\n"; return 0; }

    // Build direction map to count opposite points
    map<pair<ll, ll>, ll> dir_cnt;
    for (const auto &p : pts) {
        ll x = p.x, y = p.y;
        if (x == 0 && y == 0) continue;
        ll g = gcd(abs(x), abs(y));
        dir_cnt[{x / g, y / g}]++;
    }

    // Sort by angle
    sort(pts.begin(), pts.end(), angle_less);

    // Build arrays for direction lookup
    vector<pair<ll, ll>> point_dir(m);
    vector<ll> opp_cnt(m, 0);
    for (ll i = 0; i < m; i++) {
        ll x = pts[i].x, y = pts[i].y;
        ll g = gcd(abs(x), abs(y));
        point_dir[i] = {x / g, y / g};
        auto it = dir_cnt.find({-point_dir[i].first, -point_dir[i].second});
        if (it != dir_cnt.end()) {
            opp_cnt[i] = it->second;
        }
    }

    // Duplicate array for two-pointer
    vector<Point> pts2(2 * m);
    for (ll i = 0; i < m; i++) {
        pts2[i] = pts[i];
        pts2[i + m] = pts[i];
    }

    ll non_contain = 0;
    ll boundary = 0;
    ll r = 0;

    for (ll l = 0; l < m; l++) {
        if (r <= l) r = l + 1;

        // Advance r while points are strictly within pi CCW
        while (r < l + m) {
            ll c = cross(pts[l], pts2[r]);
            if (c > 0) { r++; continue; }
            if (c == 0 && dot(pts[l], pts2[r]) > 0 && r < m) {
                r++;
                continue;
            }
            break;
        }

        ll cnt = r - l - 1;  // points strictly between theta_l and theta_l+pi
        if (cnt >= 2) {
            non_contain += cnt * (cnt - 1) / 2;
        }
        // Boundary triangles: each opposite point forms cnt triangles
        // with the opposite point as the far vertex
        // But we must avoid double counting: only count when pts[l] is the
        // "leftmost" vertex of the boundary triangle.
        // For each opposite pair (l, j), the triangle (l, j, k) has pts[l]
        // as the leftmost. So we add opp_cnt[l] * cnt.
        // However, opp_cnt[l] counts ALL opposite points, including those
        // at both theta+pi (ahead) and theta-pi (behind, via wraparound).
        // We want only those at theta+pi (ahead, within the two-pointer range).
        // Since r stops at the first opposite point (cross=0, dot<0),
        // all opposite points are at or after position r.
        // Count opposite points at theta+pi that are in range [r, l+m):
        ll opp_ahead = 0;
        for (ll j = r; j < l + m; j++) {
            ll c = cross(pts[l], pts2[j]);
            if (c == 0 && dot(pts[l], pts2[j]) < 0) {
                opp_ahead++;
            } else if (c < 0) {
                break; // past the opposite group
            }
            // If c > 0, keep going (shouldn't happen after breaking)
        }
        boundary += opp_ahead * cnt;
    }

    ll total = m * (m - 1) * (m - 2) / 6;
    ll ans = total - non_contain - boundary;

    cout << ans << "\n";
    return 0;
}
