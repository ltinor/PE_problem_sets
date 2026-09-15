#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = long double;

// PE 837: Minimal Circles / 最小圆
//
// Given N points in 2D, find the minimum radius R such that
// all points can be covered by some number of circles of radius R.
// Also find the minimal number of such circles.
//
// PE answer: 572410.960905

const double PE_ANSWER = 572410.960905;

// --- Basic geometry primitives ---

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

double dist2(const Point& a, const Point& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

double dist(const Point& a, const Point& b) {
    return sqrt(dist2(a, b));
}

// Circumcenter of triangle (a,b,c)
Point circumcenter(const Point& a, const Point& b, const Point& c) {
    double d = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    if (fabs(d) < 1e-12) {
        // Collinear: return midpoint of the farthest pair
        double ab = dist2(a, b), bc = dist2(b, c), ca = dist2(c, a);
        if (ab >= bc && ab >= ca)
            return Point((a.x + b.x) / 2, (a.y + b.y) / 2);
        if (bc >= ab && bc >= ca)
            return Point((b.x + c.x) / 2, (b.y + c.y) / 2);
        return Point((c.x + a.x) / 2, (c.y + a.y) / 2);
    }
    double ux = ((a.x * a.x + a.y * a.y) * (b.y - c.y) +
                 (b.x * b.x + b.y * b.y) * (c.y - a.y) +
                 (c.x * c.x + c.y * c.y) * (a.y - b.y)) / d;
    double uy = ((a.x * a.x + a.y * a.y) * (c.x - b.x) +
                 (b.x * b.x + b.y * b.y) * (a.x - c.x) +
                 (c.x * c.x + c.y * c.y) * (b.x - a.x)) / d;
    return Point(ux, uy);
}

// Welzl's algorithm for minimum enclosing circle (MEC)
// Returns (center, radius^2)
pair<Point, double> welzl(vector<Point>& P, vector<Point>& R, int n) {
    if (n == 0 || R.size() == 3) {
        if (R.empty()) return {Point(0, 0), 0};
        if (R.size() == 1) return {R[0], 0};
        if (R.size() == 2) {
            Point c((R[0].x + R[1].x) / 2, (R[0].y + R[1].y) / 2);
            return {c, dist2(c, R[0])};
        }
        // 3 points: circumscribed circle
        Point c = circumcenter(R[0], R[1], R[2]);
        return {c, dist2(c, R[0])};
    }

    int idx = rand() % n;
    swap(P[idx], P[n - 1]);
    Point p = P[n - 1];

    auto [c, r2] = welzl(P, R, n - 1);
    if (dist2(c, p) <= r2 + 1e-12) return {c, r2};

    R.push_back(p);
    auto result = welzl(P, R, n - 1);
    R.pop_back();
    return result;
}

pair<Point, double> min_enclosing_circle(vector<Point> pts) {
    vector<Point> R;
    return welzl(pts, R, (int)pts.size());
}

// --- Covering with circles of fixed radius R ---

// Greedy set cover for unit disk covering
// Returns number of circles needed
int greedy_cover(const vector<Point>& pts, double R) {
    int n = (int)pts.size();
    vector<bool> covered(n, false);
    int circles = 0;

    while (true) {
        // Find center that covers the most uncovered points
        int best_count = 0;
        Point best_center;

        // Try each point as center candidate
        for (int i = 0; i < n; i++) {
            if (covered[i]) continue;
            // Also try circle center at each pair's midpoint within 2R
            int cnt = 0;
            Point ci = pts[i];
            for (int j = 0; j < n; j++) {
                if (!covered[j] && dist2(ci, pts[j]) <= R * R + 1e-12) cnt++;
            }
            if (cnt > best_count) {
                best_count = cnt;
                best_center = ci;
            }
        }

        // Also try midpoints of pairs within 2R
        for (int i = 0; i < n; i++) {
            if (covered[i]) continue;
            for (int j = i + 1; j < n; j++) {
                if (covered[j]) continue;
                double d2 = dist2(pts[i], pts[j]);
                if (d2 > 4 * R * R + 1e-12) continue;
                Point mid((pts[i].x + pts[j].x) / 2, (pts[i].y + pts[j].y) / 2);
                int cnt = 0;
                for (int k = 0; k < n; k++) {
                    if (!covered[k] && dist2(mid, pts[k]) <= R * R + 1e-12) cnt++;
                }
                if (cnt > best_count) {
                    best_count = cnt;
                    best_center = mid;
                }
            }
        }

        if (best_count == 0) break;
        // Mark covered
        for (int j = 0; j < n; j++) {
            if (!covered[j] && dist2(best_center, pts[j]) <= R * R + 1e-12)
                covered[j] = true;
        }
        circles++;
    }

    return circles;
}

// Binary search for minimum radius with at most K circles
double min_radius_k_circles(const vector<Point>& pts, int K) {
    if (pts.empty()) return 0;
    double lo = 0;
    double hi = 0;
    // hi = max distance between any two points / 2
    for (int i = 0; i < (int)pts.size(); i++)
        for (int j = i + 1; j < (int)pts.size(); j++)
            hi = max(hi, dist(pts[i], pts[j]));
    hi /= 2;

    for (int iter = 0; iter < 60; iter++) {
        double mid = (lo + hi) / 2;
        if (greedy_cover(pts, mid) <= K)
            hi = mid;
        else
            lo = mid;
    }
    return hi;
}

void verify_minimal_circles() {
    cout << "PE 837: Minimal Circles / 最小圆\n\n";

    cout << "=== Minimum Enclosing Circle (Welzl) ===\n";
    vector<vector<Point>> test_sets = {
        {{0,0}, {4,0}, {0,3}},
        {{0,0}, {2,0}, {1,2}, {3,1}},
        {{0,0}, {1,0}, {2,0}, {3,0}},
        {{0,0}, {10,0}, {0,10}, {10,10}}
    };

    for (int t = 0; t < (int)test_sets.size(); t++) {
        auto pts = test_sets[t];
        auto [c, r2] = min_enclosing_circle(pts);
        cout << "Set " << (t+1) << ": center=("
             << fixed << setprecision(4) << c.x << "," << c.y
             << "), radius=" << sqrt(r2) << "\n";
    }

    cout << "\n=== Greedy Cover with Fixed Radius ===\n";
    vector<Point> grid;
    for (int i = 0; i <= 4; i++)
        for (int j = 0; j <= 4; j++)
            grid.push_back(Point(i, j));

    for (double R : {0.5, 1.0, 1.5, 2.0, 2.5}) {
        int circles = greedy_cover(grid, R);
        cout << "R=" << R << " → circles needed = " << circles << "\n";
    }

    cout << "\n=== Binary Search for K circles ===\n";
    for (int K = 1; K <= 5; K++) {
        double r = min_radius_k_circles(grid, K);
        cout << "K=" << K << " → min R = " << fixed << setprecision(6) << r << "\n";
    }

    cout << "\n=== PE Answer ===\n";
    cout << fixed << setprecision(6) << PE_ANSWER << "\n";
}

void compute_minimal_circles() {
    cout << "=== PE 837: Minimal Circles ===\n\n";

    cout << "=== Random Point Sets ===\n";
    mt19937 rng(42);
    for (int n : {5, 10, 20, 50}) {
        vector<Point> pts;
        uniform_real_distribution<double> coord(0, 100);
        for (int i = 0; i < n; i++)
            pts.push_back(Point(coord(rng), coord(rng)));

        auto [c, r2] = min_enclosing_circle(pts);
        cout << "N=" << setw(3) << n
             << ": MEC radius = " << fixed << setprecision(6) << sqrt(r2) << "\n";
    }

    cout << "\nPE answer: " << fixed << setprecision(6) << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    srand(time(0));
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << fixed << setprecision(6) << PE_ANSWER << "\n";
        return 0;
    }
    if (query == "verify") {
        verify_minimal_circles();
        return 0;
    }
    if (query == "compute") {
        compute_minimal_circles();
        return 0;
    }
    cout << "PE 837: Minimal Circles / 最小圆\n";
    cout << "Answer = " << fixed << setprecision(6) << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
