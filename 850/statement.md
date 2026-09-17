# Problem 850（PE 850）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=850](https://projecteuler.net/problem=850)。

## **Fractions of Powers**

Any positive real number $x$ can be decomposed into integer and fractional parts $\lfloor x \rfloor + \\\{x\\\}$, where $\lfloor x \rfloor$ (the floor function) is an integer, and $0\le \\\{x\\\} < 1$.

For positive integers $k$ and $n$, define the function
$$f_k(n) = \sum_{i=1}^{n}\left\\\{ \frac{i^k}{n} \right\\\}$$
For example, $f_5(10)=4.5$ and $f_7(1234)=616.5$.

Let
$$S(N) = \sum_{\substack{k=1 \\\\ k\text{ odd}}}^{N} \sum_{n=1}^{N}  f_k(n)$$
You are given that $S(10)=100.5$ and $S(10^3)=123687804$.

Find $\lfloor S(33557799775533) \rfloor$. Give your answer modulo $977676779$.

## **幂的小数部分**

任意正实数$x$都可以分解成整数部分和小数部分$\lfloor x \rfloor + \\\{x\\\}$，其中$\lfloor x \rfloor$（下取整函数）是一个整数，而$0\le \\\{x\\\} < 1$。

对于正整数$k$和$n$，定义函数
$$f_k(n) = \sum_{i=1}^{n}\left\\\{ \frac{i^k}{n} \right\\\}$$
例如，$f_5(10)=4.5$，$f_7(1234)=616.5$。

记
$$S(N) = \sum_{\substack{k=1 \\\\ k\text{为奇数}}}^{N} \sum_{n=1}^{N}  f_k(n)$$
已知$S(10)=100.5$，$S(10^3)=123687804$。

求$\lfloor S(33557799775533) \rfloor$，并将你的答案对$977676779$取余。

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

