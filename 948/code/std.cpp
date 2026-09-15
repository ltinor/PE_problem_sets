#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 948: Left vs Right / 小左对小右（缩数据简单版）
//
// 原题：求 F(60)。缩数据版：读入 n (1 <= n <= 24)，输出 F(n)。
//
// 游戏：小左从单词左侧移除任意正数个（但不能全部）字母，小右从右侧移除。
// 最后剩一个字母：L 则小左胜，R 则小右胜。
// F(n) = 长度为 n 且"先手（无论谁先）必胜"的单词数量。
//
// 记 winL[w] = 小左先手时小左是否必胜；winR[w] = 小右先手时小右是否必胜。
// 递推（单词长 L，二进制编码，bit0 为最左字母，1 表示 'R'，0 表示 'L'）：
//   winL[w] = 存在 k∈[1,L-1] 使后缀 w[k:]（长 L-k）上 winR 为假；
//   winR[w] = 存在 k∈[1,L-1] 使前缀 w[:L-k]（长 L-k）上 winL 为假。
// 基（L=1）：winL = (字母为 L)，winR = (字母为 R)。
// F(n) = #{w : winL[w] && winR[w]}。
//
// 验证点：F(3)=4, F(8)=181。

const int MAX_N = 24;

ll solve(int n) {
    // winL[len][mask]、winR[len][mask]，len 从 1 到 n。
    vector<vector<unsigned char>> winL(n + 1), winR(n + 1);
    for (int len = 1; len <= n; len++) {
        int size = 1 << len;
        winL[len].assign(size, 0);
        winR[len].assign(size, 0);
        for (int mask = 0; mask < size; mask++) {
            if (len == 1) {
                winL[len][mask] = ((mask & 1) == 0) ? 1 : 0; // 字母为 L
                winR[len][mask] = ((mask & 1) == 1) ? 1 : 0; // 字母为 R
                continue;
            }
            unsigned char L = 0, R = 0;
            // 小左先手：移除 k 个左字母，剩后缀 mask >> k，要求其上小右不胜。
            for (int k = 1; k <= len - 1 && !L; k++) {
                int sub_len = len - k;
                int suffix = mask >> k;
                if (!winR[sub_len][suffix]) L = 1;
            }
            // 小右先手：移除 k 个右字母，剩前缀（最低 sub_len 位），要求其上小左不胜。
            for (int k = 1; k <= len - 1 && !R; k++) {
                int sub_len = len - k;
                int prefix = mask & ((1 << sub_len) - 1);
                if (!winL[sub_len][prefix]) R = 1;
            }
            winL[len][mask] = L;
            winR[len][mask] = R;
        }
    }
    ll cnt = 0;
    for (int mask = 0; mask < (1 << n); mask++)
        if (winL[n][mask] && winR[n][mask]) cnt++;
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    if (!(cin >> n)) return 0;
    if (n < 1 || n > MAX_N) return 0;
    cout << solve(n) << "\n";
    return 0;
}
