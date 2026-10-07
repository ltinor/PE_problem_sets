# Problem 861（PE 861）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=861](https://projecteuler.net/problem=861)。

## **Products of Bi-Unitary Divisors**

A <i>unitary divisor</i> of a positive integer $n$ is a divisor $d$ of $n$ such that $\gcd(d,n/d)=1$.

A <i>bi-unitary divisor</i> of $n$ is a divisor $d$ for which $1$ is the only unitary divisor of $d$ that is also a unitary divisor of $n/d$.

For example, $2$ is a bi-unitary divisor of $8$, because the unitary divisors of $2$ are $\\\{1,2\\\}$, and the unitary divisors of $8/2$ are $\\\{1,4\\\}$, with $1$ being the only unitary divisor in common.

The bi-unitary divisors of $240$ are $\\\{1,2,3,5,6,8,10,15,16,24,30,40,48,80,120,240\\\}$.

Let $P(n)$ be the product of all bi-unitary divisors of $n$. Define $Q_k(N)$ as the number of positive integers $1 < n \leq N$ such that $P(n)=n^k$. For example, $Q_2\left(10^2\right)=51$ and $Q_6\left(10^6\right)=6189$.

Find $\sum_{k=2}^{10}Q_k\left(10^{12}\right)$.

## **双元因数的乘积**

若正整数$n$的因数$d$满足$\gcd(d,n/d)=1$，则称$d$为$n$的<i class=zh>元因数</i>。

若$1$是$d$和$n/d$唯一的公共元因数，则称$d$为$n$的<i class=zh>双元因数</i>。

例如，$2$是$8$的双元因数，因为$2$的元因数有$\\\{1,2\\\}$，而$8/2$的元因数有$\\\{1,4\\\}$，只有$1$是唯一的公共元因数。

$240$的双元因数有$\\\{1,2,3,5,6,8,10,15,16,24,30,40,48,80,120,240\\\}$。

令$P(n)$为$n$的所有双元因数之积。定义$Q_k(N)$为满足$1 < n \leq N$和$P(n)=n^k$的正整数$n$的数量。例如，$Q_2\left(10^2\right)=51$，$Q_6\left(10^6\right)=6189$。

求$\sum_{k=2}^{10}Q_k\left(10^{12}\right)$。

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
参考常量: PE_ANSWER = 1940527636228617032LL
