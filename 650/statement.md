# Problem 650（PE 650）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=650](https://projecteuler.net/problem=650)。

## **Divisors of Binomial Product**

Let $B(n)=\displaystyle\prod_{k=0}^n {n \choose k}$, a product of binomial coefficients.
For example, 
$B(5)={5 \choose 0} \times {5 \choose 1} \times {5 \choose 2} \times {5\choose 3}\times {5 \choose 4}\times {5 \choose 5} = 1\times 5\times 10\times 10\times 5\times 1=2500$.

Let $D(n)=\displaystyle \sum_{d|B(n)}d$, the sum of the divisors of $B(n)$.
For example, the divisors of $B(5)$ are $1$, $2$, $4$, $5$, $10$, $20$, $25$, $50$, $100$, $125$, $250$, $500$, $625$, $1250$ and $2500$,
so $D(5) = 1 + 2 + 4 + 5 + 10 + 20 + 25 + 50 + 100 + 125 + 250 + 500 + 625 + 1250 + 2500 = 5467$.

Let $S(n)=\displaystyle \sum_{k=1}^n D(k)$.
You are given $S(5)=5736$, $S(10)=141740594713218418$ and $S(100) \mod 1\ 000\ 000\ 007=332792866$.

Find $S(20\ 000) \mod 1\ 000\ 000\ 007$.

## **二项式系数乘积的因数**

记$B(n)=\displaystyle\prod_{k=0}^n {n \choose k}$为二项式系数的乘积。
例如，
$B(5)={5 \choose 0} \times {5 \choose 1} \times {5 \choose 2} \times {5\choose 3}\times {5 \choose 4}\times {5 \choose 5} = 1\times 5\times 10\times 10\times 5\times 1=2500$。

记$D(n)=\displaystyle \sum_{d|B(n)}d$为$B(n)$的因数和。
例如，$B(5)$的因数有$1$、$2$、$4$、$5$、$10$、$20$、$25$、$50$、$100$、$125$、$250$、$500$、$625$、$1250$和$2500$，
因此$D(5) = 1 + 2 + 4 + 5 + 10 + 20 + 25 + 50 + 100 + 125 + 250 + 500 + 625 + 1250 + 2500 = 5467$。

记$S(n)=\displaystyle \sum_{k=1}^n D(k)$。
已知$S(5)=5736$，$S(10)=141740594713218418$，$S(100) \mod 1\ 000\ 000\ 007=332792866$。

求$S(20\ 000) \mod 1\ 000\ 000\ 007$。

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

