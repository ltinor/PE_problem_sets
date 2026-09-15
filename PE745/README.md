# PE745 — Sum of Squares (平方和)

来源：改编自 Project Euler Problem 745

## 原题意

对于正整数 $n$，定义 $g(n)$ 为整除 $n$ 的**最大完全平方数**。
例如：$g(18) = 9$，$g(19) = 1$。

定义：
$$S(N) = \sum_{n=1}^N g(n)$$

例如：$S(10) = 24$，$S(100) = 767$。

求 $S(10^{14})$ 对 $1\ 000\ 000\ 007$ 取余。

PE 答案：94586478

## 算法

1. **平方无因子分解**：每个 $n$ 可唯一写成 $n = a^2 \cdot b$，其中 $b$ 无平方因子（squarefree）。则 $g(n) = a^2$。

2. **求和重写**：
   $$S(N) = \sum_{a=1}^{\lfloor\sqrt{N}\rfloor} a^2 \cdot Q\!\left(\left\lfloor\frac{N}{a^2}\right\rfloor\right)$$
   其中 $Q(m)$ 为 $\le m$ 的无平方因子数的个数。

3. **$Q(m)$ 计算**（Möbius 反演）：
   $$Q(m) = \sum_{d=1}^{\lfloor\sqrt{m}\rfloor} \mu(d) \cdot \left\lfloor\frac{m}{d^2}\right\rfloor$$

4. **变量代换**（$t = ad$）：
   $$S(N) = \sum_{t=1}^{\lfloor\sqrt{N}\rfloor} \left\lfloor\frac{N}{t^2}\right\rfloor \cdot J_2(t)$$
   其中 $J_2(t) = t^2 \prod_{p\mid t} (1 - 1/p^2)$ 是 Jordan 二重 totient 函数。

5. **线性筛**：对 $t \le 10^7$ 用线性筛预处理 $J_2(t)$，然后直接求和。

6. **复杂度**：$O(\sqrt{N})$ 时间和空间（$\sqrt{10^{14}} = 10^7$）。

## 改编方向

1. 参数化 $N$
2. 改为求立方因子（$g_3(n)$ = 最大完全立方整除 $n$）
3. 改为求和 $\sum n/g(n)$（平方无因子部分之和）
4. 考虑多个模数
5. 推广至高次幂因子
