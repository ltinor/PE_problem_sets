# 逐渐增长的根（PE 479）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=479](https://projecteuler.net/problem=479)。

记a<sub>k</sub>，b<sub>k</sub>，c<sub>k</sub>分别是方程1/x = (k/x)<sup>2</sup>(k+x<sup>2</sup>) - kx在复数域内的三个根。

例如，对于k = 5，{a<sub>5</sub>, b<sub>5</sub>, c<sub>5</sub>}的近似值为{5.727244, -0.363622+2.057397i, -0.363622-2.057397i}。

对于任意整数p，k满足1 ≤ p, k ≤ n，记S(n) = Σ (a<sub>k</sub>+b<sub>k</sub>)<sup>p</sup>(b<sub>k</sub>+c<sub>k</sub>)<sup>p</sup>(c<sub>k</sub>+a<sub>k</sub>)<sup>p</sup>。

有趣的是，S(n)永远是个整数。例如，S(4) = 51160。

求S(10<sup>6</sup>) modulo 1 000 000 007。

---

## 输入格式

参数模式：输入 n。
- 字符 `PE`：输出原题官方答案。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
