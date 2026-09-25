# Problem 717（PE 717）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=717](https://projecteuler.net/problem=717)。

## **Summation of a Modular Formula**

For an odd prime $p$, define $f(p) = \left\lfloor\frac{2^{(2^p)}}{p}\right\rfloor\bmod{2^p}$.
For example, when $p=3$, $\lfloor 2^8/3\rfloor = 85 \equiv 5 \pmod 8$ and so $f(3) = 5$.

Further define $g(p) = f(p)\bmod p$. You are given $g(31) = 17$.

Now define $G(N)$ to be the summation of $g(p)$ for all odd primes less than $N$.
You are given $G(100) = 474$ and $G(10^4) = 2819236$.

Find $G(10^7)$.

## **余数求和**

对于奇素数$p$，记$f(p) = \left\lfloor\frac{2^{(2^p)}}{p}\right\rfloor\bmod{2^p}$。
例如，若$p=3$，$\lfloor 2^8/3\rfloor = 85 \equiv 5 \pmod 8$，因此$f(3) = 5$。

记$g(p) = f(p)\bmod p$。已知$g(31) = 17$。

记$G(N)$为所有小于$N$的奇素数$p$所对应$g(p)$之和。
已知$G(100) = 474$，$G(10^4) = 2819236$。

求$G(10^7)$。

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
参考常量: PE_ANSWER = 1603036763131LL
