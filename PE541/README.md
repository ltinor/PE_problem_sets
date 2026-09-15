# PE541 - 和谐数分母的整除性 (Divisibility of Harmonic Number Denominators)

来源：改编自 Project Euler Problem 541

## 原题意

第 n 个**和谐数** H_n 定义为前 n 个正整数的倒数和，可写成最简分数 a_n / b_n：
$$H_n = \sum_{k=1}^n \frac{1}{k} = \frac{a_n}{b_n}, \quad \gcd(a_n, b_n) = 1$$

令 M(p) 为使得 b_n 不能被素数 p 整除的最大的 n。

例如 M(3) = 68，因为 H_68 的分母不能被 3 整除，但所有更大的和谐数的分母都能被 3 整除。
已知 M(7) = 719102。求 M(137)。

PE 答案：4580726482872451。

## 题目

给定素数 p，求 M(p)——最大的 n 使得 H_n 的最简分母不被 p 整除。

## 算法

- H_n ∈ Z_p（p-adic 整数）当且仅当分母不被 p 整除。
- 利用 p-adic 展开：H_n = Σ_{j≥0} p^{-j} · G(⌊n/p^j⌋)，其中 G(m) = Σ_{k=1, p∤k}^m 1/k。
- G(m) ∈ Z_p，其 p-adic 位数取决于 m 的进制表示。
- 通过 p-adic 条件转化为对 n 的 p 进制位数的 DP 约束：
  - g_0(m) = G(m) mod p（周期 p，仅取决于 m mod p）
  - g_1(m) = ⌊m/p⌋ · V mod p，其中 V = (H_{p-1}/p) mod p（Wolstenholme 常数）
- 从低位到高位进行 DP，跟踪 p-adic 进位状态，搜索最大合法 n。

## 改编方向

1. **不同素数**：计算 M(p) 对更大的素数或一系列素数。
2. **部分和**：求 Σ_{p≤P} M(p) 或 Σ M(p) mod m。
3. **分母条件**：求使得分母被 p 整除的最小 n。
4. **通项研究**：分析 M(p) 的渐近行为或与 Wolstenholme 素数的关系。
