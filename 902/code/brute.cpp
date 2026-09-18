// PE902 暴力 (定义直译, 小 m): 枚举 pi^k (k=1..m!), Lehmer O(n^2) 求 rank 累加.
// 验证 P(2)=4, P(3)=780, P(4)=38810300; 与 std 闭式算法对拍.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll m;
    if (!(cin >> m)) return 0;
    ll n = m * (m + 1) / 2;
    vector<ll> sig(n + 1);
    for (ll i = 1; i <= n; i++) {
        ll k = (ll)((sqrtl(8.0L * i + 1) - 1) / 2);
        if (k * (k + 1) / 2 == i) sig[i] = k * (k - 1) / 2 + 1;
        else sig[i] = i + 1;
    }
    vector<ll> tau(n + 1), tinv(n + 1);
    for (ll i = 1; i <= n; i++) { tau[i] = (1000000007LL % n) * (i % n) % n + 1; tinv[tau[i]] = i; }
    vector<ll> pi(n + 1);
    for (ll i = 1; i <= n; i++) pi[i] = tinv[sig[tau[i]]];

    ll fact = 1; for (ll i = 2; i <= m; i++) fact *= i;
    vector<ll> cur(n + 1); for (ll i = 1; i <= n; i++) cur[i] = i;
    unsigned long long total = 0; // mod 1e9+7 逐步取模
    for (ll k = 1; k <= fact; k++) {
        for (ll i = 1; i <= n; i++) cur[i] = pi[cur[i]];
        ll rank = 1, f = 1;
        for (ll i = n; i >= 1; i--) {
            ll c = 0;
            for (ll j = i + 1; j <= n; j++) if (cur[j] < cur[i]) c++;
            rank = (rank + c % 1000000007LL * f) % 1000000007LL;
            f = f * (n - i + 1) % 1000000007LL;
        }
        total = (total + rank) % 1000000007LL;
    }
    cout << total % 1000000007LL << "\n";
    return 0;
}
