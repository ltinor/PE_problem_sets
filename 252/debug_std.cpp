#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point { ll x, y; int id; };
ll cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}
bool in_triangle(const Point& P, const Point& A, const Point& B, const Point& C) {
    ll c1 = cross(A, B, P);
    ll c2 = cross(B, C, P);
    ll c3 = cross(C, A, P);
    if (c1 == 0 || c2 == 0 || c3 == 0) return false;
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

int main() {
    int N = 5;
    auto all_pts = generate_points(N);
    
    for (int i = 0; i < N; i++)
        cerr << "Point " << i << ": (" << all_pts[i].x << ", " << all_pts[i].y << ")" << endl;
    
    int oi = 2; // (-454, -947)
    Point O = all_pts[oi];
    cerr << "Origin: (" << O.x << ", " << O.y << ")" << endl;
    
    vector<Point> pts;
    for (int i = 0; i < N; i++) {
        if (i == oi) continue;
        pts.push_back(all_pts[i]);
    }
    
    sort(pts.begin(), pts.end(), [&](const Point& a, const Point& b) {
        int qa = (a.y > O.y || (a.y == O.y && a.x > O.x)) ? 0 : 1;
        int qb = (b.y > O.y || (b.y == O.y && b.x > O.x)) ? 0 : 1;
        if (qa != qb) return qa < qb;
        ll c = cross(O, a, b);
        if (c != 0) return c > 0;
        ll da = (a.x-O.x)*(a.x-O.x) + (a.y-O.y)*(a.y-O.y);
        ll db = (b.x-O.x)*(b.x-O.x) + (b.y-O.y)*(b.y-O.y);
        return da < db;
    });
    
    int M = pts.size();
    cerr << "M = " << M << endl;
    for (int i = 0; i < M; i++)
        cerr << "  P" << i << ": (" << pts[i].x << ", " << pts[i].y << ") id=" << pts[i].id << endl;
    
    // Precompute visible
    vector<vector<bool>> visible(M, vector<bool>(M, false));
    for (int i = 0; i < M; i++) {
        for (int j = i + 1; j < M; j++) {
            if (cross(O, pts[i], pts[j]) <= 0) { cerr << "visible["<<i<<"]["<<j<<"] false (cross<=0)" << endl; continue; }
            visible[i][j] = true;
            for (int k = 0; k < M; k++) {
                if (k == i || k == j) continue;
                if (in_triangle(pts[k], O, pts[i], pts[j])) {
                    visible[i][j] = false;
                    cerr << "visible["<<i<<"]["<<j<<"] false, P"<<k<<" inside" << endl;
                    break;
                }
            }
            if (visible[i][j]) cerr << "visible["<<i<<"]["<<j<<"] true" << endl;
        }
    }
    
    vector<vector<ll>> dp(M, vector<ll>(M, 0));
    ll best = 0;
    
    for (int i = 0; i < M; i++) {
        for (int j = i + 1; j < M; j++) {
            if (!visible[i][j]) continue;
            ll a2 = cross(O, pts[i], pts[j]);
            dp[i][j] = a2;
            cerr << "init dp["<<i<<"]["<<j<<"] = " << a2 << endl;
            
            for (int k = 0; k < i; k++) {
                if (!visible[k][i]) continue;
                if (dp[k][i] == 0) continue;
                ll c = cross(pts[k], pts[i], pts[j]);
                if (c <= 0) { cerr << "  k="<<k<<": cross(P"<<k<<",P"<<i<<",P"<<j<<")="<<c<<" <=0, skip" << endl; continue; }
                
                bool empty = true;
                for (int p = 0; p < M; p++) {
                    if (p == k || p == i || p == j) continue;
                    if (in_triangle(pts[p], pts[k], pts[i], pts[j])) {
                        empty = false; break;
                    }
                }
                if (!empty) { cerr << "  k="<<k<<": triangle not empty, skip" << endl; continue; }
                
                ll new_val = dp[k][i] + a2;
                cerr << "  k="<<k<<": dp["<<k<<"]["<<i<<"]="<<dp[k][i]<<" + a2="<<a2<<" = " << new_val << endl;
                dp[i][j] = max(dp[i][j], new_val);
            }
            best = max(best, dp[i][j]);
            cerr << "dp["<<i<<"]["<<j<<"] = " << dp[i][j] << endl;
        }
    }
    
    cerr << "Best for this origin: " << best << " = " << best/2.0 << endl;
    return 0;
}
