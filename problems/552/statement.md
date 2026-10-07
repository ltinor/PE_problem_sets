# 中国剩余定理II（PE 552）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=552](https://projecteuler.net/problem=552)。

记A<sub>n</sub>为满足A<sub>n</sub> mod p<sub>i</sub> = i对所有1 ≤ i ≤ n成立的最小正整数，其中p<sub>i</sub>表示第i个素数。
例如，A<sub>2</sub> = 5，因为5是如下方程组的最小正整数解
- A<sub>2</sub> mod 2 = 1 
- A<sub>2</sub> mod 3 = 2

A<sub>3</sub>需要多满足一个方程，也就是说，A<sub>3</sub>是如下方程组的最小正整数解
- A<sub>3</sub> mod 2 = 1 
- A<sub>3</sub> mod 3 = 2
- A<sub>3</sub> mod 5 = 3

因此A<sub>3</sub> = 23。同样地我们能够得到A<sub>4</sub> = 53以及A<sub>5</sub> = 1523。

记S(n)为所有小于等于n且至少整除序列A中一个元素的素数之和。
例如，S(50) = 69 = 5 + 23 + 41，因为5整除A<sub>2</sub>，23整除A<sub>3</sub>，以及41整除A<sub>10</sub> = 5765999453。其它小于等于50的素数都不能整除A中的任意一个元素。

求S(300000)。

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
参考常量: MAX_P = 300000
