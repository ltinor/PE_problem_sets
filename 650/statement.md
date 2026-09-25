# Problem 650（PE 650）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
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

字符 `PE`：输出原题官方答案。

## 输出格式

原题官方答案。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
参考常量: PE_ANSWER = 538319652
