#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 937（缩数据版）暴力校验：直接对每个 k 用勒让德公式重算 v_p(k!)，无增量优化。
// 与 std.cpp 的公式一致但实现独立，用于 scripts/check.sh 交叉验证小数据。

const ll MOD = 1000000007LL;

bool isprime(int x) {
    if (x < 2) return false;
    for (int i = 2; (ll)i * i <= x; i++) if (x % i == 0) return false;
    return true;
}

ll vp(ll k, ll p) {
    ll s = 0, q = p;
    while (q <= k) { s += k / q; q *= p; }
    return s;
}

inline int pc(ll x) { return __builtin_popcountll(x) & 1; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    if (!(cin >> n)) return 0;
    if (n < 1) { cout << 0 << "\n"; return 0; }

    ll ans = 0, fact = 1;
    for (ll k = 1; k <= n; k++) {
        fact = fact * (k % MOD) % MOD;

        int par = pc(vp(k, 2));
        for (ll p = 3; p <= k; p++) {
            if ((p % 8 == 5 || p % 8 == 7) && isprime(p))
                par ^= pc(vp(k, p));
        }
        if (par == 0) ans = (ans + fact) % MOD;
    }

    cout << ans << "\n";
    return 0;
}
