# 无理数进制（PE 558）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=558](https://projecteuler.net/problem=558)。

记r为方程x<sup>3</sup>=x<sup>2</sup>+1的实根。
每一个正整数都能表示成r的不同幂的和。
如果我们要求级数只有有限项，而且任意两项的指数至少相差3，这样的表示是唯一的。
例如，3=r<sup>-10</sup>+r<sup>-5</sup>+r<sup>-1</sup>+r<sup>2</sup>，而10=r<sup>-10</sup>+r<sup>-7</sup>+r<sup>6</sup>。
有趣的是，这个关系对于上述方程的复根也成立。

记w(n)为n的上述唯一表示中的项数，因此w(3)=4而w(10)=3。

更正式地，对于所有正整数n，我们有：
n = $\displaystyle \sum\_{k=-\infty}^{\infty}$ b<sub>k</sub>r<sup>k</sup>
其中：
对于所有k，b<sub>k</sub>要么是0要么是1；
对于所有k，b<sub>k</sub>+b<sub>k+1</sub>+b<sub>k+2</sub>≤1；
w(n) = $\displaystyle \sum\_{k=-\infty}^{\infty}$ b<sub>k</sub>是有限的。

记S(m)= $\displaystyle \sum\_{j=1}^{m}$w(j<sup>2</sup>)。
已知S(10) = 61以及S(1000) = 19403。

求S(5 000 000)。

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

