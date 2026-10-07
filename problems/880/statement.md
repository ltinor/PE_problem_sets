# Problem 880（PE 880）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=880](https://projecteuler.net/problem=880)。

## **Nested Radicals**

$(x,y)$ is called a <i>nested radical pair</i> if $x$ and $y$ are non-zero integers such that $x/y$ is not a cube of a rational number, and there exist integers $a$, $b$ and $c$ such that:
$$\sqrt{\sqrt[3]{x}+\sqrt[3]{y}}=\sqrt[3]{a}+\sqrt[3]{b}+\sqrt[3]{c}$$
For example, both $(-4,125)$ and $(5,5324)$ are nested radical pairs:
$$
\begin{aligned}
\begin{split}
\sqrt{\sqrt[3]{-4}+\sqrt[3]{125}}	& = \sqrt[3]{-1}+\sqrt[3]{2}+\sqrt[3]{4}\\\\
\sqrt{\sqrt[3]{5}+\sqrt[3]{5324}}	& = \sqrt[3]{-2}+\sqrt[3]{20}+\sqrt[3]{25}\\\\
\end{split}
\end{aligned}
$$
Let $H(N)$ be the sum of $|x|+|y|$ for all the nested radical pairs $(x, y)$ where $|x| \leq |y|\leq N$.<br /> 
For example, $H(10^3)=2535$.

Find $H(10^{15})$. Give your answer modulo $1031^3+2$.

## **嵌套根式**

若非零整数$x$和$y$满足，$x/y$不是有理数的立方，且存在满足以下条件的整数$a$、$b$、$c$，则称$(x,y)$为<i class=zh>嵌套根式对</i>：
$$\sqrt{\sqrt[3]{x}+\sqrt[3]{y}}=\sqrt[3]{a}+\sqrt[3]{b}+\sqrt[3]{c}$$
例如，$(-4,125)$和$(5,5324)$都是嵌套根式对：
$$
\begin{aligned}
\begin{split}
\sqrt{\sqrt[3]{-4}+\sqrt[3]{125}}	& = \sqrt[3]{-1}+\sqrt[3]{2}+\sqrt[3]{4}\\\\
\sqrt{\sqrt[3]{5}+\sqrt[3]{5324}}	& = \sqrt[3]{-2}+\sqrt[3]{20}+\sqrt[3]{25}\\\\
\end{split}
\end{aligned}
$$
考虑所有满足$|x| \leq |y|\leq N$的嵌套根式对$(x,y)$，记$H(N)$为所有$|x|+|y|$的和。<br /> 
例如，$H(10^3)=2535$。

求$H(10^{15})$，并对$1031^3+2$取余作为你的答案。

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
