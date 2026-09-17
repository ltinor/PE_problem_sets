# Problem 643（PE 643）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=643](https://projecteuler.net/problem=643)。

## **$2$-Friendly**

Two positive integers $a$ and $b$ are <i>$2$-friendly</i> when $\text{gcd}(a,b)=2^t,t>0$. For example, $24$ and $40$ are $2$-friendly because $\text{gcd}(24,40)=8=2^3$ while $24$ and $36$ are not because $\text{gcd}(24,36)=12=2^2\cdot 3$ not a power of $2$.

Let $f(n)$ be the number of pairs, $(p,q)$, of positive integers with $1\le p<q\le n$ such that $p$ and $q$ are $2$-friendly. You are given $f(10^2)=1031$ and $f(10^6)=321418433$ modulo $1\ 000\ 000\ 007$.

Find $f(10^{11})$ modulo $1\ 000\ 000\ 007$.

## **$2$-友善数**

如果正整数$a$和$b$满足$\text{gcd}(a,b)=2^t,t>0$，则称它们互为<i class=zh>2-友善数</i>。例如，$24$和$40$互为$2$-友善数，因为$\text{gcd}(24,40)=8=2^3$；而$24$和$36$则不是，因为$\text{gcd}(24,36)=12=2^2\cdot 3$不是$2$的幂。

考虑所有满足$1\le p<q\le n$且$p$和$q$互为$2$-友善数的正整数对$(p,q)$，并记这些数对的数目为$f(n)$。已知$f(10^2)=1031$，$f(10^6)$对$1\ 000\ 000\ 007$取余的结果为$321418433$
.

Find $f(10^{11})$并对$1\ 000\ 000\ 007$取余。

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

