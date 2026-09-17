# Problem 812（PE 812）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=812](https://projecteuler.net/problem=812)。

## **Dynamical Polynomials**

A <i>dynamical polynomial</i> is a monic polynomial $f(x)$ with integer coefficients such that $f(x)$ divides $f(x^2-2)$.

For example, $f(x) = x^2 - x - 2$ is a dynamical polynomial because $f(x^2-2) = x^4-5x^2+4 = (x^2 + x -2)f(x)$.

Let $S(n)$ be the number of dynamical polynomials of degree $n$.<br />
For example, $S(2)=6$, as there are six dynamical polynomials of degree 2:
$$ x^2-4x+4 \quad x^2-x-2 \quad x^2-4 \quad x^2-1 \quad x^2+x-1 \quad x^2+2x+1 $$
Also, $S(5)=58$ and $S(20)=122087$.

Find $S(10\ 000)$. Give your answer modulo $998244353$.

## **动态多项式**

若首一整系数多项式$f(x)$整除$f(x^2-2)$，则称之为<i class=zh>动态多项式</i>。

例如，$f(x) = x^2 - x - 2$是动态多项式，因为$f(x^2-2) = x^4-5x^2+4 = (x^2 + x -2)f(x)$。

记$S(n)$为最高次数为$n$的动态多项式的数目。<br />
例如，$S(2)=6$，因为共有六个最高次数为$2$的动态多项式：
$$ x^2-4x+4 \quad x^2-x-2 \quad x^2-4 \quad x^2-1 \quad x^2+x-1 \quad x^2+2x+1 $$
已知$S(5)=58$，$S(20)=122087$。

求$S(10\ 000)$，并将你的答案对$998244353$取余。

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

