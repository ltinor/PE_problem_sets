# Problem 697（PE 697）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=697](https://projecteuler.net/problem=697)。

## **Randomly Decaying Sequence**

Given a fixed real number $c$, define a random sequence $(X_n)_{n\ge 0}$ by the following random process:
- $X_0 = c$ (with probability 1).
- For $n>0$, $X_n = U_n X_{n-1}$ where $U_n$ is a real number chosen at random between zero and one, uniformly, and independently of all previous choices $(U_m)_{m<n}$.

If we desire there to be precisely a $25\%$ probability that $X_{100}<1$, then this can be arranged by fixing $c$ such that $\log_{10} c \approx 46.27$.

Suppose now that $c$ is set to a different value, so that there is precisely a  $25\%$ probability that $X_{10\ 000\ 000}<1$.

Find $\log_{10} c$ and give your answer rounded to two places after the decimal point.

## **随机递减序列**

给定实数$c$，如下的随机过程可以生成一个随机序列$(X_n)_{n\ge 0}$：
- $X_0 = c$ （概率为1）。
- 对于所有$n>0$，$X_n = U_n X_{n-1}$，其中$U_n$是在$0$到$1$之间均匀随机选择的实数，且与之前所有的$(U_m)_{m<n}$独立。

如果我们希望$X_{100}<1$的概率恰好为$25\%$，我们只需选择满足$\log_{10} c \approx 46.27$的实数$c$。

假设现在我们希望$X_{10\ 000\ 000}<1$的概率恰好为 $25\%$，我们需要给$c$选择一个不同的数值。

求$\log_{10} c$并将你的答案保留小数点后两位。

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

