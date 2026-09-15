#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Number of rectangles in m x n grid: C(m+1,2) * C(n+1,2) = m*(m+1)*n*(n+1)/4
// Given target T, find m*n that minimizes |rects(m,n) - T|

ll rects(ll m, ll n) {
    return m * (m + 1) * n * (n + 1) / 4;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll T;
    cin >> T;

    ll best_diff = LLONG_MAX;
    ll best_area = 0;

    // Upper bound: when m=1, rects = 1 * n*(n+1)/2 ≈ T
    // n*(n+1)/2 ≈ T → n ≈ sqrt(2T)
    // So m ranges from 1 to sqrt(2T)
    ll limit = (ll)sqrt(2.0 * T) + 10;

    for (ll m = 1; m <= limit; m++) {
        // We need m*(m+1)*n*(n+1)/4 ≈ T
        // n*(n+1) ≈ 4T / (m*(m+1))
        ll target = 4 * T / (m * (m + 1));
        if (target == 0) break;

        // n*(n+1) ≈ target → n ≈ sqrt(target)
        ll n = (ll)sqrt((double)target);
        // Check n-1, n, n+1
        for (ll dn = -2; dn <= 2; dn++) {
            ll nn = n + dn;
            if (nn < 1) continue;
            ll r = rects(m, nn);
            ll diff = llabs(r - T);
            if (diff < best_diff || (diff == best_diff && m * nn < best_area)) {
                best_diff = diff;
                best_area = m * nn;
            }
        }
    }

    cout << best_area << "\n";
    return 0;
}
