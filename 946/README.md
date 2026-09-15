# Problem 946 (简单版 / 缩数据版)

来源：改编自 Project Euler Problem 946（Continued Fraction Fraction）

## 原题意

$\alpha$ 是一个实数，其连分数表示为

$$\alpha = [2;1,1,2,1,1,1,2,1,1,1,1,1,2,\ldots]$$

其中每两个 $2$ 之间的 $1$ 的数目是连续的质数（$2,3,5,7,11,\ldots$）。

$\beta$ 是另一个实数，定义为 $\beta = \dfrac{2\alpha+3}{3\alpha+2}$。

$\beta$ 的连分数前十个系数是 $[0;1,5,6,16,9,1,10,16,11]$，其和为 $75$。

原题要求：求 $\beta$ 的连分数前 $10^8$ 个系数之和。

## 题目（缩数据版）

给定整数 $N$，求 $\beta$ 的连分数表示的前 $N$ 个系数之和。

## 数据范围

$1 \le N \le 10^6$（原题 $N = 10^8$，这里缩小为 $\le 10^6$）。

## 算法

Gosper 连分数算法（continued-fraction arithmetic）：

- 莫比乌斯变换 $z \mapsto \dfrac{a z + b}{c z + d}$ 作用在一个连分数上，可以逐项"流式"计算。
- 状态矩阵 $Z=\begin{bmatrix}a&b\\c&d\end{bmatrix}$ 表示当前值 $\dfrac{a x + b}{c x + d}$，其中 $x$ 是 $\alpha$ 连分数的"尾巴"。
- 初始 $Z=\begin{bmatrix}2&3\\3&2\end{bmatrix}$（即 $\beta=\dfrac{2\alpha+3}{3\alpha+2}$）。
- 每步：若 $\lfloor a/c\rfloor=\lfloor b/d\rfloor$，输出该项并令 $Z\leftarrow\begin{bmatrix}c&d\\a-qc&b-qd\end{bmatrix}$；否则读入 $\alpha$ 的下一项 $x$，令 $Z\leftarrow\begin{bmatrix}ax+b&a\\cx+d&c\end{bmatrix}$。

由于 $\alpha$ 的连分数系数只含 $1$ 和 $2$（有界），$\beta$ 的连分数系数也有界，状态矩阵中的整数始终很小（$\le$ 数百），因此时间复杂度为 $O(N)$，无需大整数。

验证点（题目给定）：前 $10$ 个系数 $[0;1,5,6,16,9,1,10,16,11]$，和 $75$。另有前 $20$ 项和 $95$、前 $50$ 项和 $202$、前 $100$ 项和 $541$。
