#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 945 暴力验证（独立于 std 的约化）：
// 直接按原方程判定：对每对 (a,b) 计算
//   L = (a⊗a) ⊕ (2⊗a⊗b) ⊕ (b⊗b)
// 若存在整数 c 使 L = c⊗c，则计数 +1。
// 由于 c⊗c 只含偶次项，L = c⊗c 成立 ⇔ L 的所有奇数位置比特为 0。
// 这一判定不依赖“a⊗b 偶数位为 0”的推导，用于与 std.cpp 对拍。

ll xor_mul(ll a, ll b) {
    ll r = 0;
    while (b) {
        if (b & 1) r ^= a;
        a <<= 1;
        b >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    if (!(cin >> N)) return 0;

    ll cnt = 0;
    for (ll a = 0; a <= N; a++) {
        for (ll b = a; b <= N; b++) {
            // 2⊗a⊗b = (2⊗a)⊗b = (a<<1)⊗b
            ll L = xor_mul(a, a) ^ xor_mul(a << 1, b) ^ xor_mul(b, b);
            if ((L & 0xAAAAAAAAAAAAAAAALL) == 0) cnt++;
        }
    }
    cout << cnt << "\n";
    return 0;
}
