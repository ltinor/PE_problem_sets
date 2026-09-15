#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
    ll x, y;
    int id;
};

ll cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Check if P is strictly inside triangle ABC (assuming CCW order A,B,C)
bool in_triangle(const Point& P, const Point& A, const Point& B, const Point& C) {
    ll c1 = cross(A, B, P);
    ll c2 = cross(B, C, P);
    ll c3 = cross(C, A, P);
    if (c1 == 0 || c2 == 0 || c3 == 0) return false; // on edge
    bool all_pos = (c1 > 0) && (c2 > 0) && (c3 > 0);
    bool all_neg = (c1 < 0) && (c2 < 0) && (c3 < 0);
    return all_pos || all_neg;
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
    for (int i = 0; i < N; i++) pts[i].id = i;
    return pts;
}

double solve_convex_hole(int N) {
    auto all_pts = generate_points(N);
    ll best_area2 = 0;

    for (int oi = 0; oi < N; oi++) {
        Point O = all_pts[oi];

        // Collect all other points, sort by polar angle from O
        vector<Point> pts;
        for (int i = 0; i < N; i++) {
            if (i == oi) continue;
            pts.push_back(all_pts[i]);
        }

        int M = (int)pts.size();
        if (M < 2) continue;

        // Sort by polar angle (by quadrant, then cross product)
        sort(pts.begin(), pts.end(), [&](const Point& a, const Point& b) {
            // Compare quadrants first
            int qa = (a.y > O.y || (a.y == O.y && a.x > O.x)) ? 0 : 1;
            int qb = (b.y > O.y || (b.y == O.y && b.x > O.x)) ? 0 : 1;
            if (qa != qb) return qa < qb;
            ll c = cross(O, a, b);
            if (c != 0) return c > 0;
            ll da = (a.x-O.x)*(a.x-O.x) + (a.y-O.y)*(a.y-O.y);
            ll db = (b.x-O.x)*(b.x-O.x) + (b.y-O.y)*(b.y-O.y);
            return da < db;
        });

        // Duplicate points to handle wrap-around (for polygons starting in upper half)
        // Actually, convex hole with O as vertex: vertices must be in strict CCW order.
        // We need to consider all convex polygons that have O as the "leftmost" in angular sense.
        // For each starting vertex, build polygon going CCW (within 180 degrees from O's perspective)

        // Precompute: for each i, the set of j where triangle(O, pi, pj) is empty
        // and O->pi->pj is a left turn
        vector<vector<bool>> visible(M, vector<bool>(M, false));
        for (int i = 0; i < M; i++) {
            for (int j = i + 1; j < M; j++) {
                if (cross(O, pts[i], pts[j]) <= 0) continue;
                visible[i][j] = true;
                for (int k = 0; k < M; k++) {
                    if (k == i || k == j) continue;
                    if (in_triangle(pts[k], O, pts[i], pts[j])) {
                        visible[i][j] = false;
                        break;
                    }
                }
            }
        }

        // Also precompute triangle emptiness for (k,i,j)
        vector<vector<vector<bool>>> empty_kij(M, vector<vector<bool>>(M, vector<bool>(M, true)));
        // We'll compute on-the-fly to save memory, or precompute triples
        // For efficiency: compute whether triangle(pts[k], pts[i], pts[j]) is empty
        // Only needed when cross(pts[k], pts[i], pts[j]) > 0 (left turn)

        // dp[i][j] = max 2*area of convex hole O->...->pts[i]->pts[j]
        vector<vector<ll>> dp(M, vector<ll>(M, 0));

        for (int i = 0; i < M; i++) {
            for (int j = i + 1; j < M; j++) {
                if (!visible[i][j]) continue;

                ll a2 = cross(O, pts[i], pts[j]);
                dp[i][j] = a2;

                for (int k = 0; k < i; k++) {
                    if (!visible[k][i]) continue;
                    if (dp[k][i] == 0) continue;
                    if (cross(pts[k], pts[i], pts[j]) <= 0) continue;

                    // Check triangle(pts[k], pts[i], pts[j]) is empty
                    bool empty = true;
                    for (int p = 0; p < M; p++) {
                        if (p == k || p == i || p == j) continue;
                        if (in_triangle(pts[p], pts[k], pts[i], pts[j])) {
                            empty = false;
                            break;
                        }
                    }
                    if (!empty) continue;

                    dp[i][j] = max(dp[i][j], dp[k][i] + a2);
                }

                best_area2 = max(best_area2, dp[i][j]);
            }
        }
    }

    return best_area2 / 2.0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    cout << fixed << setprecision(1) << solve_convex_hole(N) << "\n";
    return 0;
}
