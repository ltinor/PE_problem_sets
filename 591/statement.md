# Problem 591（PE 591）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=591](https://projecteuler.net/problem=591)。

## **Best Approximations by Quadratic Integers**

Given a non-square integer $d$, any real $x$ can be approximated arbitrarily close by <b>quadratic integers</b> $a+b\sqrt{d}$, where $a,b$ are integers. For example, the following inequalities approximate $\pi$ with precision $10^{-13}$:
$4375636191520\sqrt{2}-6188084046055 < \pi < 721133315582\sqrt{2}-1019836515172 $
We call $BQA_d(x,n)$ the quadratic integer closest to $x$ with the absolute values of $a,b$ not exceeding $n$.
We also define the integral part of a quadratic integer as $I_d(a+b\sqrt{d}) = a$.

You are given that:
- $BQA_2(\pi,10) = 6 - 2\sqrt{2}$
- $BQA_5(\pi,100)=26\sqrt{5}-55$
- $BQA_7(\pi,10^6)=560323 - 211781\sqrt{7}$
- $I\_2(BQA\_2(\pi,10^{13}))=-6188084046055$

Find the sum of $|I\_d(BQA\_d(\pi,10^{13}))|$ for all non-square positive integers less than 100.

## **二次整数最佳逼近**

给定一个非完全平方的整数$d$，任意实数$x$可以用所谓<b>二次整数</b>$a+b\sqrt{d}$任意逼近，其中$a,b$均为整数。例如如下不等式能够以$10^{-13}$的精度逼近$\pi$：
$4375636191520\sqrt{2}-6188084046055 < \pi < 721133315582\sqrt{2}-1019836515172$
我们记$a,b$不超过$n$的所有二次整数中最接近$x$的为$BQA_d(x,n)$。
同时我们定义二次整数的“整数”部分为$I_d(a+b\sqrt{d}) = a$。

已知：
- $BQA_2(\pi,10) = 6 - 2\sqrt{2}$
- $BQA_5(\pi,100)=26\sqrt{5}-55$
- $BQA_7(\pi,10^6)=560323 - 211781\sqrt{7}$
- $I\_2(BQA\_2(\pi,10^{13}))=-6188084046055$

对于所有小于100的非完全平方整数$d$，求其对应的$|I\_d(BQA\_d(\pi,10^{13}))|$之和。

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

