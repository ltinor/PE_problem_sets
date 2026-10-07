#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 945（简单版本）：XOR-Equation C / 异或方程（三）
//
// 原题：求 F(10^7)。
// 改编（缩数据）：读入 N (0 <= N <= 5000)，输出 F(N)。
//
// ⊗ 为 GF(2)[x] 上的多项式乘法（无进位乘法 / carryless multiplication）：
//   x⊗y = ⊕_{i: bit_i(y)=1} (x << i)。
// 例如 7⊗3 = 111_2 ⊗ 11_2 = 1001_2 = 9。
//
// 方程 (a⊗a)⊕(2⊗a⊗b)⊕(b⊗b) = c⊗c。
// 在 GF(2)[x] 中：a⊗a = a(x)^2 = a(x^2)，b⊗b = b(x^2)，c⊗c = c(x^2)，
// 三者均只含偶次项；而 2⊗a⊗b = x·a(x)·b(x)（2 只有第 1 位是 1，故 2⊗a = a<<1）。
// 等式化为 a(x^2) ⊕ x·a(x)·b(x) ⊕ b(x^2) = c(x^2)。
// 奇次项上右端为 0，故要求 x·a·b 的奇次项系数为 0，即 a⊗b 的偶数位置比特全为 0；
// 此时 c 由偶次项唯一确定。于是
//   F(N) = #{(a,b): 0 <= a <= b <= N 且 (a⊗b) & 0x5555555555555555 == 0}。
//
// 验证点：F(10) = 21。

ll xor_mul(ll a, ll b) {
    ll r = 0;
    while (b) {
        if (b & 1) r ^= a;
        a <<= 1;
        b >>= 1;
    }
    return r;
}

bool ok(ll a, ll b) {
    return (xor_mul(a, b) & 0x5555555555555555LL) == 0;
}

ll solve(ll N) {
    ll cnt = 0;
    for (ll a = 0; a <= N; a++)
        for (ll b = a; b <= N; b++)
            if (ok(a, b)) cnt++;
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    if (!(cin >> N)) return 0;
    if (N < 0 || N > 5000) return 0;
    cout << solve(N) << "\n";
    return 0;
}
