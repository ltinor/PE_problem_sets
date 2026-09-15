# PE779 — Prime factor and exponent（质因子与指数）

来源：改编自 Project Euler Problem 779

## 原题意

对于正整数 $n$，考虑其质因数分解 $n = \prod p_i^{e_i}$。定义与质因子 $p_i$ 和指数 $e_i$ 相关的某个函数 $f(n)$。

常见的相关函数包括：
- $\Omega(n)$：质因子总数（计重数）
- $\omega(n)$：不同质因子的个数
- Liouville 函数 $\lambda(n) = (-1)^{\Omega(n)}$
- Möbius 函数 $\mu(n)$（平方自由时 $(-1)^{\omega(n)}$，否则为 0）

PE 答案：0.54732610（一个介于 0 和 1 之间的小数）。

## 算法

1. **质因数分解**：试除法或 Pollard-Rho 算法。
2. **$\Omega(n)$ 和 $\omega(n)$ 统计**：计算平均值和分布。
3. **Liouville 函数**：$\lambda(n) = (-1)^{\Omega(n)}$，其 summatory 函数的渐近行为与 Riemann 猜想相关。
4. **Mertens 函数**：$M(x) = \sum_{n \le x} \mu(n)$。
5. **平方自由数密度**：极限为 $6/\pi^2 \approx 0.607927$。

## 改编方向

1. 研究 $\omega(n)/\Omega(n)$ 比值的分布
2. 计算与 $\mu(n)$ 相关的级数
3. 分析质因子指数的联合分布
4. 对随机整数研究 $p_i + e_i$ 的统计量
5. 推广到一般数域中的理想分解
