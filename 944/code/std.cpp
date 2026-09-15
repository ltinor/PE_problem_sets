#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 944（简单版本）：元素因数之和 Sum of Elevisors
//
// 原题：S(10^14) mod 1234567891，需要 O(sqrt(n)) 整除分块 + 费马小定理。
// 简单版本：缩数据到 n <= 1e7，仍用同一条 O(sqrt(n)) 公式，秒出。
//
// 线性性：S(n) = Σ_x x * (#{E 含 x 且 x 是 elevisor})
//   x 是 elevisor ⇔ 存在 y∈E,y≠x 且 x|y
//   含 x 的总子集数 2^{n-1}；含 x 但无其它倍数的子集数 2^{n-floor(n/x)}
//   ⇒ S(n) = 2^{n-1}·n(n+1)/2 - Σ_{x=1..n} x·2^{n-floor(n/x)}
//
// 验证点：S(10)=4927。
//
// 第二项用整除分块（floor(n/x) 只有 O(sqrt n) 段）：
//   对 v = floor(n/i)，令 j = floor(n/v)，则 x∈[i,j] 都满足 floor(n/x)=v。

const ll MOD = 1234567891LL;  // 质数，用费马小定理约化指数

ll pow_mod(ll base, ll exp) {
    ll r = 1;
    base %= MOD;
    while (exp) {
        if (exp & 1) r = (i128)r * base % MOD;
        base = (i128)base * base % MOD;
        exp >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    if (!(cin >> n)) return 0;

    auto pow2 = [&](ll e) -> ll { return pow_mod(2, e % (MOD - 1)); };

    ll first = (ll)((i128)pow2(n - 1) * (((i128)n * (n + 1) / 2) % MOD) % MOD);

    ll second = 0;
    for (ll i = 1; i <= n;) {
        ll v = n / i;
        ll j = n / v;                       // [i,j] 内 floor(n/x) 均为 v
        i128 sx = (i128)(i + j) * (j - i + 1) / 2;
        second = (second + (ll)((sx % MOD) * pow2(n - v) % MOD)) % MOD;
        i = j + 1;
    }

    ll ans = ((first - second) % MOD + MOD) % MOD;
    cout << ans << "\n";
    return 0;
}
