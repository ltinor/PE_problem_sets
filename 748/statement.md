# Problem 748（PE 748）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=748](https://projecteuler.net/problem=748)。

## **Upside down Diophantine equation**

Upside Down is a modification of the famous Pythagorean equation:
$$\frac{1}{x^2}+\frac{1}{y^2}=\frac{13}{z^2}$$

A solution $(x,y,z)$  to this equation with $x,y$ and $z$ positive integers is a primitive solution if $\gcd(x,y,z)=1$.

Let $S(N)$ be the sum of $x+y+z$ over primitive Upside Down solutions such that $1 \leq x,y,z \leq N$ and $x \le y$. 
For $N=100$ the primitive solutions are $(2,3,6)$ and $(5,90,18)$, thus $S(10^2)=124$.
It can be checked that $S(10^3)=1470$ and $S(10^5)=2340084$.

Find $S(10^{16})$ and give the last $9$ digits as your answer.

## **颠倒不定方程**

把著名的毕达哥拉斯方程稍加修改就得到了如下的颠倒不定方程：
$$\frac{1}{x^2}+\frac{1}{y^2}=\frac{13}{z^2}$$

若上述方程的一组正整数解$(x,y,z)$满足$\gcd(x,y,z)=1$，则称之为该方程的本原解。

考虑该方程的所有本原解，并记$S(N)$为所有满足$1 \leq x,y,z \leq N$和$x \le y$的本原解对应$x+y+z$之和。
对于$N=100$，满足条件的本原解包括$(2,3,6)$和$(5,90,18)$，因此$S(10^2)=124$。
可以验证，$S(10^3)=1470$，$S(10^5)=2340084$。

求$S(10^{16})$，并给出最后$9$位数字作为你的答案。

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

