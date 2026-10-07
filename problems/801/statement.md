# Problem 801（PE 801）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=801](https://projecteuler.net/problem=801)。

## **$x^y\equiv y^x$**

The positive integral solutions of the equation $x^y=y^x$ are $(2,4)$, $(4,2)$ and $(k,k)$ for all $k>0$.

For a given positive integer $n$, let $f(n)$ be the number of integral values $0<x,y \le n^2-n$ such that
$$x^y\equiv y^x \pmod n$$
For example, $f(5)=104$ and $f(97)=1614336$.

Let $S(M,N)=\sum f(p)$ where the sum is taken over all primes $p$ satisfying $M\le p\le N$.

You are given $S(1,10^2)=7381000$ and $S(1,10^5) \equiv 701331986 \pmod{993353399}$.

Find $S(10^{16}, 10^{16}+10^6)$. Give your answer modulo $993353399$.

## **$x^y\equiv y^x$**

方程$x^y=y^x$的正整数解有$(2,4)$、$(4,2)$和满足$k>0$的任意$(k,k)$。

对于给定的正整数$n$，记$f(n)$为下列同余方程满足$0<x,y \le n^2-n$的正整数解的数目：
$$x^y\equiv y^x \pmod n$$
例如，$f(5)=104$，$f(97)=1614336$。

对于所有满足$M\le p\le N$的质数$p$，记$S(M,N)=\sum f(p)$。

已知$S(1,10^2)=7381000$，$S(1,10^5) \equiv 701331986 \pmod{993353399}$。

求$S(10^{16}, 10^{16}+10^6)$，并将你的答案对$993353399$取余。

---

## 输入格式

字符 `PE`：输出原题官方答案。

## 输出格式

原题官方答案。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
参考常量: PE_ANSWER = 7937995LL
