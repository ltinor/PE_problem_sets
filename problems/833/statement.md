# Problem 833（PE 833）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=833](https://projecteuler.net/problem=833)。

## **Square Triangle Products**

Triangle numbers $T_k$ are integers of the form $k(k+1)/2$.<br />
A few triangle numbers happen to be perfect squares like $T_1=1$ and $T_8=36$, but more can be found when considering the product of two triangle numbers. For example, $T_2 \cdot T_{24}=3 \cdot 300=30^2$.

Let $S(n)$ be the sum of $c$ for all integers triples $(a, b, c)$ with $0\lt c \le n$, $c^2=T_a \cdot T_b$ and $0<a<b$. For example, $S(100)= \sqrt{T_1 T_8}+\sqrt{T_2 T_{24}}+\sqrt{T_1 T_{49}}+\sqrt{T_3 T_{48}}=6+30+35+84=155$.

You are given $S(10^5)=1479802$ and $S(10^9)=241614948794$.

Find $S(10^{35})$. Give your answer modulo $136101521$.

## **恰为平方数的三角形数乘积**

三角形数$T_k$是指能表达为$k(k+1)/2$的整数。<br />
有些三角形数恰好就是完全平方数，比如$T_1=1$和$T_8=36$。如果考虑两个三角形数的乘积，那么可以找到更多的完全平方数。例如，$T_2 \cdot T_{24}=3 \cdot 300=30^2$。

考虑所有同时满足$0 \lt c \le n$、$c^2=T_a \cdot T_b$和$0<a<b$的整数三元组$(a,b,c)$，并记$S(n)$为所有此类三元组中整数$c$之和。例如，$S(100)= \sqrt{T_1 T_8}+\sqrt{T_2 T_{24}}+\sqrt{T_1 T_{49}}+\sqrt{T_3 T_{48}}=6+30+35+84=155$。

已知$S(10^5)=1479802$，$S(10^9)=241614948794$。

求$S(10^{35})$，并将你的答案对$136101521$取余。

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
参考常量: PE_ANSWER = 928306910LL
