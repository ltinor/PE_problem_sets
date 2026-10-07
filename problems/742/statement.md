# Problem 742（PE 742）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=742](https://projecteuler.net/problem=742)。

## **Minimum area of a convex grid polygon**

A <i>symmetrical convex grid polygon</i> is a polygon such that:
- All its vertices have integer coordinates.
- All its internal angles are strictly smaller than $180^\circ$.
- It has both horizontal and vertical symmetry.

For example, the left polygon is a convex grid polygon which has neither horizontal nor vertical symmetry, while the right one is a valid symmetrical convex grid polygon with six vertices:

![](/resources/images/0742_hexagons.jpg)

Define $A(N)$, the minimum area of a symmetrical convex grid polygon with $N$ vertices.

You are given $A(4) = 1$, $A(8) = 7$, $A(40) = 1039$ and $A(100) = 17473$.

Find $A(1000)$.

## **格点凸多边形的最小面积**

<i class=zh>对称格点凸多边形</i>是指满足以下条件的多边形：
- 所有顶点的坐标均为整数。
- 所有内角严格小于$180^\circ$。
- 在水平和竖直方向上对称。

例如，下图左的多边形是格点凸多边形，但是在水平和竖直方向上均不对称；而下图右的多边形则是一个有六个顶点的对称格点凸多边形：

![](/resources/images/0742_hexagons.jpg)

记$A(N)$为所有有$N$个顶点的对称格点凸多边形的最小面积。

已知$A(4) = 1$，$A(8) = 7$，$A(40) = 1039$，$A(100) = 17473$。

求$A(1000)$。

---

## 输入格式

字符 `PE`：输出原题官方答案。

## 输出格式

原题官方答案。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
参考常量: PE_ANSWER = 18397727LL
