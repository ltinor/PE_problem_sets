#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 941（简单版本）：de Bruijn 组合锁 de Bruijn's Combination Lock
//
// 原题：C(10,12) 长度 10^12，且要算每个 12 位串在序列中的首次出现位置
//       （Lyndon 词排名）并对 10^7 个 LCG 生成的串求和，难度极大。
// 简单版本：缩数据到 k,n 很小（k^n <= 1e6），只要求输出字典序最小的
//           de Bruijn 序列 C(k,n) 本身。
//
// C(k,n) = 字典序最小的、包含所有 k^n 个 n 位串的最短序列。
// 验证点：C(3,2) = 0010211220。
//
// 算法：Fredricksen–Kessler–Maiorana（FKM）。
//  字典序最小的 de Bruijn 序列 = 所有「长度整除 n 的 Lyndon 词」按字典序
//  拼接，再取该周期串的前 k^n + n - 1 个字符。
//  用 Duval 算法按字典序生成所有长度 <= n 的 Lyndon 词（O(数量)）。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    if (!(cin >> k >> n)) return 0;

    // Duval 算法生成所有长度 <= n 的 Lyndon 词（字典序）
    vector<int> w = {-1};
    string concat;
    while (!w.empty()) {
        w.back()++;
        // 此时 w 是一个 Lyndon 词
        if (n % (int)w.size() == 0) {
            for (int d : w) concat.push_back(char('0' + d));
        }
        // 把 w 周期延拓到长度 n
        int m = (int)w.size();
        while ((int)w.size() < n) w.push_back(w[w.size() - m]);
        // 回退到下一个 Lyndon 词
        while (!w.empty() && w.back() == k - 1) w.pop_back();
    }

    // concat 的长度应为 k^n；取前 k^n + n - 1 个字符（周期拼接）
    ll total = 1;
    for (int i = 0; i < n; i++) total *= k;
    string ans;
    ans.reserve(total + n - 1);
    for (ll i = 0; i < total + n - 1; i++) ans.push_back(concat[i % concat.size()]);

    cout << ans << "\n";
    return 0;
}
