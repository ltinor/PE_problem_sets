# Problem 883（PE 883）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=883](https://projecteuler.net/problem=883)。

## **Remarkable Triangles**

In this problem we consider triangles drawn on a <b>hexagonal lattice</b>, where each lattice point in the plane has six neighbouring points equally spaced around it, all distance $1$ away.

We call a triangle <i>remarkable</i> if
- All three vertices and its <b>incentre</b> lie on lattice points
- At least one of its angles is $60^\circ$

<div style="text-align:center">
<img src="/resources/images/0883_diagram.png" alt="0883_diagram.png">
</div>

Above are four examples of remarkable triangles, with $60^\circ$ angles illustrated in red. Triangles A and B have inradius $1$; C has inradius $\sqrt{3}$; D has inradius $2$.

Define $T(r)$ to be the number of remarkable triangles with inradius $\le r$. Rotations and reflections, such as triangles A and B above, are counted separately; however direct translations are not. That is, the same triangle drawn in different positions of the lattice is only counted once.

You are given $T(0.5)=2$, $T(2)=44$, and $T(10)=1302$.

Find $T(10^6)$.

## **卓越三角形**

本题所考虑的三角形的顶点均在<b>六边形格阵</b>上。六边形格阵是平面上的一种格点阵，其中每个格点周围都有六个相邻的、均匀分布的格点，其距离均为$1$。

所谓<i class=zh>卓越</i>三角形是满足以下条件的三角形：
- 其三个顶点及其<b>内心</b>都落在格点上
- 至少一个角为$60^\circ$

<div style="text-align:center">
<img src="/resources/images/0883_diagram.png" alt="0883_diagram.png">
</div>

如上所示是四个卓越三角形，其$60^\circ$的角被标记为红色。三角形A和B的内接圆半径为$1$，C的内接圆半径为$\sqrt{3}$，而D的内接圆半径为$2$。

记$T(r)$为所有内接圆半径小于等于$r$的卓越三角形的数目。旋转和翻转形成的不同三角形，如上图所示的三角形A和B，在计数时分别计算；而直接平移则不重复计算，也就是说，在格阵不同的位置绘制的完全相同的三角形只计算一次。

已知$T(0.5)=2$，$T(2)=44$，$T(10)=1302$。

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

