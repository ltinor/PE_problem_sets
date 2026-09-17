# Problem 901（PE 901）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=901](https://projecteuler.net/problem=901)。

## **Well Drilling**

A driller drills for water. At each iteration the driller chooses a depth $d$ (a positive real number), drills to this depth and then checks if water was found. If so, the process terminates. Otherwise, a new depth is chosen and a new drilling starts from the ground level in a new location nearby.

Drilling to depth $d$ takes exactly $d$ hours. The groundwater depth is constant in the relevant area and its distribution is known to be an <a href="https://en.wikipedia.org/wiki/Exponential_distribution">exponential random variable</a> with expected value of $1$. In other words, the probability that the groundwater is deeper than $d$ is $e^{-d}$.

Assuming an optimal strategy, find the minimal expected drilling time in hours required to find water. Give your answer rounded to $9$ places after the decimal point.

## **钻井**

一名钻井工人在钻探水源。每一轮，钻井工人选择一个（正实数）深度$d$，一直钻到这个深度，然后检查是否找到水。如果找到了，就结束钻探。否则，工人会在附近找一个新位置，选择一个新的深度，从地面开始新的钻探。

钻到深度$d$需要恰好$d$小时。在这片区域内，地下水的深度是恒定的，且满足期望值为1的<a href="https://zh.wikipedia.org/wiki/%E6%8C%87%E6%95%B0%E5%88%86%E5%B8%83">指数分布</a>。换言之，地下水深度超过$d$的概率是$e^{-d}$。

假设钻井工人采用最优策略，求找到水所需的最小预期钻探时间（以小时为单位），并将你的答案四舍五入保留$9$位小数。

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

