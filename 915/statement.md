# Problem 915（PE 915）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=915](https://projecteuler.net/problem=915)。

## **Giant GCDs**

The function $s(n)$ is defined recursively for positive integers by $s(1) = 1$ and $s(n+1) = \big(s(n) - 1\big)^3 +2$ for $n\geq 1$. <br/>
The sequence begins: $s(1) = 1, s(2) = 2, s(3) = 3, s(4) = 10, \ldots$.

For positive integers $N$, define 
$$T(N) = \sum_{a=1}^N \sum_{b=1}^N \gcd\Big(s\big(s(a)\big), s\big(s(b)\big)\Big).$$  
You are given $T(3) = 12$, $T(4) \equiv 24881925$ and $T(100)\equiv 14416749$ both modulo $123456789$.

Find $T(10^8)$. Give your answer modulo $123456789$.

## **超大的最大公约数**

对正整数递归定义函数$s(n)$如下：$s(1) = 1$；对$n\geq 1$，$s(n+1) = \big(s(n) - 1\big)^3 +2$。<br/>
该序列的最初几项分别是：$s(1) = 1, s(2) = 2, s(3) = 3, s(4) = 10, \ldots$。

对正整数$N$，定义 
$$T(N) = \sum_{a=1}^N \sum_{b=1}^N \gcd\Big(s\big(s(a)\big), s\big(s(b)\big)\Big).$$ 
已知$T(3) = 12$，$T(4) \equiv 24881925$，$T(100)\equiv 14416749$（对$123456789$取模）。

求$T(10^8)$，并对$123456789$取余作为你的答案。

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
