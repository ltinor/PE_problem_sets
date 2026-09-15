#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: check each triangle for small R
// Origin is inside triangle ABC iff origin can be written as
// convex combination with positive coefficients.
// Equivalent: barycentric coordinates all positive.
// using cross products to determine orientation

struct Point {
    int x, y;
};

ll cross(Point A, Point B, Point C) {
    return (ll)(B.x - A.x) * (C.y - A.y) - (ll)(B.y - A.y) * (C.x - A.x);
}

bool origin_inside(Point A, Point B, Point C) {
    // Origin (0,0) inside triangle ABC
    // Check using barycentric: all cross products with origin have same sign
    // Actually: check that origin is on same side of each edge as the third vertex
    Point O = {0, 0};
    ll c1 = cross(A, B, O);
    ll c2 = cross(B, C, O);
    ll c3 = cross(C, A, O);

    bool all_pos = (c1 > 0 && c2 > 0 && c3 > 0);
    bool all_neg = (c1 < 0 && c2 < 0 && c3 < 0);
    return all_pos || all_neg;
}

vector<Point> generate_points(int R) {
    vector<Point> pts;
    for (int x = -R+1; x < R; x++) {
        for (int y = -R+1; y < R; y++) {
            if (x == 0 && y == 0) continue;
            if (x*x + y*y < R*R) {
                pts.push_back({x, y});
            }
        }
    }
    return pts;
}

ll solve_brute(int R) {
    auto pts = generate_points(R);
    int N = pts.size();
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            for (int k = j+1; k < N; k++) {
                if (origin_inside(pts[i], pts[j], pts[k])) {
                    ans++;
                }
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int R;
        cin >> R;
        cout << solve_brute(R) << "\n";
    }

    return 0;
}
