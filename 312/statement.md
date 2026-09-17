# 谢尔宾斯基图的回路（PE 312）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=312](https://projecteuler.net/problem=312)。

1阶**谢尔宾斯基图**（S<sub>1</sub>）是一个等边三角形。
将三个S<sub>n</sub>摆在一起，使得任意两个S<sub>n</sub>都共用一个角，就得到了S<sub>n+1</sub>。

<center><img src="/resources/images/0312_sierpinskyAt.gif"></center>

记C(n)是经过S<sub>n</sub>中所有顶点恰好一次的回路的数目。
例如，C(3) = 8，因为在S<sub>3</sub>上恰好可以画出8条这样的回路，如下图所示：

<center><img src="/resources/images/0312_sierpinsky8t.gif"></center>

同样可以验证：
C(1) = C(2) = 1
C(5) = 71328803586048
C(10 000) mod 10<sup>8</sup> = 37652224
C(10 000) mod 13<sup>8</sup> = 617720485

求C(C(C(10 000))) mod 13<sup>8</sup>。

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

