# 麦卡锡91函数（PE 555）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=555](https://projecteuler.net/problem=555)。

麦卡锡91函数的定义如下：

$M\_{91}(n) =  \begin{cases} n - 10 & \text{if } n > 100 \\\\ M\_{91}(M\_{91}(n+11)) & \text{if } 0 \leq n \leq 100 \end{cases}$

通过将上述定义中的常数抽象为变量，我们可以将这个定义一般化：

$M\_{m,k,s}(n) =  \begin{cases} n - s & \text{if } n > m \\\\ M\_{m,k,s}(M\_{m,k,s}(n+k)) & \text{if } 0 \leq n \leq m \end{cases}$

这样一来，我们有$M\_{91} = M\_{100,11,10}$。

令$F\_{m,k,s}$为$M_{m,k,s}$的不动点所构成的集合，也就是说：

$F\_{m,k,s}= \\{ n \in \mathbb{N} \, | \, M\_{m,k,s}(n) = n \\}$

例如，$M\_{91}$只有一个不动点$n = 91$，换言之就是$F\_{100,11,10}= \\{91\\}$。

定义$SF(m,k,s)$为$F\_{m,k,s}$中元素的和，并记$S(p,m) = \displaystyle \sum_{1 \leq s < k \leq p}{SF(m,k,s)}$。

已知$S(10, 10) = 225$以及$S(1000, 1000)=208724467$。

求$S(10^6, 10^6)$。

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
