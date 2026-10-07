#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;
int main() {
    const ll N = 20;
    vector<i128> dp(N+1, 0);
    vector<ll> cnt(N+1, 0);
    dp[0] = 1;
    for (ll part = 1; part <= N; part++)
        for (ll s = N; s >= part; s--)
            if (dp[s-part] > 0) {
                i128 val = dp[s-part] * part;
                if (val > dp[s]) { dp[s] = val; cnt[s] = cnt[s-part] + 1; }
            }
    for (ll n = 1; n <= N; n++)
        cout << "n=" << n << " f=" << (ll)dp[n] << " m=" << cnt[n] << " f*m=" << (ll)(dp[n]*cnt[n]) << endl;
    return 0;
}
