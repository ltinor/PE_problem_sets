# PE 650 — Divisors of Binomial Product（二项式系数乘积的因数）

## 原题

[Project Euler #650](https://projecteuler.net/problem=650)

B(n) = ∏_{k=0}^n C(n, k)（二项式系数的乘积）。

D(n) = Σ_{d|B(n)} d（B(n) 的所有因数之和）。

S(n) = Σ_{k=1}^n D(k)。

已知：S(5) = 5736，S(10) = 141740594713218418，S(100) mod 1 000 000 007 = 332792866。

求 S(20 000) mod 1 000 000 007。

**答案：538319652**

## 算法

- 质因数指数：B(n) = ∏_{k=1}^n k^{2k - n - 1}。故质数 p 在 B(n) 中的指数 e_p(n) = 2·Σ_{k=1}^n v_p(k)·k − (n+1)·Σ_{k=1}^n v_p(k)。
- 指数计算：e_p(n) = Σ_{j≥1} [p^j · q · (q+1) − (n+1) · q]，其中 q = ⌊n/p^j⌋。
- 因数和：D(n) = ∏_{p≤n} (p^{e_p(n)+1} − 1) / (p − 1) = ∏_{p≤n} (1 + p + … + p^{e_p(n)})，对 MOD = 1 000 000 007 取模。
- 预计算所有质数 p ≤ 20000，对每个 p 计算所有 n 的 e_p(n)，累乘得 D(n)，再求和得 S(n)。

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
