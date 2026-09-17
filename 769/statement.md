# Problem 769（PE 769）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=769](https://projecteuler.net/problem=769)。

## **Binary Quadratic Form II**

Consider the following binary quadratic form:

$$f(x,y)=x^2+5xy+3y^2$$

A positive integer $q$ has a primitive representation if there exist positive integers $x$ and $y$ such that $q = f(x,y)$ and $\gcd(x,y)=1$.

We are interested in primitive representations of perfect squares. For example: <br />
$17^2=f(1,9)$ <br />
$87^2=f(13,40) = f(46,19)$

Define $C(N)$ as the total number of primitive representations of $z^2$ for $0 < z \leq N$.<br /> 
Multiple representations are counted separately, so for example $z=87$ is counted twice.

You are given $C(10^3)=142$ and $C(10^{6})=142463$. 

Find $C(10^{14})$.

## **二元二次型II**

考虑如下二元二次型：

$$f(x,y)=x^2+5xy+3y^2$$

对于正整数$q$，若存在正整数$x$和$y$使得$q=f(x,y)$且$\gcd(x,y)=1$，则称之为$q$的本原表达式。

我们感兴趣的是完全平方数的本原表达式。例如：<br />
$17^2=f(1,9)$ <br />
$87^2=f(13,40) = f(46,19)$

记$C(N)$为所有满足$0 < z \leq N$的完全平方数$z^2$的本原表达式数目之和。<br /> 
同一个数的不同本原表达式单独计入，因此如$z=87$就有两组本原表达式。

已知$C(10^3)=142$和$C(10^{6})=142463$。

求$C(10^{14})$。

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

