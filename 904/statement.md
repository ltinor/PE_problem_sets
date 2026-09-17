# Problem 904（PE 904）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=904](https://projecteuler.net/problem=904)。

## **Pythagorean Angle**

Given a right-angled triangle with integer sides, the smaller angle formed by the two medians drawn on the the two perpendicular sides is denoted by $\theta$.

<div style="text-align:center;"><img src="/resources/images/0904_pythagorean_angle.png?1723895050" alt="0904_Pythagorean_angle.jpg"></div>

Let $f(\alpha, L)$ denote the sum of the sides of the right-angled triangle minimizing the absolute difference between $\theta$ and $\alpha$ among all right-angled triangles with integer sides and hypotenuse not exceeding $L$.<br/>
If more than one triangle attains the minimum value, the triangle with the maximum area is chosen. All angles in this problem are measured in degrees.

For example, $f(30,10^2)=198$ and $f(10,10^6)= 1600158$.

Define $F(N,L)=\sum_{n=1}^{N}f\left(\sqrt[3]{n},L\right)$.<br/>
You are given $F(10,10^6)= 16684370$.

Find $F(45000, 10^{10})$.

## **毕达哥拉斯角**

给定一个各边长为整数的直角三角形，在其两条相互垂直的边上各画一条中线，这两条中线交叉所形成的较小角记为$\theta$。

<div style="text-align:center;"><img src="/resources/images/0904_pythagorean_angle.png?1723895050" alt="0904_Pythagorean_angle.jpg"></div>

令$f(\alpha, L)$表示，在所有各边长为整数且斜边不超过$L$的直角三角形中，使$\theta$与$\alpha$的绝对差值最小的三角形的各边长之和。<br/>
如果最小绝对差值对应多个三角形，则选择其中面积最大的一个。本题中的所有角度均以度数表示。

例如，$f(30,10^2)=198$，$f(10,10^6)= 1600158$。

定义$F(N,L)=\sum_{n=1}^{N}f\left(\sqrt[3]{n},L\right)$。<br/>
已知$F(10,10^6)= 16684370$。

求$F(45000, 10^{10})$。

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

