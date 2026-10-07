#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 289 (reduced): count non-crossing Eulerian cycles L(m,n) on an m x n grid of circles.
//
// Each circle C(x,y) is the circumcircle of the unit square with corners
// (x,y),(x+1,y),(x+1,y+1),(x,y+1). Its 4 arcs are quarter-circles that bulge outward.
//
// Key fact: arcs from different circles only ever meet at lattice points (they never
// cross in the plane).  Therefore a closed path is "non-crossing" iff, at every lattice
// point, the incident arcs are paired (entered/left) in a non-crossing way.
//
// So L(m,n) equals the number of ways to pick, at every lattice point, a non-crossing
// perfect matching of the incident half-edges (arcs) such that the resulting
// "transition graph" (each arc joined to two neighbours via the pairings) is a single
// cycle.  We enumerate all such transition systems with backtracking and count those
// forming exactly one cycle.

// Directions (counter-clockwise): 0=E, 1=N, 2=W, 3=S.
// side: 0 = CW side of the ray, 1 = CCW side of the ray.

struct HalfEdge { int arc; int dir; int side; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    ll M;
    cin >> m >> n >> M;

    int V = (m + 1) * (n + 1);          // lattice points
    vector<vector<HalfEdge>> half(V);   // half-edges incident to each point
    int E = 0;                          // number of arcs = 4*m*n

    auto vid = [&](int x, int y) { return x * (n + 1) + y; };

    auto addArc = [&](int u, int du, int su, int v, int dv, int sv) {
        int a = E++;
        half[u].push_back({a, du, su});
        half[v].push_back({a, dv, sv});
    };

    for (int x = 0; x < m; x++) {
        for (int y = 0; y < n; y++) {
            int BL = vid(x, y), BR = vid(x + 1, y);
            int TR = vid(x + 1, y + 1), TL = vid(x, y + 1);

            // bottom arc BL-BR: at BL leaves east, bulges south (CW side);
            //                     at BR leaves west, bulges south (CCW side).
            addArc(BL, 0, 0, BR, 2, 1);
            // right arc BR-TR: at BR leaves north, bulges east (CW side);
            //                    at TR leaves south, bulges east (CCW side).
            addArc(BR, 1, 0, TR, 3, 1);
            // top arc TR-TL: at TR leaves west, bulges north (CW side);
            //                  at TL leaves east, bulges north (CCW side).
            addArc(TR, 2, 0, TL, 0, 1);
            // left arc TL-BL: at TL leaves south, bulges west (CW side);
            //                   at BL leaves north, bulges west (CCW side).
            addArc(TL, 3, 0, BL, 1, 1);
        }
    }

    // Cyclic (CCW) order of half-edges around each lattice point.
    vector<vector<int>> order(V);
    for (int v = 0; v < V; v++) {
        auto &hs = half[v];
        sort(hs.begin(), hs.end(), [](const HalfEdge &a, const HalfEdge &b) {
            return a.dir * 2 + a.side < b.dir * 2 + b.side;
        });
        order[v].resize(hs.size());
        for (size_t i = 0; i < hs.size(); i++) order[v][i] = hs[i].arc;
    }

    // All non-crossing perfect matchings of the cyclic order at each point.
    // Non-crossing matchings on a cycle == non-crossing matchings on a line
    // (the "cut" between the last and first point is never crossed).
    vector<vector<vector<pair<int, int>>>> matchings(V);
    for (int v = 0; v < V; v++) {
        const vector<int> &a = order[v];
        int k = (int)a.size();
        function<vector<vector<pair<int, int>>>(int, int)> gen =
            [&](int l, int r) -> vector<vector<pair<int, int>>> {
            vector<vector<pair<int, int>>> res;
            if (l > r) { res.push_back({}); return res; }
            for (int j = l + 1; j <= r; j += 2) {
                auto inside = gen(l + 1, j - 1);
                auto outside = gen(j + 1, r);
                for (auto &mi : inside)
                    for (auto &mo : outside) {
                        vector<pair<int, int>> m = {{a[l], a[j]}};
                        m.insert(m.end(), mi.begin(), mi.end());
                        m.insert(m.end(), mo.begin(), mo.end());
                        res.push_back(std::move(m));
                    }
            }
            return res;
        };
        matchings[v] = gen(0, k - 1);
    }

    // Rollback DSU over arcs; single cycle <=> number of components == 1.
    struct DSU {
        vector<int> par, sz;
        int comp;
        vector<array<int, 4>> hist; // {child, old_par, root, old_sz}
        void init(int n) {
            par.resize(n); sz.assign(n, 1); comp = n;
            iota(par.begin(), par.end(), 0); hist.clear();
        }
        int find(int x) { while (par[x] != x) x = par[x]; return x; }
        int checkpoint() { return (int)hist.size(); }
        void unite(int a, int b) {
            a = find(a); b = find(b);
            if (a == b) return;
            if (sz[a] < sz[b]) swap(a, b);
            hist.push_back({b, par[b], a, sz[a]});
            par[b] = a; sz[a] += sz[b]; comp--;
        }
        void rollback(int cp) {
            while ((int)hist.size() > cp) {
                auto t = hist.back(); hist.pop_back();
                par[t[0]] = t[1]; sz[t[2]] = t[3]; comp++;
            }
        }
    };

    DSU dsu;
    dsu.init(E);
    ll ans = 0;

    function<void(int)> dfs = [&](int v) {
        if (v == V) { if (dsu.comp == 1) ans++; return; }
        int cp = dsu.checkpoint();
        for (auto &mt : matchings[v]) {
            for (auto &pr : mt) dsu.unite(pr.first, pr.second);
            dfs(v + 1);
            dsu.rollback(cp);
        }
    };
    dfs(0);

    cout << (ans % M) << "\n";
    return 0;
}
