# Problem 727（PE 727）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=727](https://projecteuler.net/problem=727)。

## **Triangle of Circular Arcs**

Let $r_a$, $r_b$ and $r_c$ be the radii of three circles that are mutually and externally tangent to each other. The three circles then form a <i>triangle of circular arcs</i> between their tangency points as shown for the three blue circles in the picture below.

![CircularArcs](/resources/images/0727_circular_arcs.jpg)

Define the circumcircle of this triangle to be the red circle, with centre $D$, passing through their tangency points. Further define the incircle of this triangle to be the green circle, with centre $E$, that is mutually and externally tangent to all the three blue circles. Let $d=\vert DE \vert$ be the distance between the centres of the circumcircle and the incircle.

Let $\mathbb{E}(d)$ be the expected value of $d$ when $r_a$, $r_b$ and $r_c$ are integers chosen uniformly such that $1\leq r_a<r_b<r_c \le 100$ and $\text{gcd}(r_a,r_b,r_c)=1$.

Find $\mathbb{E}(d)$, rounded to eight places after the decimal point.

## **圆弧三角形**

三个半径为$r_a$、$r_b$和$r_c$的圆两两外切，在切点之间构成了一个<i class=zh>圆弧三角形</i>，如下图的三个蓝色圆所示。

![圆弧](/resources/images/0727_circular_arcs.jpg)

记圆弧三角形的外接圆为上图中的红色圆，圆心点为$D$且过三个切点。再记圆弧三角形的内切圆为上图中的绿色圆，圆心点为$E$且与三个蓝色圆外切。记$d=\vert DE \vert$为外接圆和内切圆的圆心距。

若$r_a$、$r_b$和$r_c$均为在$1\leq r_a<r_b<r_c \le 100$范围内随机均匀抽取的整数且满足$\text{gcd}(r_a,r_b,r_c)=1$，记$\mathbb{E}(d)$为$d$的期望值。

求$\mathbb{E}(d)$并保留小数点后八位数字。

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

