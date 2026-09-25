# Problem 785（PE 785）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=785](https://projecteuler.net/problem=785)。

## **Symmetric Diophantine equation**

Consider the following Diophantine equation:
$$15  (x^2 + y^2 + z^2) = 34  (xy + yz + zx)$$
where $x$, $y$ and $z$ are positive integers.

Let $S(N)$ be the sum of all solutions, $(x,y,z)$, of this equation such that, $1 \le x \le y \le z \le N$ and $\gcd(x, y, z) = 1$.

For $N = 10^2$, there are three such solutions - $(1, 7, 16), (8, 9, 39), (11, 21, 72)$. So $S(10^2) = 184$.

Find $S(10^9)$.

## **对称丢番图方程**

考虑如下丢番图方程：
$$15  (x^2 + y^2 + z^2) = 34  (xy + yz + zx)$$
其中$x$、$y$、$z$均为正整数。

对于上述方程满足$1 \le x \le y \le z \le N$和$\gcd(x, y, z) = 1$的解$(x,y,z)$，记$S(N)$为所有这些解之和。

对于$N = 10^2$，共有三组这样的解：$(1, 7, 16), (8, 9, 39), (11, 21, 72)$，因此$S(10^2) = 184$。

求$S(10^9)$。

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
参考常量: PE_ANSWER = 295269766LL
