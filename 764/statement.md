# Problem 764（PE 764）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=764](https://projecteuler.net/problem=764)。

## **Asymmetric Diophantine Equation**

Consider the following Diophantine equation:
$$16x^2+y^4=z^2$$
where $x$, $y$ and $z$ are positive integers.

Let $S(N) = \displaystyle{\sum(x+y+z)}$ where the sum is over all solutions $(x,y,z)$ such that $1 \leq x,y,z \leq N$ and $\gcd(x,y,z)=1$. 

For $N=100$, there are only two such solutions: $(3,4,20)$ and $(10,3,41)$. So $S(10^2)=81$.

You are also given that $S(10^4)=112851$ (with $26$ solutions), and $S(10^7)\equiv 248876211 \pmod{10^9}$.

Find $S(10^{16})$. Give your answer modulo $10^9$.

## **不对称丢番图方程**

考虑如下的丢番图方程：
$$16x^2+y^4=z^2$$
其中$x$、$y$和$z$均为正整数。

考虑所有满足$1 \leq x,y,z \leq N$和$\gcd(x,y,z)=1$的解$(x,y,z)$，记$S(N) = \displaystyle{\sum(x+y+z)}$在这些解上求和。

对于$N=100$，只有两组满足上述条件的解，分别是$(3,4,20)$和$(10,3,41)$，因此$S(10^2)=81$。

已知$S(10^4)=112851$（共有$26$组解），以及$S(10^7)\equiv 248876211 \pmod{10^9}$。

求$S(10^{16})$，并将你的答案对$10^9$取余。

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

