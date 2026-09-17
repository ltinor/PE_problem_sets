# Problem 931（PE 931）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=931](https://projecteuler.net/problem=931)。

## **Totient Graph**

For a positive integer $n$ construct a graph using all the divisors of $n$ as the vertices. An edge is drawn between $a$ and $b$ if $a$ is divisible by $b$ and $a/b$ is prime, and is given weight $\phi(a)-\phi(b)$, where $\phi$ is the Euler totient function.<br/>
Define $t(n)$ to be the total weight of this graph.<br/>
The example below shows that $t(45) = 52$:

<div style="text-align:center">
<img src="/resources/images/0931_totientgraph.png" alt="0931_totientgraph.png">
</div>

Let $T(N)=\displaystyle\sum_{n=1}^{N} t(n)$. You are given $T(10)=26$ and $T(10^2)=5282$.

Find $T(10^{12})$. Give your answer modulo $715827883$.

## **欧拉函数图**

对于正整数$n$，以$n$的所有因数为顶点构造图。若$a$能被$b$整除，且$a/b$是素数，则在$a$和$b$对应的顶点之间作一条边，该边的权重为$\phi(a)-\phi(b)$，其中$\phi$表示欧拉函数。<br/>
定义$t(n)$为该图的总权重。<br/>
下图展示了$t(45) = 52$：

<div style="text-align:center">
<img src="/resources/images/0931_totientgraph.png" alt="0931_totientgraph.png">
</div>

令$T(N)=\displaystyle\sum_{n=1}^{N} t(n)$。已知$T(10)=26$，$T(10^2)=5282$。

求$T(10^{12})$，并对$715827883$取余作为你的答案。

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

