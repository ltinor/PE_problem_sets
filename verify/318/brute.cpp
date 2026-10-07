#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: directly compute N(p,q) by checking C(p,q,n) >= K for increasing n
// Only feasible for small K

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    ll ans = 0;

    for (ll p = 1; p < K; p++) {
        for (ll q = p + 1; p + q <= K; q++) {
            long double sp = sqrtl((long double)p);
            long double sq = sqrtl((long double)q);
            long double diff = sq - sp;

            if (diff >= 1.0L) continue;

            // Find minimal n such that (diff)^(2n) <= 10^(-K)
            // i.e., 2n * (-log10(diff)) >= K
            // n >= K / (2 * (-log10(diff)))
            long double logd = log10l(diff);
            if (logd >= 0) continue;

            long double needed = (long double)K / (-2.0L * logd);
            ll Nval = (ll)ceill(needed - 1e-12L);
            if (Nval < 1) Nval = 1;

            ans += Nval;
        }
    }

    cout << ans << "\n";
    return 0;
}
