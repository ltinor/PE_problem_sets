# PE900 — Cumulative Totients（累积欧拉函数）

来源：改编自 Project Euler Problem 900

## 原题意

欧拉函数 $\varphi(n)$ 计算不超过 $n$ 且与 $n$ 互质的正整数个数。累积欧拉函数 $\Phi(N) = \sum_{n=1}^{N} \varphi(n)$ 是 $\varphi$ 的部分和。问题可能涉及大范围上的 $\Phi(N)$ 计算，或嵌套求和 $\sum \Phi(k)$。

PE 答案：840282274715517044

## 算法

1. **Dirichlet 双曲线法**：
   - $\Phi(N) = \frac{N(N+1)}{2} - \sum_{k=2}^{N} \Phi(N/k)$
   - 递归 + 分组，时间复杂度 $O(N^{2/3})$

2. **Möbius 反演公式**：
   - $\Phi(N) = \frac{1}{2} \sum_{k=1}^{N} \mu(k) \cdot \lfloor N/k \rfloor \cdot \lfloor N/k + 1 \rfloor$
   - 需计算 Mertens 函数 $M(N) = \sum \mu(k)$

3. **线性筛法**：
   - 对小范围 ($N \le 10^7$) 使用线性筛计算 $\varphi(n)$
   - 前缀和得到 $\Phi(N)$

4. **渐近公式**：
   - $\Phi(N) \sim \frac{3N^2}{\pi^2}$

## 改编方向

1. 计算 $\Phi(\Phi(N))$ 等嵌套形式
2. 计算 $\sum \varphi(n)^k$ 的渐近行为
3. 研究 $\Phi(N) \bmod M$ 的周期性
4. 推广到 Jordan 函数 $J_k(n)$
