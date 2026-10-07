# Problem 929（PE 929）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=929](https://projecteuler.net/problem=929)。

## **Odd-Run Compositions**

A <b>composition</b> of $n$ is a sequence of positive integers which sum to $n$. Such a sequence can be split into <i>runs</i>, where a run is a maximal contiguous subsequence of equal terms.

For example, $2,2,1,1,1,3,2,2$ is a composition of $14$ consisting of four runs:

<div style="text-align:center">
$2, 2\quad 1, 1, 1\quad 3 \quad 2, 2$
</div>

Let $F(n)$ be the number of compositions of $n$ where every run has odd length.

For example, $F(5)=10$:
$$
\begin{aligned}
& 5 && 4,1 && 3,2 && 2,3 && 2,1,2\\\\
& 2,1,1,1 && 1,4 && 1,3,1 && 1,1,1,2 && 1,1,1,1,1
\end{aligned}
$$
Find $F(10^5)$. Give your answer modulo $1111124111$.

## **奇数长度分段组成**

$n$的一个<b>组成</b>是一个和为$n$的正整数序列；这一序列可以进一步分成若干<i class=zh>段</i>，每一段是由相等的数构成的最长连续子序列。

例如，$2,2,1,1,1,3,2,2$是$14$的一个组成，可以分成四段：

<div style="text-align:center">
$2, 2\quad 1, 1, 1\quad 3 \quad 2, 2$
</div>

令$F(n)$为$n$的所有组成中，满足每一段长度都为奇数的组成的数目。

例如，$F(5)=10$：
$$
\begin{aligned}
& 5 && 4,1 && 3,2 && 2,3 && 2,1,2\\\\
& 2,1,1,1 && 1,4 && 1,3,1 && 1,1,1,2 && 1,1,1,1,1
\end{aligned}
$$
求$F(10^5)$，并对$1111124111$取余作为你的答案。

---

## 输入格式

第一行一个 token：

- 若为 `PE`，输出原题（$n = 100000$）官方答案；
- 否则为整数 $n$（$1 \le n \le 100000$）。

## 输出格式

一行一个整数：$F(n)$ 对 $1\,111\,124\,111$ 取余。

## 样例

### 输入

```
5
```

### 输出

```
10
```

（$n \le 12$ 时 $F$ 依次为 $1, 1, 4, 4, 10, 19, 33, 59, 113, 210, 379, 704$，已与逐项枚举核对。）

---

## 数据范围

- 若输入为 `PE`，输出 $57322484$（即 $F(100000)$）；
- 否则 $1 \le n \le 100000$。

## 提示

Smirnov 变换给出递推 $F(n) = \sum_{m=1}^{n} W(m)\,F(n-m)$，其中 $W(m) = \sum_{d \mid m} s(d)\,\mathrm{Fib}(d)$，$s(d) = +1$（$d$ 奇）$/-1$（$d$ 偶），$\mathrm{Fib}$ 为斐波那契数列。
