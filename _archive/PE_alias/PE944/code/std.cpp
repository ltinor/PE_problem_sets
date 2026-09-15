#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 944: Sum of Elevisors / 元素因数之和（简单版本）
//
// 原题：S(10^14) mod 1234567891。
// 改编：读入 n (1 <= n <= 2000000)，输出 S(n) mod 1234567891。
//
// 推导（线性性）：
//   对固定 x，x 是 E 的元素因数当且仅当 x∈E 且存在 E 中另一个元素是 x 的倍数。
//   含 x 的子集总数 = 2^{n-1}。
//   x 不是元素因数：x 的所有真倍数（⌊n/x⌋-1 个）都不在 E 中，
//   此时自由选择的元素数为 n - ⌊n/x⌋，子集数为 2^{n-⌊n/x⌋}。
//   所以 x 是元素因数的子集数 = 2^{n-1} - 2^{n-⌊n/x⌋}。
//
//   S(n) = Σ_{x=1}^{n} x · (2^{n-1} - 2^{n-⌊n/x⌋})  (mod 1234567891)。
//
// 验证点：S(10) = 4927。

const ll MOD = 1234567891LL;

ll solve(ll n) {
    vector<ll> pow2(n + 1);
    pow2[0] = 1;
    for (ll i = 1; i <= n; i++) pow2[i] = (i128)pow2[i - 1] * 2 % MOD;

    ll ans = 0;
    for (ll x = 1; x <= n; x++) {
        ll term = (pow2[n - 1] - pow2[n - n / x] + MOD) % MOD;
        ans = (ans + (i128)(x % MOD) * term) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n;
    if (!(cin >> n)) return 0;
    if (n < 1 || n > 2000000) return 0;
    cout << solve(n) << "\n";
    return 0;
}
