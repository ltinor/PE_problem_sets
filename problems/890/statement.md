# Problem 890（PE 890）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=890](https://projecteuler.net/problem=890)。

## **Binary Partitions**

Let $p(n)$ be the number of ways to write $n$ as the sum of powers of two, ignoring order.

For example, $p(7) = 6$, the partitions being
$$
\begin{aligned}
7 & = 1+1+1+1+1+1+1 \\\\
  & =1+1+1+1+1+2 \\\\
  & =1+1+1+2+2 \\\\
  & =1+1+1+4 \\\\
  & =1+2+2+2 \\\\
  & =1+2+4
\end{aligned}
$$
You are also given $p(7^7) \equiv 144548435 \pmod {10^9+7}$.

Find $p(7^{777})$. Give your answer modulo $10^9 + 7$.

## **二进制分拆**

记$p(n)$为将$n$写成二的幂之和的方法数，不计顺序。

例如，$p(7) = 6$，对应的分拆包括：
$$
\begin{aligned}
7 & = 1+1+1+1+1+1+1 \\\\
& =1+1+1+1+1+2 \\\\
& =1+1+1+2+2 \\\\
& =1+1+1+4 \\\\
& =1+2+2+2 \\\\
& =1+2+4
\end{aligned}
$$
已知$p(7^7) \equiv 144548435 \pmod {10^9+7}$。

求$p(7^{777})$，并对$10^9 + 7$取余作为你的答案。

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
参考常量: PE_ANSWER = 120592557LL
