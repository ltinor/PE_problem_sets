# PE739 — Summation of Summations (求和之求和)

来源：改编自 Project Euler Problem 739

## 原题意

考虑 Fibonacci 数列 $F_1 = 1, F_2 = 1, F_n = F_{n-1} + F_{n-2}$（$n > 2$）。

定义 $k$ 重嵌套和：
$$S_k(n) = \sum_{i_1=1}^{n} \sum_{i_2=1}^{i_1} \cdots \sum_{i_k=1}^{i_{k-1}} F_{i_k}$$

即 $S_1(n) = \sum_{i=1}^{n} F_i$，$S_2(n) = \sum_{i=1}^{n} S_1(i)$，以此类推。

问题求 $S_k(N)$ 的某个特定值（或对模数取余）。

PE 答案：7113990164573665086。

## 算法

1. **组合恒等式**：利用曲棍球棒恒等式（hockey-stick identity）：
   $$S_k(n) = \sum_{i=1}^{n} \binom{n-i+k-1}{k-1} F_i$$

2. **Fibonacci 和的闭形式**：
   - $\sum_{i=1}^{n} F_i = F_{n+2} - 1$
   - $\sum_{i=1}^{n} \sum_{j=1}^{i} F_j = F_{n+4} - (n+3)$
   - 一般形式：$S_k(n) = F_{n+2k} - P_{k-1}(n)$，其中 $P$ 是 $k-1$ 次多项式

3. **递推计算**：利用矩阵快速幂或 Binet 公式计算大下标 Fibonacci 数。

4. **大整数处理**：答案约 $7.11 \times 10^{18}$，需使用 128 位整数（`__int128`）。

5. **复杂度**：$O(k \log N)$（使用快速幂计算 Fibonacci 数）。

## 改编方向

1. 参数化 $k$ 和 $N$ 的范围
2. 替换 Fibonacci 为其他线性递推数列（如 Lucas、Tribonacci）
3. 改为加权和：$\sum i \cdot F_i$ 等
4. 求模素数下的结果
5. 改为乘积形式
