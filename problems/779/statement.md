# Problem 779（PE 779）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=779](https://projecteuler.net/problem=779)。

## **Prime Factor and Exponent**

For a positive integer $n>1$, let $p(n)$ be the smallest prime dividing $n$, and let $\alpha(n)$ be its <b><i>p</i>-adic order</b>, i.e. the largest integer such that $p(n)^{\alpha(n)}$ divides $n$.

For a positive integer $K$, define the function $f_K(n)$ by:

$$\displaystyle f_K(n)=\frac{\alpha(n)-1}{(p(n))^K}$$

Also define $\overline{f_K}$ by:

$$\displaystyle \overline{f_K}=\lim_{N \to \infty} \frac{1}{N}\sum_{n=2}^{N} f_K(n)$$

It can be verified that $\overline{f_1} \approx 0.282419756159$.

Find $\displaystyle \sum_{K=1}^{\infty}\overline{f_K}$. Give your answer rounded to $12$ digits after the decimal point.

## **质因数及其指数**

对于正整数$n>1$，记$p(n)$为整除$n$的最小质数，并记$\alpha(n)$为$n$的<b><i>p</i>进数</b>，也即使得$p(n)^{\alpha(n)}$整除$n$的最大整数。

对于正整数$K$，定义函数$f_K(n)$为：

$$\displaystyle f_K(n)=\frac{\alpha(n)-1}{(p(n))^K}$$

再定义$\overline{f_K}$为：

$$\displaystyle \overline{f_K}=\lim_{N \to \infty} \frac{1}{N}\sum_{n=2}^{N} f_K(n)$$

可以验证，$\overline{f_1} \approx 0.282419756159$。

求$\displaystyle \sum_{K=1}^{\infty}\overline{f_K}$，并将你的答案保留$12$位小数。

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
