# Problem 778（PE 778）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=778](https://projecteuler.net/problem=778)。

## **Freshman's Product**

If $a,b$ are two nonnegative integers with decimal representations $a=(\dots a_2a_1a_0)$ and $b=(\dots b_2b_1b_0)$ respectively, then the <i>freshman's product</i> of $a$ and $b$, denoted $a\boxtimes b$, is the integer $c$ with decimal representation $c=(\dots c_2c_1c_0)$ such that $c_i$ is the last digit of $a_i\cdot b_i$.<br />
For example, $234 \boxtimes 765 = 480$.

Let $F(R,M)$ be the sum of $x_1 \boxtimes \dots \boxtimes x_R$ for all sequences of integers $(x_1,\dots,x_R)$ with $0\leq x_i \leq M$.<br />
For example, $F(2, 7) = 204$, and $F(23, 76) \equiv 5870548 \pmod{1\ 000\ 000\ 009}$.

Find $F(234567,765432)$, give your answer modulo $1\ 000\ 000\ 009$.

## **初学者乘积**

若$a$和$b$是两个非负整数，其十进制表示分别是$a=(\dots a_2a_1a_0)$和$b=(\dots b_2b_1b_0)$，则$a$和$b$的<i class=zh>初学者乘积</i>，记为$a\boxtimes b$，是另一个整数$c$，其十进制表示为$c=(\dots c_2c_1c_0)$，其中$c_i$是$a_i\cdot b_i$的末位数字。<br />
例如，$234 \boxtimes 765 = 480$。

对于所有满足$0\leq x_i \leq M$的整数列$(x_1,\dots,x_R)$，记$F(R,M)$为$x_1 \boxtimes \dots \boxtimes x_R$之和。<br />
例如，$F(2, 7) = 204$，$F(23, 76) \equiv 5870548 \pmod{1\ 000\ 000\ 009}$。

求$F(234567,765432)$，并将你的答案对$1\ 000\ 000\ 009$取余。

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

