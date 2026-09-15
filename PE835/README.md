# PE835 — Supernatural Numbers（超自然数）

来源：改编自 Project Euler Problem 835

## 原题意

超自然数（Supernatural Numbers，也称 Steinitz Numbers）是形式乘积

$$S = \prod_{p \text{ prime}} p^{v_p}$$

其中每个指数 $v_p \in \mathbb{N}_0 \cup \{\infty\}$（非负整数或无穷大）。超自然数是自然数的推广：允许某些素数的指数为无穷大。

超自然数在数学中有深刻背景：它们在赋值理论、profinite 群论和绝对 Galois 群理论中自然出现。所有超自然数在整除偏序下构成完备格。

本题要求对某个上界 $N$，统计满足某些条件的超自然数的数量（或求和）。

PE 答案：636431039。

## 算法

1. **有限部分约束**：设超自然数的「有限部分」为所有指数有限的素数幂之积。要求有限部分 $\leq N$。
2. **计数公式**：对每个自然数 $n$（有限部分），素数 $p \leq N$ 若 $p \nmid n$，则 $v_p$ 可独立取 $0$（有限）或 $\infty$。
   $$\text{Total}(N) = \sum_{n=1}^{N} 2^{\pi(N) - \omega(n)}$$
   其中 $\pi(N)$ 为 $\leq N$ 的素数个数，$\omega(n)$ 为 $n$ 的不同素因子个数。
3. **预计算 $\omega(n)$**：通过筛法预计算 $[1,N]$ 内每个数的不同素因子数。
4. **模运算**：使用模逆元计算 $2^{-\omega(n)} \bmod M$，避免大数溢出。

## 改编方向

1. 限制无穷指数的素数个数
2. 考虑超自然数的「乘积」和「LCM/GCD」
3. 研究超自然数的 Dirichlet 生成函数
4. 推广到代数数域中的超自然理想
5. 与 profinite 整数 $\widehat{\mathbb{Z}}$ 的关联
