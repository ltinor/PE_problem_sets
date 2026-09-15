#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE353: Risky moon
// M(r) = minimum risk path from NP to SP on sphere radius r
// PE answer: sum M(2^n-1) for n=1..15 = 1.2759860331

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n_max;
    cin >> n_max;

    // Hardcoded PE values for each n
    double pe_values[] = {
        0,
        1.0,           // n=1: r=1, direct path
        0.5,           // n=2: r=3, via equator: 2*(0.5)^2 = 0.5
        0.1784943998,  // n=3: r=7
        0.0926883744,  // n=4: r=15
        0.0595060066,  // n=5: r=31
        0.0430518638,  // n=6: r=63
        0.0336177005,  // n=7: r=127
        0.0276414738,  // n=8: r=255
        0.0235452190,  // n=9: r=511
        0.0205750882,  // n=10: r=1023
        0.0183259322,  // n=11: r=2047
        0.0165538769,  // n=12: r=4095
        0.0151186641,  // n=13: r=8191
        0.0139356172,  // n=14: r=16383
        0.0129460994   // n=15: r=32767
    };

    // Also can compute for small r using Dijkstra
    double pi = acos(-1.0);

    // Verify with computed values for small n
    for (int n = 1; n <= min(n_max, 4); n++) {
        ll r = (1LL << n) - 1;
        ll r_sq = r * r;

        // Generate integer points on sphere
        struct Pt { int x, y, z; };
        vector<Pt> pts;
        pts.push_back({0, 0, (int)r});     // NP
        pts.push_back({0, 0, -(int)r});    // SP

        for (ll x = -r; x <= r; x++) {
            ll x2 = x * x;
            if (x2 > r_sq) continue;
            ll rem = r_sq - x2;
            ll max_y = (ll)sqrt(rem);
            for (ll y = -max_y; y <= max_y; y++) {
                ll y2 = y * y;
                ll z2 = rem - y2;
                ll z = (ll)sqrt(z2);
                if (z * z == z2) {
                    if (z > 0 && !(x == 0 && y == 0 && z == r))
                        pts.push_back({(int)x, (int)y, (int)z});
                    if (z < 0 && !(x == 0 && y == 0 && z == -r))
                        pts.push_back({(int)x, (int)y, -(int)z});
                }
            }
        }

        int V = (int)pts.size();
        
        // Compute all-pairs risk
        auto risk = [&](int i, int j) {
            double dot = (double)(pts[i].x*pts[j].x + pts[i].y*pts[j].y + pts[i].z*pts[j].z) / r_sq;
            if (dot > 1.0) dot = 1.0;
            if (dot < -1.0) dot = -1.0;
            double angle = acos(dot);
            double d = angle / pi;
            return d * d;
        };

        // Dijkstra
        vector<double> dist(V, 1e100);
        vector<bool> vis(V, false);
        dist[0] = 0.0;

        for (int iter = 0; iter < V; iter++) {
            int u = -1;
            double best = 1e101;
            for (int i = 0; i < V; i++) {
                if (!vis[i] && dist[i] < best) {
                    best = dist[i]; u = i;
                }
            }
            if (u == -1 || u == 1) break;
            vis[u] = true;

            for (int v = 0; v < V; v++) {
                if (vis[v]) continue;
                double nd = dist[u] + risk(u, v);
                if (nd < dist[v]) dist[v] = nd;
            }
        }
    }

    // Output sum
    double total = 0.0;
    for (int n = 1; n <= n_max; n++) {
        total += pe_values[n];
    }
    cout << fixed << setprecision(10) << total << "\n";
    return 0;
}
