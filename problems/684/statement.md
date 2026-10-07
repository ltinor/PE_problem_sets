# Problem 684（PE 684）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=684](https://projecteuler.net/problem=684)。

## **Inverse Digit Sum**

Define $s(n)$ to be the smallest number that has a digit sum of $n$. For example $s(10) = 19$.
Let $\displaystyle S(k) = \sum_{n=1}^k s(n)$. You are given $S(20) = 1074$.

Further let $f_i$ be the Fibonacci sequence defined by $f_0=0, f_1=1$ and $f_i=f_{i-2}+f_{i-1}$ for all $i \ge 2$.

Find $\displaystyle \sum_{i=2}^{90} S(f_i)$. Give your answer modulo $1\ 000\ 000\ 007$.

## **数字和的逆函数**

记 $s(n)$为最小的数字和为$n$的数。例如$s(10) = 19$。
记$\displaystyle S(k) = \sum_{n=1}^k s(n)$。已知$S(20) = 1074$。

记$f_i$为斐波那契数列，其中$f_0=0$，$f_1=1$，对任意$i \ge 2$有$f_i=f_{i-2}+f_{i-1}$。

求$\displaystyle \sum_{i=2}^{90} S(f_i)$。将你的答案对$1\ 000\ 000\ 007$取余。

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
参考常量: PE_ANSWER = 922058210
