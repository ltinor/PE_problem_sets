#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// PE 962 (OJ 缩数据版): Angular Bisector and Tangent 2 / 角平分线与切线（二）
//
// 给定整数边长三角形 ABC，边长记为 a=BC, b=AC, c=AB，且满足 BC ≤ AC ≤ AB（即 a ≤ b ≤ c）。
// k 是 ∠ACB 的角平分线，m 是外接圆在 C 点的切线，n 是过 B 且平行于 m 的直线，E = n ∩ k。
// 求周长 a+b+c ≤ N 且 CE 为整数的三角形个数。
//
// 几何推导（以 C 为原点，角平分线方向为 x 轴正方向，令 ∠ACB = γ）：
//   A = (b·cos(γ/2), -b·sin(γ/2)),  B = (a·cos(γ/2), a·sin(γ/2))。
//   外接圆过原点，设为 x² + y² + u·x + v·y = 0，代入 A、B 解得
//     u = -(a+b)/(2·cos(γ/2)),  v = -(a-b)/(2·sin(γ/2))。
//   外接圆在 C 点的切线方程为 u·x + v·y = 0。
//   过 B 且平行于该切线的直线与 x 轴（角平分线）交于 E，解得
//     CE = 2·a²·cos(γ/2) / (a+b)。
//   又 cos²(γ/2) = ((a+b)² - c²) / (4ab)，故
//     CE² = a³·(a+b-c)·(a+b+c) / (b·(a+b)²)。
//   CE 为整数当且仅当该有理数约分后分母为 1 且分子为完全平方数。
//
// 枚举所有 a ≤ b ≤ c、a+b > c、a+b+c ≤ N 的三角形，逐一判断。

ull isqrt_ull(ull x) {
    if (x == 0) return 0;
    ull r = (ull)sqrt((long double)x);
    while (r > 0 && r * r > x) r--;
    while ((r + 1) * (r + 1) <= x) r++;
    return r;
}

bool ce_integral(ll a, ll b, ll c) {
    ll t = a + b;                      // ≤ 2N
    ull N1 = (ull)a * a * a * (ull)(t - c) * (ull)(t + c);
    ull D1 = (ull)b * (ull)t * (ull)t;
    ull g = std::gcd(N1, D1);
    ull P = N1 / g, Q = D1 / g;
    if (Q != 1) return false;          // CE² 不是整数
    ull r = isqrt_ull(P);
    return r * r == P;                 // CE² 为完全平方数 => CE 为整数
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll b = a; a + b + b <= N; b++) {          // 需 c ≥ b 且 a+b+c ≤ N
            ll cmax = min(a + b - 1, N - a - b);       // 三角形 a+b>c 且周长 ≤ N
            for (ll c = b; c <= cmax; c++) {
                if (ce_integral(a, b, c)) ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
