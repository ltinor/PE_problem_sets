#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;
const ll MOD = 982451653;
int main() {
    const ll N = 100;
    vector<i128> dp(N+1, 0);
    vector<ll> cnt(N+1, 0);
    dp[0] = 1;
    for (ll part = 1; part <= N; part++)
        for (ll s = N; s >= part; s--)
            if (dp[s-part] > 0) {
                i128 val = dp[s-part] * part;
                if (val > dp[s]) { dp[s] = val; cnt[s] = cnt[s-part] + 1; }
            }
    i128 raw = 0;
    ll modsum = 0;
    for (ll n = 1; n <= N; n++) {
        raw += dp[n] * cnt[n];
        modsum = (modsum + (ll)(dp[n] % MOD) * (cnt[n] % MOD)) % MOD;
    }
    string s;
    i128 t = raw;
    if (t == 0) s = "0";
    else while (t) { s = char('0'+t%10) + s; t /= 10; }
    cout << "Raw total: " << s << endl;
    cout << "Mod total: " << modsum << endl;
    ll expected = (ll)((i128)1683550844462ULL % MOD);
    cout << "Expected mod: " << expected << endl;
    return 0;
}
