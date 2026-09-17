# Problem 586（PE 586）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=586](https://projecteuler.net/problem=586)。

## **Binary Quadratic Form**

The number $209$ can be expressed as $a^2 + 3ab + b^2$ in two distinct ways:

$$\begin{aligned}
209 &= 8^2 + 3\cdot 8\cdot 5 + 5^2 \\\\
209 &= 13^2 + 3\cdot13\cdot 1 + 1^2
\end{aligned}
$$

Let $f(n,r)$ be the number of integers $k$ not exceeding $n$ that can be expressed as $k=a^2 + 3ab + b^2$, with $a\gt b>0$ integers, in exactly $r$ different ways.

You are given that $f(10^5, 4) = 237$ and $f(10^8, 6) = 59517$.

Find $f(10^{15}, 40)$.

## **二元二次型**

数$209$可以用两种方式表达为$a^2 + 3ab + b^2$：

$$\begin{aligned}
209 &= 8^2 + 3\cdot 8\cdot 5 + 5^2 \\\\
209 &= 13^2 + 3\cdot13\cdot 1 + 1^2
\end{aligned}
$$

记$f(n,r)$为不超过$n$且恰好可以用$r$种方式表达为$k=a^2 + 3ab + b^2$的整数$k$的数目，其中整数$a\gt b>0$。

已知$f(10^5, 4) = 237$以及$f(10^8, 6) = 59517$。

求$f(10^{15}, 40)$。

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

