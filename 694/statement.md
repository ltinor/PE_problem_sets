# Problem 694（PE 694）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=694](https://projecteuler.net/problem=694)。

## **Cube-full Divisors**

A positive integer $n$ is considered <i>cube-full</i>, if for every prime $p$ that divides $n$, so does $p^3$. Note that $1$ is considered cube-full.

Let $s(n)$ be the function that counts the number of cube-full divisors of $n$. For example, $1$, $8$ and $16$ are the three cube-full divisors of $16$. Therefore, $s(16)=3$.

Let $S(n)$ represent the summatory function of $s(n)$, that is $S(n)=\displaystyle\sum_{i=1}^n s(i)$.

You are given $S(16) =  19$, $S(100) = 126$ and $S(10000) = 13344$.

Find $S(10^{18})$.

## **满立方约数**

考虑正整数$n$，若对于任意整除$n$的质数$p$，总有$p^3$也整除$n$，则称$n$为<i class=zh>满立方</i>数。作为特例，$1$也是满立方数。

记$s(n)$为$n$的所有约数中满立方数的数目。例如，$16$的约数中有$1$、$8$和$16$三个满立方数，因此$s(16)=3$。

记$S(n)$为$s(n)$的部分和函数，也即$S(n)=\displaystyle\sum_{i=1}^n s(i)$。

已知$S(16) =  19$，$S(100) = 126$，$S(10000) = 13344$。

求$S(10^{18})$。

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
参考常量: PE_ANSWER = 1339784153569958487LL
