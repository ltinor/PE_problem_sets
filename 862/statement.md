# Problem 862（PE 862）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=862](https://projecteuler.net/problem=862)。

## **Larger Digit Permutation**

For a positive integer $n$ define $T(n)$ to be the number of strictly larger integers which can be formed by permuting the digits of $n$.

Leading zeros are not allowed and so for $n = 2302$ the total list of permutations would be:
$$2023,2032,2203,2230,\mathbf{2302},2320,3022,3202,3220$$
giving $T(2302)=4$.

Further define $S(k)$ to be the sum of $T(n)$ for all $k$-digit numbers $n$. You are given $S(3) = 1701$.

Find $S(12)$.

## **更大的数字重排（一）**

对于正整数$n$，定义$T(n)$为对$n$的数字进行重排所能得到的严格大于$n$的整数数量。

重排不允许有前导零，因此对于$n = 2302$，所有的合法重排包括：
$$2023,2032,2203,2230,\mathbf{2302},2320,3022,3202,3220$$
因此可得$T(2302)=4$。

再定义$S(k)$为所有的$k$位整数$n$对应的$T(n)$之和。已知$S(3) = 1701$。

求$S(12)$。

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

