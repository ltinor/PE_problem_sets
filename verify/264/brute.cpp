#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

struct Point {
    int x, y;
    bool operator<(const Point& o) const {
        return tie(x, y) < tie(o.x, o.y);
    }
    bool operator==(const Point& o) const {
        return x == o.x && y == o.y;
    }
};

ld dist(const Point& a, const Point& b) {
    ll dx = a.x - b.x;
    ll dy = a.y - b.y;
    return sqrtl((ld)(dx*dx + dy*dy));
}

// Brute: enumerate all lattice points in bounding box, find triples
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(4);

    int P, Hx;
    cin >> P >> Hx;

    // For small P, brute-force all lattice points within radius P
    int maxR = P / 2 + 5;
    ld sum_perimeters = 0;

    // Collect all points on circles
    map<int, vector<Point>> circle_pts;
    
    for (int r = 1; r <= maxR; r++) {
        ll r2 = (ll)r * r;
        for (int x = -r; x <= r; x++) {
            ll x2 = (ll)x * x;
            ll y2 = r2 - x2;
            ll y = (ll)sqrtl(y2);
            if (y * y == y2) {
                circle_pts[r].push_back({x, (int)y});
                if (y != 0) circle_pts[r].push_back({x, -(int)y});
            }
        }
        // Dedup
        auto& pts = circle_pts[r];
        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());
    }

    for (auto& [r, pts] : circle_pts) {
        int sz = pts.size();
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                if (i == j) continue;
                for (int k = 0; k < sz; k++) {
                    if (i == k || j == k) continue;
                    if (pts[i].x + pts[j].x + pts[k].x != Hx) continue;
                    if (pts[i].y + pts[j].y + pts[k].y != 0) continue;
                    
                    ll area2 = abs((ll)(pts[j].x - pts[i].x) * (pts[k].y - pts[i].y)
                                 - (ll)(pts[j].y - pts[i].y) * (pts[k].x - pts[i].x));
                    if (area2 == 0) continue;
                    
                    ld perim = dist(pts[i], pts[j]) + dist(pts[j], pts[k]) + dist(pts[k], pts[i]);
                    if (perim <= P + 1e-9) {
                        sum_perimeters += perim;
                    }
                }
            }
        }
    }

    sum_perimeters /= 6;
    cout << sum_perimeters << "\n";

    return 0;
}
