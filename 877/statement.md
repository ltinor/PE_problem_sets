# Problem 877（PE 877）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=877](https://projecteuler.net/problem=877)。

## **XOR-Equation A**

We use $x\oplus y$ for the bitwise XOR of $x$ and $y$.<br />
Define the <i>XOR-product</i> of $x$ and $y$, denoted by $x \otimes y$, similar to a long multiplication in base $2$, except that the intermediate results are XORed instead of the usual integer addition.

For example, $7 \otimes 3 = 9$, or in base $2$, $111_2 \otimes 11_2 = 1001_2$:
$$
\begin{aligned}
\phantom{\otimes 111} 111_2 \\\\
\otimes \phantom{1111} 11_2 \\\\
\hline
\phantom{\otimes 111} 111_2 \\\\
\oplus \phantom{11} 111_2  \phantom{9} \\\\
\hline
\phantom{\otimes 11} 1001_2 \\\\
\end{aligned}
$$
We consider the equation:
$$(a \otimes a) \oplus (2 \otimes a \otimes b) \oplus (b \otimes b) = 5$$
For example, $(a, b) = (3, 6)$ is a solution.

Let $X(N)$ be the XOR of the $b$ values for all solutions to this equation satisfying $0 \le a \le b \le N$.<br />
You are given $X(10)=5$.

Find $X(10^{18})$.

## **异或方程（一）**

用$x\oplus y$表示$x$和$y$按位异或的结果。<br />
考虑$x$和$y$的$2$进制长乘法，但将中间结果的相加替换为按位异或，定义其结果为$x$和$y$的<i class=zh>异或积</i>，并记作$x \otimes y$。 

例如，$7 \otimes 3 = 9$，或在$2$进制下，$111_2 \otimes 11_2 = 1001_2$：
$$
\begin{aligned}
\phantom{\otimes 111} 111_2 \\\\
\otimes \phantom{1111} 11_2 \\\\
\hline
\phantom{\otimes 111} 111_2 \\\\
\oplus \phantom{11} 111_2  \phantom{9} \\\\
\hline
\phantom{\otimes 11} 1001_2 \\\\
\end{aligned}
$$
考虑方程：
$$(a \otimes a) \oplus (2 \otimes a \otimes b) \oplus (b \otimes b) = 5$$
例如，$(a, b) = (3, 6)$是上式的一个解。

考虑所有满足$0 \le a \le b \le N$的上式的解，并记$X(N)$为所有这些解中$b$的取值按位异或的结果。<br />
已知$X(10)=5$。

求$X(10^{18})$。

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

