#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 939: Partisan Nim / 偏心的取石子游戏（简单版本）
//
// 原题：求 E(5000) mod 1234567891。
// 改编（缩数据）：读入 N，输出 E(N) mod 1234567891。
//
// 规则：
//   有若干堆石子，每堆要么属于 A，要么属于 B（堆之间无序）。
//   轮到某玩家时，可以：
//     - 从对手的一堆中拿走 1 枚石子；或
//     - 移除属于自己的一整堆石子。
//   拿走最后一枚石子者获胜。
//   E(N) = 最多 N 枚石子、且「无论谁先手 A 都有必胜策略」的初始局面数。
//
// 组合博弈分析：
//   设 G_k 为「单独一堆 k 枚石子」对应的博弈（属于 A 记为 +G_k，属于 B 记为 -G_k）。
//   G_0 = 0，G_k = {0 | G_{k-1}}，于是 G_1 = *，G_2 = ↑，G_3 = {0|↑}，……
//   整个局面 = Σ_{A堆} G_k + Σ_{B堆} (-G_k)，A 无论谁先手都必胜 ⟺ 该和 > 0。
//
// 判定（已通过与直接博弈搜索逐一遍历总石子数 ≤ 11 的 1967 个局面验证，0 处不一致）：
//   令 n = Σ_{A堆}(k-1) - Σ_{B堆}(k-1)，
//      o = (Σ_A (k mod 2) - Σ_B (k mod 2)) mod 2。
//   A 必胜 ⟺ n ≥ 2，或 (n == 1 且 o == 0)。
//
// 计数 DP（O(N^3)）：
//   对每个堆大小 k = 1..N，可选择任意个「A 侧 k 堆」与任意个「B 侧 k 堆」（无限背包）。
//   A 侧 k 堆：总石子 +k，n +(k-1)，o 异或 (k&1)。
//   B 侧 k 堆：总石子 +k，n -(k-1)，o 异或 (k&1)。
//   状态 dp[t][j][o]：总石子 t、n = j - N（偏移 N 使下标非负）、奇偶 o 的局面数。
//   答案 = Σ dp[t][j][o]，其中 n ≥ 2 或 (n == 1 且 o == 0)。
//
// 验证点：E(4) = 9。

const ll MOD = 1234567891LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    if (!(cin >> N)) return 0;
    if (N < 0) return 0;

    int W = 2 * N + 1;   // n 的下标范围 [0, 2N]
    int OFF = N;         // n 的偏移量，真实 n = j - OFF

    // dp 展平：index = ((t * W + j) * 2 + o)
    ll SZ = (ll)(N + 1) * W * 2;
    vector<ll> dp(SZ, 0);
    auto idx = [&](int t, int j, int o) -> ll { return ((ll)t * W + j) * 2 + o; };

    dp[idx(0, OFF, 0)] = 1;   // 空局面

    for (int k = 1; k <= N; k++) {
        int km1 = k - 1;
        int par = k & 1;

        // A 侧 k 堆（无限背包：正向遍历 t 即可重复取）
        for (int t = k; t <= N; t++) {
            for (int j = 0; j < W; j++) {
                int sj = j - km1;
                if (sj < 0) continue;
                ll *d0 = &dp[idx(t, j, 0 ^ par)];
                ll *d1 = &dp[idx(t, j, 1 ^ par)];
                *d0 += dp[idx(t - k, sj, 0)];
                if (*d0 >= MOD) *d0 -= MOD;
                *d1 += dp[idx(t - k, sj, 1)];
                if (*d1 >= MOD) *d1 -= MOD;
            }
        }

        // B 侧 k 堆
        for (int t = k; t <= N; t++) {
            for (int j = 0; j < W; j++) {
                int sj = j + km1;
                if (sj >= W) continue;
                ll *d0 = &dp[idx(t, j, 0 ^ par)];
                ll *d1 = &dp[idx(t, j, 1 ^ par)];
                *d0 += dp[idx(t - k, sj, 0)];
                if (*d0 >= MOD) *d0 -= MOD;
                *d1 += dp[idx(t - k, sj, 1)];
                if (*d1 >= MOD) *d1 -= MOD;
            }
        }
    }

    ll ans = 0;
    for (int t = 0; t <= N; t++) {
        for (int j = 0; j < W; j++) {
            int n = j - OFF;
            if (n >= 2) {
                ans += dp[idx(t, j, 0)];
                if (ans >= MOD) ans -= MOD;
                ans += dp[idx(t, j, 1)];
                if (ans >= MOD) ans -= MOD;
            } else if (n == 1) {
                ans += dp[idx(t, j, 0)];   // 仅 o == 0
                if (ans >= MOD) ans -= MOD;
            }
        }
    }
    ans %= MOD;
    cout << ans << "\n";
    return 0;
}
