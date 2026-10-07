# 总计函数台阶序列（PE 337）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=337](https://projecteuler.net/problem=337)。

记{a<sub>1</sub>, a<sub>2</sub>,..., a<sub>n</sub>}是长度为n且满足以下条件的整数序列：
- a<sub>1</sub> = 6
- 对于所有1 ≤ i &lt; n：φ(a<sub>i</sub>) &lt; φ(a<sub>i+1</sub>) &lt; a<sub>i</sub> &lt; a<sub>i+1</sub> <sup>1</sup>

记S(N)为满足a<sub>n</sub> ≤ N的这类序列的数目。
例如，S(10) = 4：{6}、{6, 8}、{6, 8, 9}和{6, 10}。
我们可以验证S(100) = 482073668以及S(10 000) mod 10<sup>8</sup> = 73808307。

求S(20 000 000) mod 10<sup>8</sup>。

<sup>1</sup> φ表示<b>欧拉总计函数</b>.

---

## 输入格式

输入 N。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
