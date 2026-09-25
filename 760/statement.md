# Problem 760（PE 760）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=760](https://projecteuler.net/problem=760)。

## **Sum over Bitwise Operators**

Define
$$\displaystyle g(m,n) = (m\oplus n)+(m\vee n)+(m\wedge n)$$
where $\oplus, \vee, \wedge$ are the bitwise XOR, OR and AND operator respectively.

Also set
$$\displaystyle G(N) = \sum_{n=0}^N\sum_{k=0}^n g(k,n-k)$$

For example, $G(10) = 754$ and $G(10^2) = 583766$.

Find $G(10^{18})$. Give your answer modulo $1\ 000\ 000\ 007$.

## **位运算求和**

记
$$\displaystyle g(m,n) = (m\oplus n)+(m\vee n)+(m\wedge n)$$
其中$\oplus, \vee, \wedge$分别代表“按位异或”、“按位或”和“按位与”运算。

再记
$$\displaystyle G(N) = \sum_{n=0}^N\sum_{k=0}^n g(k,n-k)$$

例如，$G(10) = 754$，$G(10^2) = 583766$。

求$G(10^{18})$，并将你的答案对$1\ 000\ 000\ 007$取余。

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
