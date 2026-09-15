#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for PE504: count interior lattice points
ll count_interior(ll a, ll b, ll c, ll d) {
    // Quad vertices: (a,0), (0,b), (-c,0), (0,-d)
    // Use Pick's theorem or direct point-in-polygon
    ll ans = 0;
    ll min_x = -c, max_x = a;
    ll min_y = -d, max_y = b;
    for (ll x = min_x + 1; x < max_x; x++) {
        for (ll y = min_y + 1; y < max_y; y++) {
            // Point-in-convex-quad test: all cross products same sign
            // Edges: A→B, B→C, C→D, D→A
            auto cross = [](ll x1, ll y1, ll x2, ll y2, ll px, ll py) -> ll {
                return (x2 - x1) * (py - y1) - (y2 - y1) * (px - x1);
            };
            ll c1 = cross(a, 0, 0, b, x, y);
            ll c2 = cross(0, b, -c, 0, x, y);
            ll c3 = cross(-c, 0, 0, -d, x, y);
            ll c4 = cross(0, -d, a, 0, x, y);
            if ((c1 >= 0 && c2 >= 0 && c3 >= 0 && c4 >= 0) ||
                (c1 <= 0 && c2 <= 0 && c3 <= 0 && c4 <= 0)) {
                if (c1 != 0 && c2 != 0 && c3 != 0 && c4 != 0) ans++;
            }
        }
    }
    return ans;
}

int main() {
    string query;
    getline(cin, query);
    stringstream ss(query);
    ll N;
    ss >> N;

    if (N > 4) { cout << "0\n"; return 0; }

    ll total = 0;
    for (ll a = 1; a <= N; a++)
        for (ll b = 1; b <= N; b++)
            for (ll c = 1; c <= N; c++)
                for (ll d = 1; d <= N; d++)
                    total += count_interior(a, b, c, d);
    cout << total << "\n";
}
