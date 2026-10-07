# 值为整数的多项式（PE 402）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=402](https://projecteuler.net/problem=402)。

可以验证，对于任意整数n，n<sup>4</sup> + 4n<sup>3</sup> + 2n<sup>2</sup> + 5n是6的倍数，而6是最大的满足这一性质的整数。

若对于任意整数n，n<sup>4</sup> + an<sup>3</sup> + bn<sup>2</sup> + cn是整数m的倍数，记M(a, b, c)为m的最大值。例如，M(4, 2, 5) = 6。

记S(N)是所有满足0 &lt; a, b, c ≤ N的M(a, b, c)的和。

我们可以验证S(10) = 1972，以及S(10000) = 2024258331114。

记F<sub>k</sub>为斐波那契数列：
F<sub>0</sub> = 0，F<sub>1</sub> = 1 并且对于任意k ≥ 2
F<sub>k</sub> = F<sub>k-1</sub> + F<sub>k-2</sub>。

对于2 ≤ k ≤ 1234567890123，求Σ S(F<sub>k</sub>)的最后9位数字。

---

## 输入格式

参数模式：输入 N。
- 字符 `PE`：输出原题官方答案。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
