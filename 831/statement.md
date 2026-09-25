# Problem 831（PE 831）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=831](https://projecteuler.net/problem=831)。

## **Triple Product**

Let $g(m)$ be the integer defined by the following double sum of products of binomial coefficients:

$$\sum_{j=0}^m\sum_{i = 0}^j (-1)^{j-i}\binom mj \binom ji \binom{j+5+6i}{j+5}.$$

You are given that $g(10) = 127278262644918$.<br />
Its first (most significant) five digits are $12727$.<br />
Find the first ten digits of $g(142857)$ when written in base $7$.

## **三个二项式系数的乘积**

记$g(m)$为如下表达式（对一系列二项式系数的乘积进行双重求和）所定义的整数：

$$\sum_{j=0}^m\sum_{i = 0}^j (-1)^{j-i}\binom mj \binom ji \binom{j+5+6i}{j+5}.$$

已知$g(10) = 127278262644918$。<br />
它的前五位数字是$12727$。<br />
求$g(142857)$的$7$进制表示的前十位数字。

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
参考常量: PE_ANSWER = 223153684303778LL
