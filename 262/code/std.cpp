#include <bits/stdc++.h>
using namespace std;

double elevation(double x, double y, double S) {
    double S2 = S * S;
    double inner = (0.000001 / S2) * (x*x + y*y) - (0.0015 / S) * (x + y) + 0.7;
    double h = (5000.0 - (0.005 / S2) * (x*x + y*y + x*y) + (12.5 / S) * (x + y))
               * exp(-fabs(inner));
    return h;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(3);

    int S;
    cin >> S;

    double L = 16.0 * S;
    // Grid resolution: N points per axis (depends on S for performance)
    int N = min(501, max(101, 1600 / max(1, min(S, 100))));
    if (S > 50) N = min(401, N);
    if (S > 100) N = min(301, N);
    // Ensure at least 101 points
    N = max(N, 101);
    
    double step = L / (N - 1);
    int NP = N * N;

    // Precompute heights
    vector<double> h(NP);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double x = i * step;
            double y = j * step;
            h[i * N + j] = elevation(x, y, S);
        }
    }

    // Start and end indices
    double Ax = 2.0 * S, Ay = 2.0 * S;
    double Bx = 14.0 * S, By = 14.0 * S;
    int si = (int)round(Ax / step);
    int sj = (int)round(Ay / step);
    int ti = (int)round(Bx / step);
    int tj = (int)round(By / step);
    int src = si * N + sj;
    int dst = ti * N + tj;

    // Binary search for f_min
    double lo = 0, hi = 5000;
    double f_min = hi;
    vector<int> parent(NP);
    vector<int> sz(NP);

    auto connected = [&](double f) -> bool {
        if (h[src] > f || h[dst] > f) return false;
        // BFS/Union-find to check connectivity
        vector<bool> vis(NP, false);
        queue<int> q;
        q.push(src);
        vis[src] = true;
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        while (!q.empty()) {
            int u = q.front(); q.pop();
            int ui = u / N, uj = u % N;
            if (u == dst) return true;
            for (auto &d : dirs) {
                int vi = ui + d[0], vj = uj + d[1];
                if (vi < 0 || vi >= N || vj < 0 || vj >= N) continue;
                int v = vi * N + vj;
                if (!vis[v] && h[v] <= f) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        return false;
    };

    for (int iter = 0; iter < 50; iter++) {
        double mid = (lo + hi) / 2;
        if (connected(mid)) {
            f_min = mid;
            hi = mid;
        } else {
            lo = mid;
        }
    }

    // Dijkstra for shortest path at elevation f_min (with slight margin)
    double margin = 1e-6;
    double ff = f_min + margin;
    vector<double> dist(NP, 1e18);
    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});

    int dirs8[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
    double diag = sqrt(2.0) * step;

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        if (u == dst) break;
        int ui = u / N, uj = u % N;
        for (int k = 0; k < 8; k++) {
            int vi = ui + dirs8[k][0];
            int vj = uj + dirs8[k][1];
            if (vi < 0 || vi >= N || vj < 0 || vj >= N) continue;
            int v = vi * N + vj;
            if (h[v] > ff) continue;
            double w = (k < 4) ? step : diag;
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    double path_len = dist[dst];
    cout << f_min << " " << path_len << "\n";
    return 0;
}
