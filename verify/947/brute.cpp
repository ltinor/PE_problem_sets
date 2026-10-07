#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 947 缩数据版 暴力对拍：对每个 m、每个 (a,b) 直接迭代求周期。
// 复杂度 O(M^4)，仅用于小 M 对拍验证 std。

const ll MOD = 999999893LL;

ll period(ll a, ll b, ll m) {
    ll x = a, y = b;
    ll bound = 6 * m + 10; // Pisano 周期上界 π(m) <= 6m
    for (ll n = 1; n <= bound; n++) {
        ll z = (x + y) % m;
        x = y;
        y = z;
        if (x == a && y == b) return n;
    }
    return 1; // m=1 时只有 (0,0)，周期为 1
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll M;
    if (!(cin >> M)) return 0;
    ll ans = 0;
    for (ll m = 1; m <= M; m++) {
        for (ll a = 0; a < m; a++) {
            for (ll b = 0; b < m; b++) {
                ll p = period(a, b, m);
                ans = (ans + (__int128)p * p) % MOD;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
