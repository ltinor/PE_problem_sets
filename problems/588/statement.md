# Problem 588（PE 588）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=588](https://projecteuler.net/problem=588)。

## **Quintinomial coefficients**

The coefficients in the expansion of $(x+1)^k$ are called <b>binomial coefficients</b>.
Analoguously the coefficients in the expansion of $(x^4+x^3+x^2+x+1)^k$ are called <b>quintinomial coefficients</b>.
(quintus= Latin for fifth).

Consider the expansion of $(x^4+x^3+x^2+x+1)^3$:
$x^{12}+3x^{11}+6x^{10}+10x^9+15x^8+18x^7+19x^6+18x^5+15x^4+10x^3+6x^2+3x+1$
As we can see 7 out of the 13 quintinomial coefficients for $k=3$ are odd.

Let $Q(k)$ be the number of odd coefficients in the expansion of $(x^4+x^3+x^2+x+1)^k$.
So $Q(3)=7$.

You are given $Q(10)=17$ and $Q(100)=35$.

Find $\sum_{k=1}^{18}Q(10^k)$.

## **五项式系数**

$(x+1)^k$展开的各项系数被称为<b>二项式系数</b>。
类似地，$(x^4+x^3+x^2+x+1)^k$展开的各项系数被称为<b>五项式系数</b>。
（quintus是表示“第5”的拉丁语词汇）。

考虑$(x^4+x^3+x^2+x+1)^3$的展开式：
$x^{12}+3x^{11}+6x^{10}+10x^9+15x^8+18x^7+19x^6+18x^5+15x^4+10x^3+6x^2+3x+1$
我们可以看出，当$k=3$时，13个五项式系数中有7个是奇数。

令$Q(k)$表示$(x^4+x^3+x^2+x+1)^k$的展开式的系数中奇数的数目。
因此$Q(3)=7$。

已知$Q(10)=17$以及$Q(100)=35$。

求$\sum_{k=1}^{18}Q(10^k)$。

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
