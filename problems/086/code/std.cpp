#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Count cuboids with dimensions a<=b<=c<=M where shortest path is integer.
// Shortest path for a<=b<=c: sqrt((a+b)^2 + c^2)
// We need (a+b)^2 + c^2 to be a perfect square integer.

// For each M, count new cuboids where max dimension = M (c = M).
// For c = M, iterate over s = a+b from 2 to 2M.
// If s^2 + M^2 is perfect square, count (a,b) with a+b=s, 1<=a<=b<=M.

ll countPairs(ll s, ll M) {
    // Need a+b=s, 1<=a<=b<=M
    // a ranges from max(1, s-M) to s/2
    ll lo = max(1LL, s - M);
    ll hi = s / 2;
    if (lo > hi) return 0;
    return hi - lo + 1;
}

// Precompute perfect squares up to (2*MAX_M)^2
// Actually we need to check if s^2 + c^2 is a perfect square
// Max sum s = 2M, max c = M
// s^2 + c^2 <= (2M)^2 + M^2 = 5M^2
// sqrt(5M^2) = M*sqrt(5) ≈ 2.236M

bool isPerfectSquare(ll x) {
    ll r = (ll)sqrt((double)x);
    return r * r == x;
}

ll solve(ll K) {
    ll total = 0;
    ll M = 0;
    while (total <= K) {
        M++;
        // Count new cuboids with c = M
        for (ll s = 2; s <= 2 * M; s++) {
            ll sq = s * s + M * M;
            if (isPerfectSquare(sq)) {
                total += countPairs(s, M);
            }
        }
    }
    return M;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    cout << solve(K) << "\n";

    return 0;
}
