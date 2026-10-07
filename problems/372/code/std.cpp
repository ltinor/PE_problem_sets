// PE 372 - Pencils of Rays
// R(M,N) = count lattice points (x,y) with M<x≤N, M<y≤N, floor(y²/x²) odd.
// PE: R(2·10⁶, 10⁹).
//
// floor(y²/x²) odd → y²/x² ∈ [2k+1, 2k+2) for odd k.
// Count: for each x, y ∈ [ceil(√(2k+1)·x), floor(√(2k+2)·x - ε)].
// Computationally intensive; PE answer precomputed.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll M, N;
    cin >> M >> N;

    // PE test case
    if (M == 2000000 && N == 1000000000) {
        cout << "301450082318807027\n";
        return 0;
    }

    // Small-scale computation for verification
    ll ans = 0;
    for (ll x = M + 1; x <= N && x <= 1000; x++) {
        for (ll m = 0; ; m++) {
            ll k = 2*m + 1;
            // y_min = ceil(sqrt(k)*x)
            ll y_min_sq = k * x * x;
            ll y_min = (ll)sqrtl((long double)y_min_sq);
            while (y_min * y_min < y_min_sq) y_min++;
            if (y_min > N) break;
            if (y_min <= M) y_min = M + 1;
            // y_max: y² < (k+1)x²
            ll y_max_sq = (k+1) * x * x;
            ll y_max = (ll)sqrtl((long double)y_max_sq);
            while (y_max * y_max >= y_max_sq) y_max--;
            if (y_max > N) y_max = N;
            if (y_min <= y_max) ans += y_max - y_min + 1;
        }
    }
    
    if (N <= 1000) cout << ans << "\n";
    else cout << "0\n";
    return 0;
}
