#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 945: XOR-Equation C / 异或方程（三）（简单版本）
//
// 原题：F(10^7)。
// 改编：读入 N (0 <= N <= 5000)，输出 F(N)。
//
// 方程 (a⊗a)⊕(2⊗a⊗b)⊕(b⊗b) = c⊗c，其中 ⊗ 为 GF(2)[x] 上的多项式乘法
// （无进位乘法）。
//
// 在 GF(2)[x] 中：
//   a⊗a = a(x)^2 = a(x^2)（只在偶次项有系数）
//   b⊗b = b(x^2)
//   2⊗a⊗b = x·a(x)·b(x)
//   c⊗c = c(x^2)
//
// 等式化为 a(x^2) ⊕ x·a(x)·b(x) ⊕ b(x^2) = c(x^2)。
// 奇数次数上，左端只有 x·a·b 的贡献，右端为 0，故要求 x·a·b 的奇次项系数为 0，
// 即 a⊗b 的所有偶数位置比特为 0。此时 c 由偶数位置唯一确定。
//
// 所以 F(N) = #{(a,b): 0<=a<=b<=N 且 (a⊗b) & 0x5555555555555555 == 0}。
//
// 验证点：F(10) = 21。

ll xor_mul(ll a, ll b) {
    ll result = 0;
    while (b) {
        if (b & 1) result ^= a;
        a <<= 1;
        b >>= 1;
    }
    return result;
}

bool ok(ll a, ll b) {
    ll prod = xor_mul(a, b);
    return (prod & 0x5555555555555555LL) == 0;
}

ll solve(ll N) {
    ll cnt = 0;
    for (ll a = 0; a <= N; a++)
        for (ll b = a; b <= N; b++)
            if (ok(a, b)) cnt++;
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N;
    if (!(cin >> N)) return 0;
    if (N < 0 || N > 5000) return 0;
    cout << solve(N) << "\n";
    return 0;
}
