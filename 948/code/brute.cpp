#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 948 缩数据版 暴力对拍：直接按游戏定义递归（带记忆化）。
// bit0 为最左字母，1 表示 'R'，0 表示 'L'。
// 返回 {小左先手是否必胜, 小右先手是否必胜}。

map<pair<int, int>, pair<int, int>> memo;

pair<int, int> solve_word(int mask, int len) {
    if (len == 1) {
        int bit = mask & 1;
        return {(bit == 0) ? 1 : 0, (bit == 1) ? 1 : 0};
    }
    auto key = make_pair(len, mask);
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;

    int L = 0, R = 0;
    // 小左先手：移除 k 个左字母，剩后缀，要求小右不胜。
    for (int k = 1; k <= len - 1 && !L; k++)
        if (!solve_word(mask >> k, len - k).second) L = 1;
    // 小右先手：移除 k 个右字母，剩前缀，要求小左不胜。
    for (int k = 1; k <= len - 1 && !R; k++)
        if (!solve_word(mask & ((1 << (len - k)) - 1), len - k).first) R = 1;

    return memo[key] = {L, R};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    if (!(cin >> n)) return 0;
    ll cnt = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        auto p = solve_word(mask, n);
        if (p.first && p.second) cnt++;
    }
    cout << cnt << "\n";
    return 0;
}
