# Problem 719（PE 719）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=719](https://projecteuler.net/problem=719)。

## **Number Splitting**

We define an $S$-number to be a natural number, $n$, that is a perfect square and its square root can be obtained by splitting the decimal representation of $n$ into $2$ or more numbers then adding the numbers.

For example, $81$ is an $S$-number because $\sqrt{81} = 8+1$.
$6724$ is an $S$-number: $\sqrt{6724} = 6+72+4$. 
$8281$ is an $S$-number: $\sqrt{8281} = 8+2+81 = 82+8+1$.
$9801$ is an $S$-number: $\sqrt{9801}=98+0+1$.

Further we define $T(N)$ to be the sum of all $S$-numbers $n\le N$. You are given $T(10^4) = 41333$.

Find $T(10^{12})$

## **数字分割**

若自然数$n$是个完全平方数，且其平方根可以表示为将$n$的十进制表示分成至少$2$部分再相加的和，则称其为$S$-数。

例如，$81$是个$S$-数，因为$\sqrt{81} = 8+1$。
$6724$是个$S$-数：$\sqrt{6724} = 6+72+4$。
$8281$是个$S$-数：$\sqrt{8281} = 8+2+81 = 82+8+1$。
$9801$是个$S$-数：$\sqrt{9801}=98+0+1$。

再记$T(N)$为所有满足$n\le N$的$S$-数之和。已知$T(10^4) = 41333$。

求$T(10^{12})$。

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
参考常量: PE_ANSWER = 128088830547982LL
