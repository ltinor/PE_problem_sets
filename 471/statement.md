# 椭圆内接三角形（PE 471）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=471](https://projecteuler.net/problem=471)。

三角形ΔABC内接于椭圆$\frac{x^2}{a^2}+\frac{y^2}{b^2}=1$，其中0 < 2b < a，a和b均为整数。

当三角形ΔABC的内接圆圆心是(2b, 0)，且A点坐标是$(\frac{a}{2}, \frac{\sqrt{3}}{2}b)$时，记r(a,b)是三角形ΔABC内接圆的半径。

例如，r(3,1) = ½，r(6,2) = 1，r(12,3) = 2。

<center><img src="/resources/images/0471-triangle-inscribed-in-ellipse-1.png"></center>
<center><img src="/resources/images/0471-triangle-inscribed-in-ellipse-2.png"></center>

记$G(n)=\sum\_{a=3}^{n}\sum\_{b=1}^{\lfloor \frac{a-1}{2} \rfloor}r(a,b)$

已知G(10) = 20.59722222，G(100) = 19223.60980（保留10位有效数字）

求G(1011)。

答案应当用10位有效数字的科学计数法表示，用小写字母e来分割尾数和指数。

例如，G(10)应当写成2.059722222e1。

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

