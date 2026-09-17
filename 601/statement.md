# Problem 601（PE 601）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=601](https://projecteuler.net/problem=601)。

## **Divisibility streaks**

For every positive number $n$ we define the function $streak(n)=k$ as the smallest positive integer $k$ such that $n+k$ is not divisible by $k+1$.
E.g:
13 is divisible by 1 
14 is divisible by 2 
15 is divisible by 3 
16 is divisible by 4 
17 is NOT divisible by 5 
So $streak(13) = 4$.  
Similarly:
120 is divisible by 1 
121 is NOT divisible by 2 
So $streak(120) = 1$.

Define $P(s, N)$ to be the number of integers $n$, $1 < n < N$, for which $streak(n) = s$.
So $P(3, 14) = 1$ and $P(6, 10^6) = 14286$.

Find the sum, as $i$ ranges from 1 to 31, of $P(i, 4^i)$.

## **连续整除**

对于任意正整数$n$，我们定义函数$streak(n)=k$为使$n+k$不能被$k+1$整除的最小正整数$k$。
例如：
13能被1整除 
14能被2整除 
15能被3整除
16能被4整除
17不能被5整除
因此$streak(13) = 4$。
类似地：
120能被1整除
121不能被2整除
因此$streak(120) = 1$。

定义$P(s, N)$为$1 < n < N$中满足$streak(n) = s$的整数$n$的数量。
因此$P(3, 14) = 1$，而$P(6, 10^6) = 14286$。

令$i$取值从1到31，求对应的$P(i, 4^i)$之和。

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

