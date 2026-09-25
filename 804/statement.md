# Problem 804（PE 804）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=804](https://projecteuler.net/problem=804)。

## **Counting Binary Quadratic Representations**

Let $g(n)$ denote the number of ways a positive integer $n$ can be represented in the form: 
$$x^2+xy+41y^2$$
where $x$ and $y$ are integers. For example, $g(53)=4$ due to $(x,y) \in \{(-4,1),(-3,-1),(3,1),(4,-1)\}$.

Define $\displaystyle T(N)=\sum_{n=1}^{N}g(n)$. You are given $T(10^3)=474$ and $T(10^6)=492128$.

Find $T(10^{16})$.

## **二元二次型表示计数**

记$g(n)$为将正整数$n$表示成如下二元二次型的方式数目：
$$x^2+xy+41y^2$$
其中$x$和$y$均为整数。例如，$g(53)=4$，对应的方式为$(x,y) \in \{(-4,1),(-3,-1),(3,1),(4,-1)\}$。

定义$\displaystyle T(N)=\sum_{n=1}^{N}g(n)$。已知$T(10^3)=474$，$T(10^6)=492128$。

求$T(10^{16})$。

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
参考常量: PE_ANSWER = 721014409585053LL
