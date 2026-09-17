# 翻滚的椭圆（PE 525）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=525](https://projecteuler.net/problem=525)。

椭圆E(a, b)的初始位置由以下方程给出：
$\frac{x^2}{a^2}+\frac{(y-b)^2}{b^2}=1$

椭圆沿着x轴无滑动地滚动一周。有趣的是，椭圆焦点的运动轨迹长度与椭圆短轴的长度无关：
$F(a,b)=2\pi max(a,b)$

<center><img src="/resources/images/0525-rolling-ellipse-1.gif" alt="p525-rolling-ellipse-1.gif"></center>

对于椭圆中心而言则并非如此；记C(a,b)为椭圆无滑动地滚动一周时椭圆中心的运动轨迹长度。

<center><img src="/resources/images/0525-rolling-ellipse-2.gif" alt="p525-rolling-ellipse-2.gif"></center>

已知C(2, 4) ~ 21.38816906。

求C(1, 4) + C(3, 4)。将你的答案四舍五入到小数点后8位小数，即格式为ab.cdefghij。

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

