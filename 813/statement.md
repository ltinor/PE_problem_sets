# Problem 813（PE 813）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=813](https://projecteuler.net/problem=813)。

## **XOR-Powers**

We use $x\oplus y$ to be the bitwise XOR of $x$ and $y$.

Define the <i>XOR-product</i> of $x$ and $y$, denoted by $x \otimes y$, similar to a long multiplication in base $2$, except that the intermediate results are XORed instead of the usual integer addition.

For example, $11 \otimes 11 = 69$, or in base $2$, $1011_2 \otimes 1011_2 = 1000101_2$:
$$
\begin{aligned}
\phantom{\otimes 1111} 1011_2 \\\\
\otimes \phantom{1111} 1011_2 \\\\
\hline
\phantom{\otimes 1111} 1011_2 \\\\
\phantom{\otimes 111} 1011_2 \phantom{9} \\\\
\oplus \phantom{1} 1011_2  \phantom{999} \\\\
\hline
\phantom{\otimes 11} 1000101_2 \\\\
\end{aligned}
$$
Further we define $P(n) = 11^{\otimes n} = \overbrace{11\otimes 11\otimes \ldots \otimes 11}^n$. For example $P(2)=69$.

Find $P(8^{12}\cdot 12^8)$. Give your answer modulo $10^9+7$.

## **异或幂**

记$x\oplus y$为$x$和$y$按位异或的结果。

我们定义一种新运算，称为$x$和$y$的<i class=zh>异或积</i>并记作$x \otimes y$。这种运算类似于对$x$和$y$的二进制表示做长乘法，但是将其中的相加替换为异或。

例如，$11 \otimes 11 = 69$，或用二进制表示写作$1011_2 \otimes 1011_2 = 1000101_2$：
$$
\begin{aligned}
\phantom{\otimes 1111} 1011_2 \\\\
\otimes \phantom{1111} 1011_2 \\\\
\hline
\phantom{\otimes 1111} 1011_2 \\\\
\phantom{\otimes 111} 1011_2 \phantom{9} \\\\
\oplus \phantom{1} 1011_2  \phantom{999} \\\\
\hline
\phantom{\otimes 11} 1000101_2 \\\\
\end{aligned}
$$
进一步定义$P(n) = 11^{\otimes n} = \overbrace{11\otimes 11\otimes \ldots \otimes 11}^n$，例如$P(2)=69$。

求$P(8^{12}\cdot 12^8)$，并将你的答案对$10^9+7$取余。

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
参考常量: PE_ANSWER = 42867443257356715LL
