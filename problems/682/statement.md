# Problem 682（PE 682）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=682](https://projecteuler.net/problem=682)。

## **$5$-Smooth Pairs**

$5$-smooth numbers are numbers whose largest prime factor doesn't exceed $5$.
$5$-smooth numbers are also called Hamming numbers.

Let $\Omega(a)$ be the count of prime factors of $a$ (counted with multiplicity).
Let $s(a)$ be the sum of the prime factors of $a$ (with multiplicity).
For example, $\Omega(300) = 5$ and $s(300) = 2+2+3+5+5 = 17$.

Let $f(n)$ be the number of pairs, $(p,q)$, of Hamming numbers such that $\Omega(p)=\Omega(q)$ and $s(p)+s(q)=n$.
You are given $f(10)=4$ (the pairs are $(4,9),(5,5),(6,6),(9,4)$) and $f(10^2)=3629$.

Find $f(10^7) \bmod 1\ 000\ 000\ 007$.

## **$5$-光滑数对**

$5$-光滑数是指最大质因数不超过$5$的数。
$5$-光滑数也被称为汉明数。

记$\Omega(a)$为$a$的质因数数目（包括重复的质因数）。
记$s(a)$为$a$的质因数之和（包括重复的质因数）。
例如，$\Omega(300) = 5$，$s(300) = 2+2+3+5+5 = 17$。

记$f(n)$为所有满足$\Omega(p)=\Omega(q)$和$s(p)+s(q)=n$的汉明数对$(p,q)$的数目。
已知$f(10)=4$（包括$(4,9),(5,5),(6,6),(9,4)$），$f(10^2)=3629$。

求$f(10^7) \bmod 1\ 000\ 000\ 007$。

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
参考常量: PE_ANSWER = 290872710
