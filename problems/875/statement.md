# Problem 875（PE 875）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=875](https://projecteuler.net/problem=875)。

## **Quadruple Congruence**

For a positive integer $n$ we define $q(n)$ to be the number of solutions to:

$$a_1^2+a_2^2+a_3^2+a_4^2 \equiv b_1^2+b_2^2+b_3^2+b_4^2 \pmod n$$

where $0 \leq a_i, b_i \lt n$. For example, $q(4)= 18432$.

Define $\displaystyle Q(n)=\sum_{i=1}^{n}q(i)$. You are given $Q(10)=18573381$.

Find $Q(12345678)$. Give your answer modulo $1001961001$.

## **四重同余**

对于正整数$n$，定义$q(n)$为如下同余方程的解的数目：
$$a_1^2+a_2^2+a_3^2+a_4^2 \equiv b_1^2+b_2^2+b_3^2+b_4^2 \pmod n$$
其中$0 \leq a_i, b_i \lt n$。例如，$q(4)= 18432$。

定义$\displaystyle Q(n)=\sum_{i=1}^{n}q(i)$。已知$Q(10)=18573381$。

求$Q(12345678)$，并对$1001961001$取余作为你的答案。

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
参考常量: PE_ANSWER = 130702327LL
