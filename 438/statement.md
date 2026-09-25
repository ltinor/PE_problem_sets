# 多项式方程式解的整数部分（PE 438）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=438](https://projecteuler.net/problem=438)。

对于整数n元组t = (a<sub>1</sub>, ..., a<sub>n</sub>)，记(x<sub>1</sub>, ..., x<sub>n</sub>)是多项式方程x<sup>n</sup> + a<sub>1</sub>x<sup>n-1</sup> + a<sub>2</sub>x<sup>n-2</sup> + ... + a<sub>n-1</sub>x + a<sub>n</sub> = 0的解集。

考虑下面两个条件：
- x<sub>1</sub>, ..., x<sub>n</sub>均为实数。
- 如果 x<sub>1</sub>, ..., x<sub>n</sub>是从小到大排序的，则[x<sub>i</sub>] = i对1 ≤ i ≤ n恒成立。（[·]指向下取整函数。）

当n = 4时，有12个整数n元组同时满足这两个条件。
记S(t)是t中整数的绝对值的和。
当n = 4时，对于所有同时满足这两个条件的整数n元组t，可以验证∑S(t) = 2087。

当n = 7时，求∑S(t)。

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
参考常量: N = 7
