# PE738 — Counting Ordered Factorisations (有序因子分解计数)

来源：改编自 Project Euler Problem 738

## 原题意

令 $d(n, k)$ 表示将 $n$ 写成 $k$ 个大于 $1$ 的整数有序乘积的方式数。即满足以下条件的序列 $(a_1, a_2, \dots, a_k)$ 的数量：
$$a_1 \times a_2 \times \dots \times a_k = n, \quad \forall i: a_i > 1$$

定义 $D(n) = \sum_{k} d(n, k)$，即 $n$ 的所有有序因子分解的总数。

问题求 $\sum_{i=1}^{N} D(i!)$ 模某素数 $M$ 的结果。

PE 答案：143155974。

## 算法

1. **单个数 $D(n)$ 的递推**：
   - $D(1) = 1$（空乘积）
   - $D(n) = \sum_{d \mid n,\ d < n} D(d)$（对于 $n > 1$）

2. **计算 $D(i!)$**：
   - $i!$ 的质因数分解已知：$i! = \prod_{p \le i} p^{e_p(i)}$，其中 $e_p(i) = \sum_{k \ge 1} \lfloor i/p^k \rfloor$
   - $D(i!)$ 可通过 Dirichlet 卷积或生成函数计算

3. **生成函数方法**：
   - $\sum_{n \ge 1} D(n)/n^s = 1/(2 - \zeta(s))$
   - 对质数幂 $p^e$：$D(p^e) = 2^{e-1}$
   - 利用乘性结构加速计算

4. **前缀和**：对 $i = 1 \dots N$ 计算 $D(i!)$ 的累积和，取模。

5. **复杂度**：$O(N \log N)$（使用筛法）。

## 改编方向

1. 参数化 $N$ 的范围（更大或更小）
2. 改变因子分解的限制条件（如因子互质、因子递增等）
3. 改为无序因子分解
4. 求 $D(N!)$ 本身而非前缀和
5. 使用不同的模数
