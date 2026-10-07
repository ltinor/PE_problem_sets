#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;
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
    i128 total = 0;
    for (ll n = 1; n <= N; n++) total += dp[n] * cnt[n];
    // Print as string since cout might not support __int128
    string s;
    if (total == 0) s = "0";
    else while (total) { s = char('0'+total%10) + s; total /= 10; }
    cout << s << endl;
    return 0;
}
