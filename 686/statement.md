# Problem 686（PE 686）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=686](https://projecteuler.net/problem=686)。

## **Powers of Two**

$2^7=128$ is the first power of two whose leading digits are "$12$".
The next power of two whose leading digits are "$12$" is $2^{80}$.

Define $p(L, n)$ to be the $n$th-smallest value of $j$ such that the base $10$ representation of $2^j$ begins with the digits of $L$.
So $p(12, 1) = 7$ and $p(12, 2) = 80$.

You are also given that $p(123, 45) = 12710$.

Find $p(123, 678910)$.

## **二的幂**

在二的幂中，第一个拥有前导数字“$12$”的是$2^7=128$。下一个拥有前导数字“$12$”的二的幂是$2^{80}$。

记$p(L, n)$为第$n$个使得$10$进制表示的$2^j$拥有前导数字$L$的数$j$。
因此$p(12, 1) = 7$，$p(12, 2) = 80$。

已知$p(123, 45) = 12710$。

求$p(123, 678910)$。

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
参考常量: PE_ANSWER = 193060223
