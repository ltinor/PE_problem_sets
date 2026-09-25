# Problem 752（PE 752）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=752](https://projecteuler.net/problem=752)。

## **Powers of $1+\sqrt{7}$**

When $(1+\sqrt 7)$ is raised to an integral power, $n$, we always get a number of the form $(a+b\sqrt 7)$.
We write $(1+\sqrt 7)^n = \alpha(n) + \beta(n)\sqrt 7$.

For a given number $x$ we define $g(x)$ to be the smallest positive integer $n$ such that:
$$\alpha(n) \equiv 1 \pmod x\quad \text{and}\quad \beta(n) \equiv 0 \pmod x$$
and $g(x) = 0$ if there is no such value of $n$. For example, $g(3) = 0$, $g(5) = 12$.

Further define
$$G(N) = \displaystyle \sum_{x=2}^{N} g(x)$$
You are given $G(10^2) = 28891$ and $G(10^3)  = 13131583$.

Find $G(10^6)$.

## **$1+\sqrt{7}$的幂**

对于任意正整数$n$，$(1+\sqrt 7)$的$n$次幂总能写成$(a+b\sqrt 7)$的形式。
我们记$(1+\sqrt 7)^n = \alpha(n) + \beta(n)\sqrt 7$。

给定正整数$x$，我们记$g(x)$为满足下列条件的最小正整数$n$：
$$\alpha(n) \equiv 1 \pmod x\quad \text{and}\quad \beta(n) \equiv 0 \pmod x$$
若不存在这样的$n$，则$g(x) = 0$。例如，$g(3) = 0$，$g(5) = 12$。

进一步记
$$G(N) = \displaystyle \sum_{x=2}^{N} g(x)$$
已知$G(10^2) = 28891$，$G(10^3)  = 13131583$。

求$G(10^6)$。

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
参考常量: PE_ANSWER = 56158650LL
