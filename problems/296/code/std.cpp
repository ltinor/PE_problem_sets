#include <bits/stdc++.h>
using namespace std;
#define ll long long

// PE 296 (简化版 / 缩数据版)
// ---------------------------------------------------------------
// 三角形 ABC，整数边长，设 BC=a, AC=b, AB=c，且 a <= b <= c。
// k 为角 ACB 的角平分线；m 为外接圆在 C 点的切线；n 为过 B 且平行于 m 的直线；
// E 为 n 与 k 的交点。
//
// 几何推导（详见 README）：BE = a*c / (a+b)。
// 因此 BE 为整数 <=> (a+b) | a*c。
// 令 g = gcd(a,b)，则 gcd(a, a+b) = g，故条件等价于 (a+b)/g | c。
//
// 计数：枚举 a,b（d=a+b），对满足
//        b <= c <= min(d-1, P-d)  且  m=(a+b)/gcd(a,b) | c
// 的 c 计数（即区间 [b, cmax] 内 m 的倍数个数）。

ll gcd_ll(ll a, ll b) { return b ? gcd_ll(b, a % b) : a; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll P;
    cin >> P;

    ll ans = 0;
    for (ll a = 1; a <= P / 2; ++a) {
        for (ll b = a; a + b + 1 <= P; ++b) {
            ll d = a + b;
            // 三角形条件 a+b>c => c <= d-1；周长 a+b+c<=P => c <= P-d
            ll cmax = min(d - 1, P - d);
            if (cmax < b) continue;          // 无满足 b<=c 的 c

            ll g = gcd_ll(a, b);
            ll m = d / g;                    // 需 m | c
            ll first = ((b + m - 1) / m) * m; // 区间内第一个 m 的倍数
            if (first <= cmax)
                ans += (cmax - first) / m + 1;
        }
    }

    cout << ans << "\n";
    return 0;
}
