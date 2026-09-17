# Problem 921（PE 921）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=921](https://projecteuler.net/problem=921)。

## **Golden Recurrence**

Consider the following recurrence relation:
$$
\begin{aligned}
a_0 &= \frac{\sqrt 5 + 1}{2}\\\\
a_{n+1} &= \dfrac{a_n(a_n^4 + 10a_n^2 + 5)}{5a_n^4 + 10a_n^2 + 1}
\end{aligned}
$$

Note that $a_0$ is the <b>golden ratio</b>.

$a_n$ can always be written in the form $\dfrac{p_n\sqrt{5}+1}{q_n}$, where $p_n$ and $q_n$ are positive integers.

Let $s(n)=p_n^5+q_n^5$. So, $s(0)=1^5+2^5=33$.

The <b>Fibonacci sequence</b> is defined as: $F_1=1$, $F_2=1$, $F_n=F_{n-1}+F_{n-2}$ for $n \gt 2$.

Define $\displaystyle S(m)=\sum_{i=2}^{m}s(F_i)$.

Find $S(1618034)$. Submit your answer modulo $398874989$.

## **黄金递推**

考虑以下递推关系：
$$
\begin{aligned}
a_0 &= \frac{\sqrt 5 + 1}{2}\\\\
a_{n+1} &= \dfrac{a_n(a_n^4 + 10a_n^2 + 5)}{5a_n^4 + 10a_n^2 + 1}
\end{aligned}
$$

注意到，$a_0$恰好是<b>黄金比例</b>。

$a_n$总可以写成$\dfrac{p_n\sqrt{5}+1}{q_n}$的形式，其中$p_n$和$q_n$是正整数。

令$s(n)=p_n^5+q_n^5$。因此，$s(0)=1^5+2^5=33$。

<b>斐波那契数列</b>的定义是：$F_1=1$，$F_2=1$，对于$n > 2$有$F_n=F_{n-1}+F_{n-2}$。

定义$\displaystyle S(m)=\sum_{i=2}^{m}s(F_i)$。

求$S(1618034)$，并对$398874989$取余作为你的答案。

---

## 输入格式

（待人工补充：请对照 code/std.cpp 的读取约定描述。）

## 输出格式

（待人工补充。）

## 样例

（无 data 数据，待人工补充。）

---

## 数据范围

（待人工补充；原题参数范围见上方原题描述。）

