# Problem 570（PE 570）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=570](https://projecteuler.net/problem=570)。

## **Snowflakes**

A snowflake of order n is formed by overlaying an equilateral triangle (rotated by 180 degrees) onto each equilateral triangle of the same size in a snowflake of order n-1. A snowflake of order 1 is a single equilateral triangle.

<center><img src="/resources/images/0570-slowflakes.png" alt="p570-slowflakes.png"></center>

Some areas of the snowflake are overlaid repeatedly. In the above picture, blue represents the areas that are one layer thick, red two layers thick, yellow three layers thick, and so on. 

For an order n snowflake, let A(n) be the number of triangles that are one layer thick, and let B(n) be the number of triangles that are three layers thick. Define G(n) = gcd(A(n), B(n)).

E.g. A(3) = 30, B(3) = 6, G(3)=6
A(11) = 3027630, B(11) = 19862070, G(11) = 30

Further, G(500) = 186 and  $\sum_{n=3}^{500}G(n)=5124$

Find $\displaystyle \sum_{n=3}^{10^7}G(n)$.

## **雪花**

将n-1阶雪花中每个等边三角形旋转180度，再覆盖到其本身上，就得到了一个n阶雪花；而最初的1阶雪花就是一个等边三角形。

<center><img src="/resources/images/0570-slowflakes.png" alt="p570-slowflakes.png"></center>

雪花中的部分区域会被多次覆盖。在上图中，蓝色的区域的厚度为一，红色的区域为二，黄色的区域为三，依此类推。

对于n阶雪花，记A(n)为厚度为一的三角形的数量，B(n)为厚度为三的三角形的数量。令G(n) = gcd(A(n), B(n))。

例如，A(3) = 30，B(3) = 6，G(3)=6
A(11) = 3027630，B(11) = 19862070，G(11) = 30

进一步地，G(500) = 186，而$\sum_{n=3}^{500}G(n)=5124$

求$\displaystyle \sum_{n=3}^{10^7}G(n)$。

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

