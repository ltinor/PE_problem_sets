#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 961 (OJ 缩数据版): Removing Digits / 删除数字
//
// 两位玩家轮流从一个正整数中删除一个数字；每次删除后产生的前导零一并去掉。
// 删除最后一个非零数字（即把数变成 0）的玩家获胜。
//
// W(N) = 小于 N 且双方最优策略下先手必胜（Grundy 值 != 0）的正整数个数。
// 原题求 W(10^18)；本题为缩数据版，N <= 1e6，直接 DP 计算 Grundy 值。
//
// 模型：普通 play 的无偏博弈，终止态为 0（无法再动，即上一步已获胜）。
//   g(0) = 0
//   g(n) = mex{ g(m) : m 为删除 n 的某一位并去掉前导零后的结果 }
// 删除一位后数字严格变小，故可按 n 递增顺序 DP。
// 每一位的删除结果用整数运算得到：删除第 i 位（自低位起，i 从 0 开始）
//   m = (n / 10^(i+1)) * 10^i + (n % 10^i)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    if (!(cin >> N)) return 0;

    vector<int> g(N, 0);   // g[n] = Grundy 值，g[0] = 0
    ll ans = 0;

    for (ll n = 1; n < N; n++) {
        bool seen[64] = {false};
        for (ll pw = 1; pw <= n; pw *= 10) {
            ll high = n / (pw * 10);
            ll low = n % pw;
            ll m = high * pw + low;   // 删除第 log10(pw) 位后的结果
            seen[g[m]] = true;
        }
        int mex = 0;
        while (seen[mex]) mex++;
        g[n] = mex;
        if (mex != 0) ans++;
    }

    cout << ans << "\n";
    return 0;
}
