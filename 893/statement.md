# Problem 893（PE 893）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=893](https://projecteuler.net/problem=893)。

## **Matchsticks**

Define $M(n)$ to be the minimum number of matchsticks needed to represent the number $n$.

A number can be represented in digit form or as an expression involving addition and/or multiplication. Also order of operations must be followed, that is multiplication binding tighter than addition. Any other symbols or operations, such as brackets, subtraction, division or exponentiation, are not allowed.

The valid digits and symbols are shown below:

<div style="text-align:center;"><img src="/resources/images/0893_DigitDiagram.jpg?1714876316" alt="0893_DigitDiagram.jpg" height="433" width="668"></div>

For example, $28$ needs $12$ matchsticks to represent it in digit form but representing it as $4\times 7$ would only need $9$ matchsticks and as there is no way using fewer matchsticks $M(28) = 9$.

Define $\displaystyle T(N) = \sum_{n=1}^N M(n)$. You are given $T(100) = 916$.

Find $T(10^6)$.

## **火柴棍**

定义$M(n)$为表示数$n$所需的最少火柴棒数量。

一个数既可以用数字形式表示，也可以用涉及加法和/或乘法的表达式表示，但必须遵守运算顺序，即乘法优先于加法。不允许使用任何其他符号或运算，如括号、减法、除法或幂运算。

有效的数字和符号如下所示：

<div style="text-align:center;"><img src="/resources/images/0893_DigitDiagram.jpg?1714876316" alt="0893_DigitDiagram.jpg" height="433" width="668"></div>

<i class=zh>译注：最下排分别是“加号”和“乘号”。</i>

例如，$28$用数字形式表示需要$12$根火柴棍，但将其表示为$4\times 7$只需要$9$根火柴棍，且不存在使用更少火柴棍的表示方法，因此$M(28) = 9$。

定义$\displaystyle T(N) = \sum_{n=1}^N M(n)$。已知$T(100) = 916$。

求$T(10^6)$。

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

