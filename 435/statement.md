# 斐波那契数多项式（PE 435）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=435](https://projecteuler.net/problem=435)。

<strong>斐波那契数</strong>{f<sub>n</sub>, n ≥ 0}由递归式f<sub>n</sub> = f<sub>n-1</sub> + f<sub>n-2</sub>给出，初值是f<sub>0</sub> = 0和f<sub>1</sub> = 1。

定义多项式{F<sub>n</sub>, n ≥ 0}为F<sub>n</sub>(x) = ∑f<sub>i</sub>x<sup>i</sup>，其中0 ≤ i ≤ n。

例如，F<sub>7</sub>(x) = x + x<sup>2</sup> + 2x<sup>3</sup> + 3x<sup>4</sup> + 5x<sup>5</sup> + 8x<sup>6</sup> + 13x<sup>7</sup>，而F<sub>7</sub>(11) = 268357683.

取n = 10<sup>15</sup>。求[∑<sub>0≤x≤100</sub> F<sub>n</sub>(x)] mod 1307674368000 (= 15!)。

---

## 输入格式

参数模式：输入 mode x max_x。
- 字符 `PE`：输出原题官方答案。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
参考常量: PE_N = 1000000000000000LL
