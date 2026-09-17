# Problem 786（PE 786）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=786](https://projecteuler.net/problem=786)。

## **Billiard**

The following diagram shows a billiard table of a special quadrilateral shape. The four angles $A, B, C, D$ are $120^\circ, 90^\circ, 60^\circ, 90^\circ$ respectively, and the lengths $AB$ and $AD$ are equal.

![](/resources/images/0786_billiard_shape.jpg)

The diagram on the left shows the trace of an infinitesimally small billiard ball, departing from point $A$, bouncing twice on the edges of the table, and finally returning back to point $A$. The diagram on the right shows another such trace, but this time bouncing eight times:

![](/resources/images/0786_billiard_traces.jpg)

The table has no friction and all bounces are perfect elastic collisions.
Note that no bounce should happen on any of the corners, as the behaviour would be unpredictable.

Let $B(N)$ be the number of possible traces of the ball, departing from point $A$, bouncing at most $N$ times on the edges and returning back to point $A$.

For example, $B(10) = 6$, $B(100) = 478$, $B(1000) = 45790$.

Find $B(10^9)$.

## **台球**

下图展示了一张特别的四边形台球桌。其四个角$A, B, C, D$分别为$120^\circ, 90^\circ, 60^\circ, 90^\circ$，且边$AB$和$AD$等长。

![](/resources/images/0786_billiard_shape.jpg)

下图左侧展示了由$A$点出发的一颗任意小的台球，沿桌边反弹两次后回到$A$点的路径。下图右侧则展示了另一条从$A$点出发反弹八次回到起点的路径。

![](/resources/images/0786_billiard_traces.jpg)

假设桌面没有摩擦，且每次反弹均是完美碰撞。
注意反弹不能发生在任意一个角上，因为此时台球的运动行为将会无法预测。

记$B(N)$为台球从$A$点出发，反弹至多$N$次后返回$A$点的所有可能的路径数目。

例如，$B(10) = 6$，$B(100) = 478$，$B(1000) = 45790$。

求$B(10^9)$。

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

