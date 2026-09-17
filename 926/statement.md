# Problem 926（PE 926）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=926](https://projecteuler.net/problem=926)。

## **Total Roundness**

A <b>round number</b> is a number that ends with one or more zeros in a given base.

Let us define the <i>roundness</i> of a number $n$ in base $b$ as the number of zeros at the end of the base $b$ representation of $n$.<br/>
For example, $20$ has roundness $2$ in base $2$, because the base $2$ representation of $20$ is $10100$, which ends with $2$ zeros.

Also define $R(n)$, the <i>total roundness</i> of a number $n$, as the sum of the roundness of $n$ in base $b$ for all $b > 1$.<br/>
For example, $20$ has roundness $2$ in base $2$ and roundness $1$ in base $4$, $5$, $10$, $20$, hence we get $R(20)=6$.<br/>
You are also given $R(10!) = 312$.

Find $R(10\ 000\ 000!)$. Give your answer modulo $10^9 + 7$.

## **总取整度**

<b>取整数</b>是指在给定进制下以一个或多个零结尾的数。

定义数$n$在进制$b$下的<i class=zh>取整度</i>为$n$在$b$进制表示下末尾零的个数。<br/>
例如，$20$在$2$进制下的取整度为$2$，因为$20$的$2$进制表示是$10100$，末尾有$2$个零。

再定义$R(n)$为数$n$的<i class=zh>总取整度</i>，即$n$在所有$b > 1$的进制$b$下的取整度之和。<br/>
例如，$20$在$2$进制下的取整度为$2$，在$4$、$5$、$10$、$20$进制下的取整度为$1$，因此$R(20)=6$。<br/>
已知$R(10!) = 312$。

求$R(10\ 000\ 000!)$，并对$10^9 + 7$取余作为你的答案。

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

