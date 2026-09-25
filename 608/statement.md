# Problem 608（PE 608）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=608](https://projecteuler.net/problem=608)。

## **Divisor Sums**

Let $D(m,n)=\displaystyle\sum\_{d|m}\sum\_{k=1}^n\sigma\_{\small 0}(kd)$ where $d$ runs through all divisors of $m$ and $\sigma\_{\small 0}(n)$ is the number of divisors of $n$.
You are given $D(3!,10^2)=3398$ and $D(4!,10^6)=268882292$.

Find $D(200!,10^{12}) \text{ mod } (10^9 + 7)$.

## **因数和**

记$D(m,n)=\displaystyle\sum\_{d|m}\sum\_{k=1}^n\sigma\_{\small 0}(kd)$，其中$d$取遍$m$的所有因数，而$\sigma\_{\small 0}(n)$表示$n$的因数数目。
已知$D(3!,10^2)=3398$以及$D(4!,10^6)=268882292$。

求$D(200!,10^{12}) \text{ mod } (10^9 + 7)$。

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
参考常量: PE_ANSWER = 439689828LL
