#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 暴力实现（独立写法）：对每个 n 用试除法分解质因数，
// 计算奇数次质因子的异或，异或为 0 则计入答案。

ll nim_value(ll n) {
    ll x = 0;
    for (ll p = 2; p * p <= n; p++) {
        int cnt = 0;
        while (n % p == 0) { n /= p; cnt++; }
        if (cnt & 1) x ^= p;
    }
    if (n > 1) x ^= n;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    if (!(cin >> N)) return 0;

    ll ans = 0;
    for (ll n = 1; n <= N; n++)
        if (nim_value(n) == 0) ans += n;

    cout << ans << "\n";
    return 0;
}
