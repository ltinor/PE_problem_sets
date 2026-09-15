#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE412 brute: enumerate all valid numberings for very small L-shapes
// Uses DP: number of linear extensions = number of topological sorts
// of the partial order defined by the grid constraints

const ll M = 76543217;

// For very small m: enumerate all fillings of the L-shape
// Each valid numbering gives a permutation of {1..N}
// such that each cell > cell to its left and cell below (wait, "smaller than the number below it and to the left of it")
// So numbers increase going right and down (standard Young tableaux)
// Cell value < value below, and < value to the left
// Wait re-read: "the number in every cell is smaller than the number below it and to the left of it"
// So cell < cell below AND cell < cell to left
// This means numbers increase going down and going left
// This is a standard Young tableaux (increasing right, increasing down) but rotated

// Hook-length DP: number of SYT of shape λ

ll brute_LC(ll m, ll n) {
    ll N = m*m - n*n;
    if (N > 6) return 0; // too large for brute enumeration

    // Collect all cell coordinates
    vector<pair<ll,ll>> cells;
    for (ll r = 0; r < m; r++) {
        for (ll c = 0; c < m; c++) {
            if (r < n && c >= m - n) continue;
            cells.push_back({r, c});
        }
    }
    sort(cells.begin(), cells.end());

    // Generate all permutations and check constraints
    vector<ll> perm(N);
    for (ll i = 0; i < N; i++) perm[i] = i + 1;

    ll ans = 0;
    do {
        // Assign perm values to cells
        vector<vector<ll>> grid(m, vector<ll>(m, -1));
        for (ll i = 0; i < N; i++) {
            auto [r, c] = cells[i];
            grid[r][c] = perm[i];
        }
        // Check: cell < cell below AND cell < cell to left
        bool ok = true;
        for (ll r = 0; r < m && ok; r++) {
            for (ll c = 0; c < m && ok; c++) {
                if (r < n && c >= m - n) continue;
                ll val = grid[r][c];
                // below
                if (r + 1 < m) {
                    bool below_exists = !(r+1 < n && c >= m-n);
                    if (below_exists && grid[r+1][c] != -1) {
                        if (val >= grid[r+1][c]) ok = false;
                    }
                }
                // left
                if (c - 1 >= 0) {
                    bool left_exists = !(r < n && c-1 >= m-n);
                    if (left_exists && grid[r][c-1] != -1) {
                        if (val >= grid[r][c-1]) ok = false;
                    }
                }
            }
        }
        if (ok) ans++;
    } while (next_permutation(perm.begin(), perm.end()));

    return ans % M;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll m, n; cin >> m >> n;
    cout << brute_LC(m, n) << "\n";
}
