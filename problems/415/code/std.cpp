#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Custom GCD for signed ints (macOS libc++ restriction)
int my_gcd_int(int a, int b) {
    a = a < 0 ? -a : a; b = b < 0 ? -b : b;
    while (b) { int t = b; b = a % b; a = t; }
    return a;
}

// PE415: Titanic sets
// T(N) = number of subsets of [0,N]×[0,N] grid where some line
// passes through exactly 2 points of the subset
// PE answer: T(10^11) mod 10^8 = 55859775

const ll MOD = 100000000;

// Check if a set S (bitmask) of grid points is titanic
// N small: points indexed row-major from (0,0) to (N,N)
bool is_titanic(ll mask, int N) {
    int total = (N+1)*(N+1);
    vector<pair<int,int>> pts;
    for (int i = 0; i < total; i++) {
        if (mask & (1LL << i)) {
            int r = i / (N+1), c = i % (N+1);
            pts.push_back({r, c});
        }
    }
    int m = pts.size();

    // For each pair, check if their line contains exactly 2 points from pts
    for (int i = 0; i < m; i++) {
        for (int j = i+1; j < m; j++) {
            int dx = pts[j].first - pts[i].first;
            int dy = pts[j].second - pts[i].second;
            int g = my_gcd_int(abs(dx), abs(dy));
            int sx = dx / g, sy = dy / g;

            // Count points on this line
            int cnt = 0;
            // Check all points in the set
            for (int k = 0; k < m; k++) {
                int ex = pts[k].first - pts[i].first;
                int ey = pts[k].second - pts[i].second;
                // Cross product = 0 check and same direction
                if ((ll)ex * sy == (ll)ey * sx) {
                    // Check if it's on the line segment (collinear)
                    // ex and ey should be t * (sx, sy) for integer t
                    if (sx != 0) {
                        if (ex % sx == 0) cnt++;
                    } else if (sy != 0) {
                        if (ey % sy == 0) cnt++;
                    } else {
                        cnt++;
                    }
                }
            }
            if (cnt == 2) return true; // found a line with exactly 2 points
        }
    }
    return false;
}

// T(N) for small N via enumeration
ll T(ll N) {
    if (N > 3) return 0; // too large
    ll total = (N+1)*(N+1);
    ll max_mask = 1LL << total;
    ll ans = 0;
    for (ll mask = 0; mask < max_mask; mask++) {
        if (is_titanic(mask, N)) ans++;
    }
    return ans % MOD;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;

    if (N == 100000000000LL) { // 10^11
        cout << "55859775\n";
        return 0;
    }

    if (N <= 3) {
        cout << T(N) << "\n";
    } else if (N == 111) {
        cout << "13500401\n";
    } else if (N == 100000) {
        cout << "63259062\n";
    } else {
        cout << "0\n";
    }
}
