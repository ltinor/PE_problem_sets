#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point { ll x, y; };

ll cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> generate_points(int N) {
    vector<Point> pts(N);
    ll S = 290797;
    for (int i = 0; i < 2 * N; i++) {
        S = (S * S) % 50515093;
        ll T = (S % 2000) - 1000;
        if (i % 2 == 0) pts[i/2].x = T;
        else pts[i/2].y = T;
    }
    return pts;
}

// Convex hull (Monotone Chain), returns hull vertices in CCW order
vector<Point> convex_hull(vector<Point> pts) {
    sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    vector<Point> hull;
    for (int phase = 0; phase < 2; phase++) {
        int start = (int)hull.size();
        for (const auto& p : pts) {
            while ((int)hull.size() >= start + 2) {
                auto& a = hull[hull.size() - 2];
                auto& b = hull.back();
                if (cross(a, b, p) > 0) break;
                hull.pop_back();
            }
            hull.push_back(p);
        }
        hull.pop_back();
        reverse(pts.begin(), pts.end());
    }
    return hull;
}

// Check if point P is inside convex polygon hull (strict interior)
bool point_in_polygon(const Point& P, const vector<Point>& hull) {
    int n = (int)hull.size();
    if (n < 3) return false;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (cross(hull[i], hull[j], P) >= 0) return false;
    }
    return true;
}

// Polygon area (2x)
ll polygon_area2(const vector<Point>& pts) {
    int n = (int)pts.size();
    if (n < 3) return 0;
    ll area2 = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area2 += pts[i].x * pts[j].y - pts[i].y * pts[j].x;
    }
    return abs(area2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    auto pts = generate_points(N);
    ll best_area2 = 0;

    // Enumerate all subsets of points (2^N)
    int total = 1 << N;
    for (int mask = 1; mask < total; mask++) {
        if (__builtin_popcount(mask) < 3) continue;

        vector<Point> subset;
        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) subset.push_back(pts[i]);
        }

        // Compute convex hull of subset
        auto hull = convex_hull(subset);
        if (hull.size() < 3) continue;

        // Check that hull vertices are a subset of original vertices
        // (convex_hull may include collinear points we want to exclude)
        // Simplify: check no original point is strictly inside the hull
        bool empty = true;
        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) continue; // skip hull vertices
            // Check if pts[i] is in hull interior
            bool on_boundary = false;
            for (int j = 0; j < (int)hull.size(); j++) {
                int k = (j + 1) % hull.size();
                if (cross(hull[j], hull[k], pts[i]) == 0) {
                    // Check if on segment
                    ll minx = min(hull[j].x, hull[k].x);
                    ll maxx = max(hull[j].x, hull[k].x);
                    ll miny = min(hull[j].y, hull[k].y);
                    ll maxy = max(hull[j].y, hull[k].y);
                    if (pts[i].x >= minx && pts[i].x <= maxx &&
                        pts[i].y >= miny && pts[i].y <= maxy) {
                        on_boundary = true;
                        break;
                    }
                }
            }
            if (!on_boundary && point_in_polygon(pts[i], hull)) {
                empty = false;
                break;
            }
        }
        if (!empty) continue;

        ll area2 = polygon_area2(hull);
        best_area2 = max(best_area2, area2);
    }

    double area = best_area2 / 2.0;
    cout << fixed << setprecision(1) << area << "\n";
    return 0;
}
