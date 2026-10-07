#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for small n: O(n^3) check all triples

struct Point {
    ll x, y;
};

// Cross product: (B-A) × (C-A)
ll cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Check if origin (0,0) is strictly inside triangle (p1,p2,p3)
bool contains_origin(const Point &p1, const Point &p2, const Point &p3) {
    // Origin is inside iff it's on the same side of each edge as the third vertex
    // Use barycentric / same-side technique
    ll d1 = cross(p1, p2, {0, 0});
    ll d2 = cross(p2, p3, {0, 0});
    ll d3 = cross(p3, p1, {0, 0});

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
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
        pts.push_back({px - SUB_X, py - SUB_Y});
    }

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = i + 1; j < n; j++) {
            for (ll k = j + 1; k < n; k++) {
                if (contains_origin(pts[i], pts[j], pts[k])) {
                    ans++;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
