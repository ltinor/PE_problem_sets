# Problem 631（PE 631）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=631](https://projecteuler.net/problem=631)。

## **Constrained Permutations**

Let $(p_1p_2\ldots p_k)$ denote the permutation of the set $\{1,\ldots,k\}$ that maps $p_i\mapsto i$. Define the length of the permutation to be $k$; note that the empty permutation $()$ has length zero.

Define an <i>occurrence</i> of a permutation $p=(p_1p_2\ldots p_k)$  in a permutation $P=(P_1P_2\ldots P_n)$ to be a sequence $1\le t_1<t_2<\cdots <t_k\le n$ such that $p_i<p_j$ if and only if $P_{t_i}<P_{t_j}$ for all $i,j\in\{1,\ldots,k\}$.

For example, $(1243)$ occurs twice in the permutation $(314625)$: once as the 1st, 3rd, 4th and 6th elements $(3\ 46\ 5)$, and once as the 2nd, 3rd, 4th and 6th elements $(\ 146\ 5)$.

Let $f(n,m)$ be the number of permutations $P$ of length at most $n$ such that there is no occurrence of the permutation $(1243)$ in $P$ and there are at most $m$ occurrences of the permutation $(21)$ in $P$.

For example, $f(2,0)=3$, with the permutations $()$, $(1)$, $(1,2)$ but not $(2,1)$.

You are also given that $f(4,5)=32$ and $f(10,25)=294\ 400$.

Find $f(10^{18},40)$ modulo $1\ 000\ 000\ 007$.

## **带约束的排列**

用$(p_1p_2\ldots p_k)$表示将集合 $\{1,\ldots,k\}$ 按照$p_i\mapsto i$映射的排列。记这样的排列的长度为$k$；注意空排列$()$的长度视为0。

考虑排列$P=(P_1P_2\ldots P_n)$和较短的排列$p=(p_1p_2\ldots p_k)$，如果存在序列$1\le t_1<t_2<\cdots <t_k\le n$ ，使得对任意$i,j\in\{1,\ldots,k\}$，$p_i<p_j$ 当且仅当$P_{t_i}<P_{t_j}$，则称$p$在$P$中<i class=zh>出现</i>了一次。

例如，排列$(1243)$在排列$(314625)$中出现了两次：第一次由第1、3、4、6个元素组成，即 $(3\ 46\ 5)$；第二次由第2、3、4、6个元素组成，即$(\ 146\ 5)$。

考虑所有长度不超过$n$的排列$P$，其中，没有排列$(1243)$出现，且排列$(21)$出现至多$m$次的排列总数记为$f(n,m)$。

例如，$f(2,0)=3$，这三种排列分别是$()$，$(1)$和$(1,2)$，而$(2,1)$不满足要求。

已知$f(4,5)=32$，以及$f(10,25)=294\ 400$。

求$f(10^{18},40)$并对$1\ 000\ 000\ 007$取余。

---

## 输入格式

第一行一个 token：

- 若为 `PE`，输出原题（$f(10^{18}, 40)$）官方答案；
- 否则为两个整数 $n$ 和 $m$（$0 \le n \le 10$，$0 \le m \le 40$）。

## 输出格式

一行一个整数：$f(n, m)$ 对 $1\,000\,000\,007$ 取余。

## 样例

### 输入

```
4 5
```

### 输出

```
32
```

（与原题陈述一致：$f(2,0)=3$，$f(4,5)=32$，$f(10,25)=294\,400$。）

---

## 数据范围

- 若输入为 `PE`，输出 $823094358$；
- 否则 $0 \le n \le 10$，$0 \le m \le 40$。

## 提示

长度不超过 $10$ 的排列可暴力枚举：按长度 $L=0..n$ 依次枚举 $L!$ 个排列，统计反演数（$(21)$ 出现次数）并做 $(1243)$ 模式检查。原题参数下需借助反演表/插入 DP 等组合方法。
