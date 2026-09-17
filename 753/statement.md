# Problem 753（PE 753）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=753](https://projecteuler.net/problem=753)。

## **Fermat Equation**

Fermat's Last Theorem states that no three positive integers $a$, $b$, $c$ satisfy the equation 
$$a^n+b^n=c^n$$
for any integer value of $n$ greater than $2$.

For this problem we are only considering the case $n=3$. For certain values of $p$, it is possible to solve the congruence equation:
$$a^3+b^3 \equiv c^3 \pmod{p}$$

For a prime $p$, we define $F(p)$ as the number of integer solutions to this equation for $1 \le a,b,c < p$.

You are given $F(5) = 12$ and $F(7) = 0$.

Find the sum of $F(p)$ over all primes $p$ less than $6\ 000\ 000$.

## **费马方程**

费马大定理指出，不存在正整数$a$、$b$、$c$满足方程
$$a^n+b^n=c^n$$
其中$n$为大于$2$的正整数。

在本题中我们只考虑$n=3$的情况。对于特定的$p$，如下的同余方程可能有解：
$$a^3+b^3 \equiv c^3 \pmod{p}$$

对于素数$p$，我们记$F(p)$为上述同余方程满足$1 \le a,b,c < p$的整数解的数目。

已知$F(5) = 12$，$F(7) = 0$。

求出所有小于$6\ 000\ 000$的素数$p$所对应$F(p)$之和。

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

