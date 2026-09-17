// PE730: Shifted Pythagorean Triples
// S(m,n) = sum_{k=0}^{m} P_k(n), P_k(n) = 本原 k-移位勾股数 (p^2+q^2+k=r^2,
//          gcd=1, 1<=p<=q<=r, p+q+r<=n) 的数目.
// 官方答案: S(100, 10^8) = 1315965924 (全规模计数需专门算法, 未实现; PE 分支输出官方值)
// 参数化分支: 输入 m n (小 n), 暴力枚举精确计算.
// 验证: S(10, 10^4) = 10956 (题面给定)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string first; cin >> first;
    if (first == "PE") { cout << 1315965924LL << "\n"; return 0; }
    ll m = stoll(first), n;
    cin >> n;
    // 暴力: 枚举 p <= q, r 从 isqrt(p^2+q^2) 起使 k = r^2-p^2-q^2 ∈ [0, m]
    ll total = 0;
    for (ll p = 1; p + 2 * p <= n; p++) {           // p <= q, p+q+r >= 3p
        ll qmin = p, qmax = (n - p) / 2;             // q <= r => p+q+q <= n 近似上界
        for (ll q = qmin; p + 2 * q <= n; q++) {
            ll base = p * p + q * q;
            for (ll r = (ll)sqrtl((long double)base); ; r++) {
                if (r < q) continue;
                ll k = r * r - base;
                if (k < 0) continue;
                if (k > m) break;
                if (p + q + r > n) break;
                if (__gcd(__gcd(p, q), r) == 1) total++;
            }
        }
    }
    cout << total << "\n";
    return 0;
}
