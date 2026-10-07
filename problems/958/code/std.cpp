#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 958: Euclid's Labour / 欧几里得的劳作  (简单版本 / simple version)
//
// 原题：求 f(10^12 + 39)（需要 Stern-Brocot / 连分数等高效方法）。
// 简单版本：给定 n（小），直接暴力枚举 m 求 f(n)。
//
// 定义：
//   欧几里得算法（减法版）：每一步从较大数中减去较小数，直到两数相等。
//   d(n, m)：计算 gcd(n, m) 所用的减法次数。
//   f(n)：与 n 互质且使 d(n, m) 最小的正整数 m（若有多个取最小）。
//
// 算法（暴力枚举）：
//   - d(n, m) 可用除法加速：减法次数 = Σ 欧几里得除法商之和 - 1
//     （对互质的 n,m，最后一步只差 1 次减法）。
//   - 枚举 m = 1..n-1，对 gcd(n,m)==1 的 m 求 d(n,m)，取最小值对应的最小 m。
//   - 复杂度 O(n log n)。
//
// 验证点：f(7) = 2（d=4 步），f(89) = 34，f(8191) = 1856。
//
// 缩数据范围：1 <= n <= 10^6。

// 欧几里得算法商之和（等价于减法步数 + 1，对互质情况）
ll qsum(ll n, ll m) {
    if (m > n) swap(n, m);
    ll s = 0;
    while (m > 0) {
        s += n / m;
        ll r = n % m;
        n = m;
        m = r;
    }
    return s;
}

// 真正的减法次数（互质时 = qsum - 1）
ll d(ll n, ll m) {
    return qsum(n, m) - 1;
}

// f(n)：与 n 互质且使 d(n,m) 最小的最小 m
ll f(ll n) {
    ll best_m = -1, best_d = LLONG_MAX;
    for (ll m = 1; m < n; m++) {
        if (gcd(m, n) == 1) {
            ll s = qsum(n, m);   // 最小化 qsum 等价于最小化 d
            if (s < best_d) {
                best_d = s;
                best_m = m;
            }
        }
    }
    return best_m;
}

void verify() {
    cout << "PE 958: Euclid's Labour / 欧几里得的劳作  (简单版本)\n\n";
    cout << "=== 验证点 ===\n";
    ll f7 = f(7);
    cout << "f(7) = " << f7 << "（期望 2）" << (f7 == 2 ? "  ✓" : "  ✗")
         << "，d(7," << f7 << ") = " << d(7, f7) << " 步（题面：至少 4 步）\n";
    ll f89 = f(89);
    cout << "f(89) = " << f89 << "（期望 34）" << (f89 == 34 ? "  ✓" : "  ✗")
         << "，d(89," << f89 << ") = " << d(89, f89) << " 步\n";
    ll f8191 = f(8191);
    cout << "f(8191) = " << f8191 << "（期望 1856）" << (f8191 == 1856 ? "  ✓" : "  ✗")
         << "，d(8191," << f8191 << ") = " << d(8191, f8191) << " 步\n\n";

    cout << "=== n=7 的 d(7,m) 明细 ===\n";
    for (ll m = 1; m < 7; m++) {
        if (gcd(m, 7) == 1)
            cout << "  d(7," << m << ") = " << d(7, m) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string line;
    if (!getline(cin, line)) return 0;

    if (line == "verify") { verify(); return 0; }

    ll n;
    stringstream ss(line);
    if (!(ss >> n) || n < 2) {
        cout << "用法: 输入整数 n (2<=n<=1000000)，输出 f(n)。\n";
        cout << "或输入 'verify' 运行验证。\n";
        return 0;
    }
    cout << f(n) << "\n";
    return 0;
}
