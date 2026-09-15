#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int my_gcd(int a, int b) { return b ? my_gcd(b, a % b) : a; }

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(4);

    int P, Hx;
    cin >> P >> Hx;

    int maxR = P; // rough bound: perimeter ≤ P ⇒ each side ≤ P/2, circumradius ≤ P/2
    // Actually max side ≤ P/2, diameter ≥ max side, so R ≤ P/2

    // Map: radius -> list of lattice points on circle
    map<int, vector<Point>> circle_pts;
    
    // Generate all primitive Pythagorean triples
    for (int m = 2; m * m <= maxR; m++) {
        for (int n = 1; n < m; n++) {
            if ((m - n) % 2 == 0) continue; // m-n must be odd for primitive
            if (my_gcd(m, n) != 1) continue;
            
            int a = m*m - n*n;
            int b = 2*m*n;
            int c = m*m + n*n;
            
            // Add multiples
            for (int k = 1; k * c <= maxR; k++) {
                int r = k * c;
                int ka = k * a, kb = k * b;
                // Add all 8 symmetric points (accounting for signs and swaps)
                vector<Point> pts = {
                    {ka, kb}, {ka, -kb}, {-ka, kb}, {-ka, -kb},
                    {kb, ka}, {kb, -ka}, {-kb, ka}, {-kb, -ka}
                };
                for (auto& p : pts) {
                    circle_pts[r].push_back(p);
                }
            }
        }
    }
    
    // Also add axial points: (R,0), (-R,0), (0,R), (0,-R) for all R
    // These are always on the circle but might not come from triples
    for (int r = 1; r <= maxR; r++) {
        // Always add axial points
        circle_pts[r].push_back({r, 0});
        circle_pts[r].push_back({-r, 0});
        circle_pts[r].push_back({0, r});
        circle_pts[r].push_back({0, -r});
    }

    ld sum_perimeters = 0;
    int tri_count = 0;

    for (auto& [r, pts] : circle_pts) {
        // Dedup
        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());
        
        int sz = pts.size();
        if (sz < 3) continue;
        
        // Check all ordered triples (each triangle counted 6 times)
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                if (i == j) continue;
                for (int k = 0; k < sz; k++) {
                    if (i == k || j == k) continue;
                    
                    // Check A+B+C = (Hx, 0)
                    int sx = pts[i].x + pts[j].x + pts[k].x;
                    int sy = pts[i].y + pts[j].y + pts[k].y;
                    if (sx != Hx || sy != 0) continue;
                    
                    // Check non-degenerate (area > 0)
                    ll area2 = abs((ll)(pts[j].x - pts[i].x) * (pts[k].y - pts[i].y)
                                 - (ll)(pts[j].y - pts[i].y) * (pts[k].x - pts[i].x));
                    if (area2 == 0) continue;
                    
                    // Compute perimeter
                    ld d12 = dist(pts[i], pts[j]);
                    ld d23 = dist(pts[j], pts[k]);
                    ld d31 = dist(pts[k], pts[i]);
                    ld perim = d12 + d23 + d31;
                    
                    if (perim <= P + 1e-9) {
                        sum_perimeters += perim;
                        tri_count++;
                    }
                }
            }
        }
    }

    // Each triangle counted 6 times (3! permutations)
    sum_perimeters /= 6;
    
    cout << sum_perimeters << "\n";

    return 0;
}
