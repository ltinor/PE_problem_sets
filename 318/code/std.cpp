#include<bits/stdc++.h>
using namespace std;
#define ll long long

// N(p,q) = ceil(K / (-2 * log10(sqrt(q) - sqrt(p))))
// Need sqrt(q) - sqrt(p) < 1 for the condition to hold.
// This is equivalent to q - p < 2*sqrt(p) + 1, or roughly q < p + 2*sqrt(p).

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

            // Condition: (sqrt(q)-sqrt(p)) < 1
            if (diff >= 1.0L) continue;

            // C(p,q,n) >= K  <=>  -2n * log10(diff) >= K
            // n >= K / (-2 * log10(diff))
            // N(p,q) = ceil(K / (-2 * log10(diff)))
            long double logd = log10l(diff);
            if (logd >= 0) continue; // diff >= 1

            long double needed = (long double)K / (-2.0L * logd);
            ll Nval = (ll)ceill(needed - 1e-12L);
            if (Nval < 1) Nval = 1;

            ans += Nval;
        }
    }

    cout << ans << "\n";
    return 0;
}
