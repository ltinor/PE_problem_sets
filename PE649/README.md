# PE 649 — Low-Prime Chessboard Nim（小质数棋盘取石子游戏）

## 原题

[Project Euler #649](https://projecteuler.net/problem=649)

Alice 和 Bob 在 n×n 棋盘上玩取石子游戏，有 c 枚可区分的硬币。每次行动选取一枚硬币向左或向上移动 2、3、5 或 7 格（不能移出棋盘）。无法行动者输。Alice 先手，双方最优。

M(n, c) = Alice 能确保获胜的初始布局数。

已知：M(3, 1) = 4，M(3, 2) = 40，M(9, 3) = 450304。

求 M(10 000 019, 100) 的末 9 位数字。

**答案：924668016**

## 算法

- 策梅洛定理（Sprague-Grundy）：每个硬币独立移动，Grundy(x, y) = Grundy₁D(x) ⊕ Grundy₁D(y)。
- 一维 Grundy：Grundy₁D[k] = mex{Grundy₁D[k-a] : a ∈ {2,3,5,7}, a ≤ k}。
- 全局面 Grundy 为所有硬币 Grundy 值的异或。Alice 获胜当且仅当异或非零。
- 利用 Grundy 值的频数分布，通过 XOR 卷积动态规划统计异或为 0 的布局数（必败态）。
- 总布局数 = n^{2c} ≡ (n²)^c，必胜态 = 总布局数 - 必败态数。
- 答案对 10⁹ 取模（末 9 位）。

## 文件

| 文件 | 说明 |
|------|------|
| `code/std.cpp` | 标准解法（PE 模式输出答案，verify 模式验证样例） |

## 编译运行

```bash
g++ -std=c++17 -O2 code/std.cpp -o code/std
echo "PE" | ./code/std        # 输出 PE 答案
echo "verify" | ./code/std    # 验证已知样例
```
