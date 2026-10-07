#include <bits/stdc++.h>
using namespace std;

double elevation(double x, double y, double S) {
    double S2 = S * S;
    double inner = (0.000001 / S2) * (x*x + y*y) - (0.0015 / S) * (x + y) + 0.7;
    double h = (5000.0 - (0.005 / S2) * (x*x + y*y + x*y) + (12.5 / S) * (x + y))
               * exp(-fabs(inner));
    return h;
}

// Brute: coarser grid, same algorithm
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(3);

    int S;
    cin >> S;

    double L = 16.0 * S;
    // Coarser grid for brute
    int N = min(201, max(51, 320 / max(1, min(S, 20))));
    N = max(N, 51);

    double step = L / (N - 1);
    int NP = N * N;

    vector<double> h(NP);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            h[i * N + j] = elevation(i * step, j * step, S);
        }
    }

    double Ax = 2.0 * S, Ay = 2.0 * S;
    double Bx = 14.0 * S, By = 14.0 * S;
    int si = (int)round(Ax / step);
    int sj = (int)round(Ay / step);
    int ti = (int)round(Bx / step);
    int tj = (int)round(By / step);
    int src = si * N + sj;
    int dst = ti * N + tj;

    double lo = 0, hi = 5000;
    double f_min = hi;

    for (int iter = 0; iter < 40; iter++) {
        double mid = (lo + hi) / 2;
        if (h[src] > mid || h[dst] > mid) { lo = mid; continue; }
        vector<bool> vis(NP, false);
        queue<int> q;
        q.push(src);
        vis[src] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            int ui = u / N, uj = u % N;
            for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++) {
                    if (di == 0 && dj == 0) continue;
                    int vi = ui + di, vj = uj + dj;
                    if (vi < 0 || vi >= N || vj < 0 || vj >= N) continue;
                    int v = vi * N + vj;
                    if (!vis[v] && h[v] <= mid) {
                        vis[v] = true;
                        q.push(v);
                    }
                }
        }
        if (vis[dst]) { f_min = mid; hi = mid; }
        else lo = mid;
    }

    double ff = f_min + 1e-6;
    vector<double> dist(NP, 1e18);
    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        if (u == dst) break;
        int ui = u / N, uj = u % N;
        for (int di = -1; di <= 1; di++)
            for (int dj = -1; dj <= 1; dj++) {
                if (di == 0 && dj == 0) continue;
                int vi = ui + di, vj = uj + dj;
                if (vi < 0 || vi >= N || vj < 0 || vj >= N) continue;
                int v = vi * N + vj;
                if (h[v] > ff) continue;
                double w = (abs(di) + abs(dj) == 2) ? sqrt(2.0) * step : step;
                if (d + w < dist[v]) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
    }

    cout << f_min << " " << dist[dst] << "\n";
    return 0;
}
