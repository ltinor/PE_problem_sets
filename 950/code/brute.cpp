#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute / reference implementation for PE 950 (simple version).
// Same game logic as std.cpp but uses long double arithmetic (p = 1/sqrtl(m))
// and a plain sorted vector of survivor coins, serving as an independent check.

int main() {
    ll N, C, m;
    if (!(cin >> N >> C >> m)) return 0;

    long double p = 1.0L / sqrtl((long double)m);

    vector<ll> coins = {C};   // coins held by survivors
    ll w = 0;                 // doomed count
    ll c = C;                 // c(1)
    ll ans = c + w;

    for (ll n = 2; n <= N; ++n) {
        ll free_votes = 1 + w;
        ll need = (n + 1) / 2;
        ll votes = need - free_votes;

        if (votes <= 0) {
            c = C;
            w = 0;
            coins.assign(n, 0);
            coins[0] = C;
        } else {
            // D = ceil(p * (1+w)); p irrational -> ceil == floor + 1
            ll D = (ll)ceill(p * (long double)(1 + w));
            sort(coins.begin(), coins.end());
            ll S = 0;
            for (ll i = 0; i < votes; ++i) S += coins[i];
            ll total = S + votes * D;

            if (total <= C) {
                c = C - total;
                w = 0;
                vector<ll> nf;
                nf.reserve(n);
                nf.push_back(C - total);
                for (ll i = 0; i < votes; ++i) nf.push_back(coins[i] + D);
                for (ll i = 0; i < n - 1 - votes; ++i) nf.push_back(0);
                coins.swap(nf);
            } else {
                w = 1 + w;
                // c unchanged, coins unchanged
            }
        }
        ans += c + w;
    }

    cout << ans << "\n";
    return 0;
}
