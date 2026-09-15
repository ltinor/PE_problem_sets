# PE454 - 丢番图倒数 III (Diophantine reciprocals III)

来源：改编自 Project Euler Problem 454

## 原题意

方程 1/x + 1/y = 1/n，x, y, n 为正整数。

F(L) = 满足 x < y ≤ L 的解的数目。

验证：F(15) = 4, F(1000) = 1069。

原题求 F(10^12) = 5435004633092。

## 题目

给定 L，求 F(L)。

## 算法

- 变换：(x-n)(y-n) = n²
- 设 a = x-n, b = y-n，则 a·b = n², a < b, n+b ≤ L
- 即 a | n², a < n, a ≥ n²/(L-n)
- 枚举 v = d·s²（d squarefree），则 u = d·t² (t < s)
- 约束：d·s·(t+s) ≤ L

## 改编方向

1. **多变量倒数**：1/x₁ + ... + 1/xₖ = 1/n
2. **不等式推广**：1/x + 1/y ≤ 1/n
3. **带权版本**：a/x + b/y = 1/n
