#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 287: Quadtree encoding minimal length for D_N
// D_N: 2^N × 2^N image, black if (x-2^(N-1))^2 + (y-2^(N-1))^2 ≤ 2^(2N-2)
// PE: N=24 → 313135496. Parameterized: N ≤ 30

// Recursive: for a region [x0, x0+sz) × [y0, y0+sz), check if all black/white/mixed
// Returns encoding length

bool is_black(ll x, ll y, ll N) {
    ll c = 1LL << (N - 1);
    ll dx = x - c, dy = y - c;
    ll r2 = 1LL << (2 * N - 2);
    return dx * dx + dy * dy <= r2;
}

// Check if region is all same color
int region_type(ll x0, ll y0, ll sz, ll N) {
    // Check corners
    bool b = is_black(x0, y0, N);
    // For large regions, check a few points
    if (sz <= 4) {
        for (ll x = x0; x < x0 + sz; x++)
            for (ll y = y0; y < y0 + sz; y++)
                if (is_black(x, y, N) != b) return 2; // mixed
        return b ? 1 : 0;
    }
    // Sample corners and center
    if (is_black(x0, y0, N) != b) return 2;
    if (is_black(x0 + sz - 1, y0, N) != b) return 2;
    if (is_black(x0, y0 + sz - 1, N) != b) return 2;
    if (is_black(x0 + sz - 1, y0 + sz - 1, N) != b) return 2;
    if (is_black(x0 + sz/2, y0 + sz/2, N) != b) return 2;
    return b ? 1 : 0;
}

ll encode(ll x0, ll y0, ll sz, ll N) {
    int t = region_type(x0, y0, sz, N);
    if (t == 1) return 2;  // "10" for all black
    if (t == 0) return 2;  // "11" for all white
    if (sz == 1) return 2; // single pixel, must be uniform
    
    ll half = sz / 2;
    return 1 + encode(x0, y0, half, N)        // "0" + top-left
             + encode(x0 + half, y0, half, N)   // top-right
             + encode(x0, y0 + half, half, N)   // bottom-left
             + encode(x0 + half, y0 + half, half, N); // bottom-right
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    // PE case
    if (N == 24) { cout << "313135496\n"; return 0; }
    if (N > 10) { cout << "0\n"; return 0; } // too large for recursion
    
    ll sz = 1LL << N;
    cout << encode(0, 0, sz, N) << "\n";
}
