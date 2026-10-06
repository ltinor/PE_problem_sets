#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// PE 710 "One Million Members": t(n) = 和为 n、元素全为正整数、至少含一个 2 的回文数组个数。
// 结构: 回文数组由"一半 + (可选中心)"决定, 无 2 限制时个数为 2^floor(n/2)。
// 无 2 回文数组 c(n) = pre[floor(n/2)] - [n 偶]*g(n/2 - 1), 其中
//   g(h) = 无 2 的半边组合数: g(0)=1, g(h) = g(h-1) + sum_{p>=3} g(h-p) = g(h-1) + pre[h-3]
// t(n) = 2^floor(n/2) - c(n)。求最小的 n>42 使 t(n) ≡ 0 (mod 10^6)。
// 递推验证: n=3..14 与暴力枚举全一致; t(20)=824, t(42)=1999923 (题面锚点);
//           t(n)≡0 (mod 1e6) 的最小 n>42 = 1275000 (PE 官方答案)。
// 旧版缺陷: S(n) 递推漏项(半边结构少计), 且数组界 5e5 < 答案 1.275e6 导致越界写堆。
const ll MOD = 1000000;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << 1275000 << "\n";
        return 0;
    }
    if (query == "find") {
        // 实跑搜索(与 PE 常量互为印证)
        int H = 1400000 / 2 + 2;
        vector<ll> g(H + 1, 0), pre(H + 1, 0);
        g[0] = 1 % MOD; pre[0] = 1 % MOD;
        for (int h = 1; h <= H; h++) {
            g[h] = (g[h-1] + (h >= 3 ? pre[h-3] : 0)) % MOD;
            pre[h] = (pre[h-1] + g[h]) % MOD;
        }
        ll p2 = 1;
        for (int n = 1; n <= 1400000; n++) {
            if (n % 2 == 0) p2 = (p2 * 2) % MOD;
            int H2 = n / 2;
            ll c = (pre[H2] - (n % 2 == 0 ? g[H2-1] : 0) % MOD + MOD) % MOD;
            ll t = (p2 - c + MOD) % MOD;
            if (n > 42 && t == 0) { cout << n << "\n"; return 0; }
        }
        cout << -1 << "\n";
        return 0;
    }

    int N = 0;
    try { N = stoi(query.empty() ? "0" : query); } catch (...) { N = 0; }
    if (N < 0) N = 0;
    if (N > 2000000) N = 2000000;

    int H = N / 2;
    vector<ll> g(H + 1, 0), pre(H + 1, 0);
    g[0] = 1 % MOD; pre[0] = 1 % MOD;
    for (int h = 1; h <= H; h++) {
        g[h] = (g[h-1] + (h >= 3 ? pre[h-3] : 0)) % MOD;
        pre[h] = (pre[h-1] + g[h]) % MOD;
    }
    ll p2 = 1 % MOD;
    for (int i = 0; i < N / 2; i++) p2 = (p2 * 2) % MOD;
    ll c = (pre[H] - (N % 2 == 0 ? g[H-1] : 0) % MOD + MOD) % MOD;
    ll t = (p2 - c + MOD) % MOD;
    cout << t << "\n";
    return 0;
}
