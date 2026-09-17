# Problem 722（PE 722）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=722](https://projecteuler.net/problem=722)。

## **Slowly converging series**

For a non-negative integer $k$, define
$$E_k(q) = \sum\limits_{n = 1}^\infty \sigma_k(n)q^n$$
where $\sigma_k(n) = \sum_{d \mid n} d^k$ is the sum of the $k$-th powers of the positive divisors of $n$.

It can be shown that, for every $k$, the series $E_k(q)$ converges for any $0<q< 1$.

For example,
$E_1(1 - \frac{1}{2^4}) = \mathrm{3.872155809243e2}$
$E_3(1 - \frac{1}{2^8}) = \mathrm{2.767385314772e10}$
$E_7(1 - \frac{1}{2^{15}}) = \mathrm{6.725803486744e39}$
All the above values are given in scientific notation rounded to twelve digits after the decimal point.

Find the value of $E_{15}(1 - \frac{1}{2^{25}})$.
Give the answer in scientific notation rounded to twelve digits after the decimal point.

## **缓慢收敛级数**

对于非负整数$k$，记
$$E_k(q) = \sum\limits_{n = 1}^\infty \sigma_k(n)q^n$$
其中$\sigma_k(n) = \sum_{d \mid n} d^k$表示$n$的所有正约数的$k$次幂之和。

可以证明，对于所有$k$和任意$0<q< 1$，级数$E_k(q)$始终收敛。

例如，
$E_1(1 - \frac{1}{2^4}) = \mathrm{3.872155809243e2}$
$E_3(1 - \frac{1}{2^8}) = \mathrm{2.767385314772e10}$
$E_7(1 - \frac{1}{2^{15}}) = \mathrm{6.725803486744e39}$
上述取值均以科学计数法表示并保留小数点后十二位。

求$E_{15}(1 - \frac{1}{2^{25}})$的值，以科学计数法表示并保留小数点后十二位。

---

## 输入格式

（待人工补充：请对照 code/std.cpp 的读取约定描述。）

## 输出格式

（待人工补充。）

## 样例

（无 data 数据，待人工补充。）

---

## 数据范围

（待人工补充；原题参数范围见上方原题描述。）

