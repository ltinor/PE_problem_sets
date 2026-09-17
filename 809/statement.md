# Problem 809（PE 809）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=809](https://projecteuler.net/problem=809)。

## **Rational Recurrence Relation**

The following is a function defined for all positive rational values of $x$.
$$	f(x)=\begin{cases} x  & x\text{ is integral}\\\\
					f(\frac 1{1-x})	& x \lt 1\\\\
					f\Big(\frac 1{\lceil x\rceil -x}-1+f(x-1)\Big)	& \text{otherwise}\end{cases}	$$

For example, $f(3/2)=3$, $f(1/6) = 65533$ and $f(13/10) = 7625597484985$.

Find $f(22/7)$. Give your answer modulo $10^{15}$.

## **有理数递归关系式**

如下是定义在所有正有理数$x$上的函数：
$$	f(x)=\begin{cases} x  & \text{若}x\text{是整数}\\\\
					f(\frac 1{1-x})	& \text{若}x \lt 1\\\\
					f\Big(\frac 1{\lceil x\rceil -x}-1+f(x-1)\Big)	& \text{其余情况}\end{cases}	$$

例如，$f(3/2)=3$，$f(1/6) = 65533$，$f(13/10) = 7625597484985$。

求$f(22/7)$，并将你的答案对$10^{15}$取余。

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

