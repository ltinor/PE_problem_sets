# 不和谐的数（PE 515）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=515](https://projecteuler.net/problem=515)。

记d(p,n,0)是n在模素数p同余下的乘法逆元，即n × d(p,n,0) = 1 mod p。

记d(p,n,k) = $\Sigma^n_{i=1}$d(p,i,k?1)，其中k ≥ 1。

记D(a,b,k) = $\Sigma$(d(p,p-1,k) mod p)，对于所有的素数a ≤ p < a + b。

已知：
- D(101,1,10) = 45
- D(10<sup>3</sup>,10<sup>2</sup>,10<sup>2</sup>) = 8334
- D(10<sup>6</sup>,10<sup>3</sup>,10<sup>3</sup>) = 38162302

求D(10<sup>9</sup>,10<sup>5</sup>,10<sup>5</sup>)。

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
