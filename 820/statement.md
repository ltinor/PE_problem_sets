# Problem 820（PE 820）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=820](https://projecteuler.net/problem=820)。

## **$N$<sup>th</sup> digit of Reciprocals**

Let $d_n(x)$ be the $n$<sup>th</sup> decimal digit of the fractional part of $x$, or $0$ if the fractional part has fewer than $n$ digits.

For example:
- $d_7 \left( 1 \right) = d_7 \left( \frac 1 2 \right) = d_7 \left( \frac 1 4 \right) = d_7 \left( \frac 1 5 \right) = 0$
- $d_7 \left( \frac 1 3 \right) = 3$ since $\frac 1 3 = 0.333333{\color{red}3}333\ldots$
- $d_7 \left( \frac 1 6 \right) = 6$ since $\frac 1 6 = 0.166666{\color{red}6}666\ldots$
- $d_7 \left( \frac 1 7 \right) = 1$ since $\frac 1 7 = 0.142857{\color{red}1}428\ldots$

Let $\displaystyle  S(n) = \sum_{k=1}^n d_n \left( \frac 1 k \right)$.

You are given:
- $S(7) = 0 + 0 + 3 + 0 + 0 + 6 + 1 = 10$
- $S(100) = 418$

Find $S(10^7)$.

## **倒数的第$N$位数字**

记$d_n(x)$为$x$的小数点后第$n$位数字；若其小数部分不满$n$位则记为$0$。

例如：
- $d_7 \left( 1 \right) = d_7 \left( \frac 1 2 \right) = d_7 \left( \frac 1 4 \right) = d_7 \left( \frac 1 5 \right) = 0$
- $d_7 \left( \frac 1 3 \right) = 3$，因为$\frac 1 3 = 0.333333{\color{red}3}333\ldots$
- $d_7 \left( \frac 1 6 \right) = 6$，因为$\frac 1 6 = 0.166666{\color{red}6}666\ldots$
- $d_7 \left( \frac 1 7 \right) = 1$，因为$\frac 1 7 = 0.142857{\color{red}1}428\ldots$

记$\displaystyle  S(n) = \sum_{k=1}^n d_n \left( \frac 1 k \right)$。

已知：
- $S(7) = 0 + 0 + 3 + 0 + 0 + 6 + 1 = 10$
- $S(100) = 418$

求$S(10^7)$。

---

## 输入格式

字符 `PE`：输出原题官方答案。

## 输出格式

原题官方答案。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
参考常量: PE_ANSWER_S_1E7 = 44967734LL
