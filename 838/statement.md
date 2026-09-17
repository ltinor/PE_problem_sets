# Problem 838（PE 838）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=838](https://projecteuler.net/problem=838)。

## **Not Coprime**

Let $f(N)$ be the smallest positive integer that is not coprime to any positive integer $n \le N$ whose least significant digit is $3$.

For example $f(40)$ equals to $897 = 3 \cdot 13 \cdot 23$ since it is not coprime to any of $3,13,23,33$. By taking the **[natural logarithm](https://en.wikipedia.org/wiki/Natural_logarithm)** (log to base $e$) we obtain $\ln f(40) = \ln 897 \approx 6.799056$ when rounded to six digits after the decimal point.

You are also given $\ln f(2800) \approx 715.019337$.

Find $f(10^6)$. Enter its natural logarithm rounded to six digits after the decimal point.

## **不互质**

记$f(N)$为最小的、与所有小于等于$N$且末位为$3$的数都不互质的正整数。

例如，$f(40)$等于$897 = 3 \cdot 13 \cdot 23$，因为它和$3,13,23,33$中的任意一个都不互质。对这个数取**[自然对数](https://en.wikipedia.org/wiki/Natural_logarithm)**（以$e$为底的对数）并保留六位小数，可得$\ln f(40) = \ln 897 \approx 6.799056$。

已知$\ln f(2800) \approx 715.019337$。

求$f(10^6)$，取其自然对数并保留六位小数作为答案。

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

