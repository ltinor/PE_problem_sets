#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 956: Super Duper Sum / 超级无敌和  (简单版本 / simple version)
//
// 原题：求 D(1000★, 1000) mod 999999001（涉及超级无敌阶乘与单位根过滤，计算量巨大）。
// 简单版本：直接给定 n 与 m，求 D(n, m)。
//
// 定义：
//   Ω(n)：n 的质因数个数（含重复）。
//   D(n, m)：n 的所有满足 Ω(d) 能被 m 整除的因数 d 之和。
//
// 例：D(24, 3) = 1 + 8 + 12 = 21（Ω(1)=0, Ω(8)=3, Ω(12)=3 均能被 3 整除）。
//
// 算法（因数枚举）：
//   1. 对 n 做质因数分解（试除法到 sqrt(n)），得到 (p_i, e_i)；
//   2. 枚举所有因数 d = Π p_i^{f_i} (0<=f_i<=e_i)；
//   3. 对每个因数 d，Ω(d) = Σ f_i，若 Ω(d) % m == 0 则累加 d。
//
// 验证点：D(24, 3) = 21。
//
// 缩数据范围：1 <= n <= 10^6，1 <= m <= 100。

ll D(ll n, ll m) {
    // 质因数分解
    vector<ll> primes, exps;
    ll x = n;
    for (ll p = 2; p * p <= x; p++) {
        if (x % p == 0) {
            ll e = 0;
            while (x % p == 0) { x /= p; e++; }
            primes.push_back(p);
            exps.push_back(e);
        }
    }
    if (x > 1) { primes.push_back(x); exps.push_back(1); }

    // 枚举所有因数，累加满足条件的
    ll total = 0;
    int np = primes.size();
    function<void(int, ll, ll)> dfs = [&](int i, ll cur, ll omega) {
        if (i == np) {
            if (omega % m == 0) total += cur;
            return;
        }
        ll p = primes[i];
        ll pw = 1;
        for (ll f = 0; f <= exps[i]; f++) {
            dfs(i + 1, cur * pw, omega + f);
            pw *= p;
        }
    };
    dfs(0, 1, 0);
    return total;
}

void verify() {
    cout << "PE 956: Super Duper Sum / 超级无敌和  (简单版本)\n\n";

    // 手算验证 D(24,3)：24 的因数 1,2,3,4,6,8,12,24，
    // Ω 分别为 0,1,1,2,2,3,3,4，能被 3 整除的是 1,8,12 -> 和为 21。
    cout << "=== 验证点 ===\n";
    cout << "D(24, 3) = " << D(24, 3) << "（期望 21）"
         << (D(24, 3) == 21 ? "  ✓" : "  ✗") << "\n\n";

    // 额外对照
    cout << "=== 额外对照 ===\n";
    vector<pair<pair<ll,ll>,ll>> cases = {
        {{24, 1}, 60},   // 所有因数之和 σ(24) = 60
        {{24, 2}, 21},   // Ω 偶数的因数：1,4,6,24 -> 35? 见下
    };
    // D(24,1)=σ(24)=1+2+3+4+6+8+12+24=60
    cout << "D(24, 1) = " << D(24, 1) << "（σ(24)=60）\n";
    // Ω 能被 2 整除：Ω=0(1),2(4),2(6),4(24) -> 1+4+6+24=35
    cout << "D(24, 2) = " << D(24, 2) << "（1+4+6+24=35）\n";
    cout << "D(24, 4) = " << D(24, 4) << "（Ω 能被 4 整除：1(0),24(4) -> 1+24=25）\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string line;
    if (!getline(cin, line)) return 0;

    if (line == "verify") { verify(); return 0; }

    // 参数化：读入 n m，输出 D(n, m)。
    ll n, m;
    stringstream ss(line);
    if (!(ss >> n >> m)) {
        cout << "用法: 输入两个整数 n m，输出 D(n, m)。\n";
        cout << "或输入 'verify' 运行验证。\n";
        return 0;
    }
    cout << D(n, m) << "\n";
    return 0;
}
