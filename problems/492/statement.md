# 爆炸序列（PE 492）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=492](https://projecteuler.net/problem=492)。

定义序列 a<sub>1</sub>, a<sub>2</sub>, a<sub>3</sub>, ... 如下：
- a<sub>1</sub> = 1
- a<sub>n+1</sub> = 6a<sub>n</sub><sup>2</sup> + 10a<sub>n</sub> + 3 for n ≥ 1.

例如：
a<sub>3</sub> = 2359
a<sub>6</sub> = 269221280981320216750489044576319
a<sub>6</sub> mod 1&nbsp;000&nbsp;000&nbsp;007 = 203064689
a<sub>100</sub> mod 1&nbsp;000&nbsp;000&nbsp;007 = 456482974

对所有满足x ≤ p ≤ x+y的素数p，定义B(x,y,n)等于∑ (a<sub>n</sub> mod p)。

例如：
B(10<sup>9</sup>, 10<sup>3</sup>, 10<sup>3</sup>) = 23674718882
B(10<sup>9</sup>, 10<sup>3</sup>, 10<sup>15</sup>) = 20731563854

求B(10<sup>9</sup>, 10<sup>7</sup>, 10<sup>15</sup>)。

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
