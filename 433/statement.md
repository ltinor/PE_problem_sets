# 欧几里德算法的步数（PE 433）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=433](https://projecteuler.net/problem=433)。

记E(x<sub>0</sub>, y<sub>0</sub>)为运用**欧几里德算法**求x<sub>0</sub>和y<sub>0</sub>的最大公约数的步数。更加正式的说：
x<sub>1</sub> = y<sub>0</sub>, y<sub>1</sub> = x<sub>0</sub> mod y<sub>0</sub>
x<sub>n</sub> = y<sub>n-1</sub>, y<sub>n</sub> = x<sub>n-1</sub> mod y<sub>n-1</sub>
E(x<sub>0</sub>, y<sub>0</sub>)是使得y<sub>n</sub> = 0的最小的n。

已知E(1,1) = 1，E(10,6) = 3以及E(6,10) = 4。

对于1 ≤ x,y ≤ N，定义S(N)为所有E(x,y)的和。
已知S(1) = 1，S(10) = 221以及S(100) = 39826。

求S(5·10<sup>6</sup>)。

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

