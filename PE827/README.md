# PE827 — Pseudoprime Nimbers（伪素数Nim）

来源：改编自 Project Euler Problem 827

## 原题意

将"伪素数"（pseudoprime，能通过某些素性测试的合数）与"Nimbers"（Nim 数 / Grundy 值）两个概念结合。在某种定义在自然数上的组合游戏中，计算那些合数但 Nim 值与素数相同的"伪素数 Nimber"的总和。

伪素数：例如 Fermat 伪素数（$2^{n-1} \equiv 1 \pmod{n}$ 的合数）、Carmichael 数（对所有互素底数都通过 Fermat 测试的合数）等。

PE 答案：34981821048。

## 算法

1. **Grundy 值计算**：对于因子游戏，$G(n) = \operatorname{mex}\{G(d) : d \mid n,\ 1 < d < n\}$，从底向上递推。
2. **素性检验**：使用 Miller-Rabin 算法确定性判断素数。
3. **伪素数识别**：检查合数是否满足 Fermat 小定理或更严格的条件。
4. **统计求和**：筛选出合数且 Nim 值等于素数 Nim 值的数，累加求和。

## 改编方向

1. 改变游戏的合法操作（如减去因子、乘以因子等）
2. 使用其他素性测试定义伪素数（Euler 伪素数、强伪素数）
3. 研究 Nim 值的分布规律
4. 在多堆 Nim 游戏中考察伪素数 Nimber
5. 引入不同进制或不同运算的变体游戏
