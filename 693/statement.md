# Problem 693（PE 693）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=693](https://projecteuler.net/problem=693)。

## **Finite Sequence Generator**

Two positive integers $x$ and $y$ ($x>y$) can generate a sequence in the following manner:
- $a_x = y$ is the first term,
- $a_{z+1} = a_z^2 \bmod z$ for $z = x, x+1,x+2,\ldots$ and
- the generation stops when a term becomes $0$ or $1$.

The number of terms in this sequence is denoted $l(x,y)$.

For example, with $x = 5$ and $y = 3$, we get $a_5 = 3$, $a_6 = 3^2 \bmod 5 = 4$, $a_7 = 4^2\bmod 6 = 4$, etc. Giving the sequence of $29$ terms:
$3,4,4,2,4,7,9,4,4,3,9,6,4,16,4,16,16,4,16,3,9,6,10,19,25,16,16,8,0$
Hence $l(5,3) = 29$.

$g(x)$ is defined to be the maximum value of $l(x,y)$ for $y<x$. For example, $g(5) = 29$.

Further, define $f(n)$ to be the maximum value of $g(x)$ for $x \le n$. For example, $f(100) = 145$ and $f(10\ 000) = 8824$.

Find $f(3\ 000\ 000)$.

## **有限数列生成器**

对两个任意正整数$x$和$y$（其中$x>y$），可以按照如下方式生成数列：
- 数列的第一项为$a_x = y$；
- 对于$z = x, x+1,x+2,\ldots$，令$a_{z+1} = a_z^2 \bmod z$；
- 当某一项为$0$或$1$时停止。

当序列停止时，记$l(x,y)$为此时序列中的项数。

例如，若$x = 5$而$y = 3$，那么依次生成的项分别是$a_5 = 3$，$a_6 = 3^2 \bmod 5 = 4$，$a_7 = 4^2\bmod 6 = 4$，依此类推，前$29$项分别是：
$3,4,4,2,4,7,9,4,4,3,9,6,4,16,4,16,16,4,16,3,9,6,10,19,25,16,16,8,0$
因此$l(5,3) = 29$。

记$g(x)$在所有$y<x$中$l(x,y)$的最大值。例如，$g(5) = 29$。

记$f(n)$为所有$x\le n$中$g(x)$的最大值。例如，$f(100) = 145$，$f(10\ 000) = 8824$。

求$f(3\ 000\ 000)$。

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

