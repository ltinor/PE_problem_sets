#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 944 暴力验证：枚举全部 2^n 个子集，按定义直接统计每个子集的 elevisor 和。
// 用于 check.sh 与 std.cpp 对拍（n <= 16）。

const ll MOD = 1234567891LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    if (!(cin >> n)) return 0;

    ll total = 0;
    for (ll mask = 0; mask < (1LL << n); mask++) {
        ll sev = 0;
        for (ll x = 1; x <= n; x++) {
            if (!(mask & (1LL << (x - 1)))) continue;
            bool is_el = false;
            for (ll y = 1; y <= n; y++) {
                if (y == x) continue;
                if ((mask & (1LL << (y - 1))) && y % x == 0) { is_el = true; break; }
            }
            if (is_el) sev += x;
        }
        total = (total + sev) % MOD;
    }
    cout << total << "\n";
    return 0;
}
