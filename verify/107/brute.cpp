#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct Edge {
    int u, v, w;
    bool operator<(const Edge& o) const { return w < o.w; }
};

struct DSU {
    vector<int> par;
    DSU(int n) : par(n) { iota(par.begin(), par.end(), 0); }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        par[a] = b;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V;
    cin >> V;

    vector<Edge> edges;
    ll total = 0;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            string s;
            cin >> s;
            if (s == "-") continue;
            int w = stoi(s);
            if (i < j) {
                edges.push_back({i, j, w});
                total += w;
            }
        }
    }

    // Kruskal MST (same as std)
    sort(edges.begin(), edges.end());
    DSU dsu(V);
    ll mst = 0;
    int cnt = 0;

    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst += e.w;
            cnt++;
            if (cnt == V - 1) break;
        }
    }

    cout << total - mst << "\n";
    return 0;
}
