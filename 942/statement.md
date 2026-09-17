# Problem 942（PE 942）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=942](https://projecteuler.net/problem=942)。

## **Mersenne's Square Root**

Given a natural number $q$, let $p = 2^q - 1$ be the $q$-th **Mersenne number**.

Let $R(q)$ be the minimal square root of $q$ modulo $p$, if one exists. In other words, $R(q)$ is the smallest positive integer $x$ such that $x^2 - q$ is divisible by $p$.

For example, $R(5)=6$ and $R(17)=47569$.

Find $R(74\ 207\ 281)$. Give your answer modulo $10^9 + 7$.

Note: $2^{74207281}-1$ is prime.

## **梅森平方根**

对于给定自然数$q$，记$p = 2^q - 1$为第$q$个**梅森数**。

记$R(q)$为$q$在模$p$同余意义下的最小平方根（若存在）。换句话说，$R(q)$是满足$x^2 - q$能被$p$整除的最小正整数$x$。

例如，$R(5)=6$，$R(17)=47569$。

求$R(74\ 207\ 281)$，并对$10^9 + 7$取余作为你的答案。

注意：$2^{74207281}-1$是质数。

---

## 输入格式

（待人工补充：请对照 code/std.cpp 的读取约定描述。）

## 输出格式

（待人工补充。）

## 样例

### 输入

```
5
```

### 输出

```
6
```

---

## 数据范围

（待人工补充；原题参数范围见上方原题描述。）

