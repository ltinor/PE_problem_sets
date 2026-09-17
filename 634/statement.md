# Problem 634（PE 634）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=634](https://projecteuler.net/problem=634)。

## **Numbers of the form $a^2b^3$**

Define $F(n)$ to be the number of integers $x\le n$ that can be written in the form $x=a^2b^3$, where $a$ and $b$ are integers not necessarily different and both greater than $1$.

For example, $32=2^2\times 2^3$ and $72=3^2\times 2^3$ are the only two integers less than $100$ that can be written in this form. Hence, $F(100)=2$.

Further you are given $F(2\times 10^4)=130$ and $F(3\times 10^6)=2014$.

Find $F(9\times 10^{18})$.

## **可写成$a^2b^3$的数**

考虑整数$x\le n$，若$x$可写成$x=a^2b^3$，其中$a$和$b$是大于$1$且可重复的整数，记所有此类整数的数目为$F(n)$。

例如，在小于$100$的整数中，只有$32=2^2\times 2^3$和$72=3^2\times 2^3$可以写成这种形式，因此$F(100)=2$。

此外，还已知$F(2\times 10^4)=130$以及$F(3\times 10^6)=2014$。

求$F(9\times 10^{18})$。

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

