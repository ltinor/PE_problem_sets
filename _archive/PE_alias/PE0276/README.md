# 互质三角形 (Primitive Triangles)

来源：改编自 Project Euler Problem 276

## 原题意

统计周长不超过 10,000,000 的互质整数三角形（$\gcd(a,b,c)=1$，$a\le b\le c$，$a+b>c$）的数量。PE 答案：5777137137739992。

## 题目

输入 $N$，输出周长不超过 $N$ 的互质三角形数量。

## 数据范围

$3 \le N \le 10^7$

## 算法

### 方向一：Möbius 反演

先求所有（不要求互质）整数三角形的数量 $F(n)$ = 周长 $\le n$ 的三角形数，再用 Möbius 反演：

$$\text{答案} = \sum_{d=1}^N \mu(d) \cdot F\left(\left\lfloor\frac{N}{d}\right\rfloor\right)$$

其中 $F(n) = \sum_{p=3}^n T(p)$，$T(p)$ 是周长为 $p$ 的整数三角形数。

### 方向二：$T(p)$ 闭公式（Alcuin 序列）

- $p$ 为偶数：$T(p) = \operatorname{round}(p^2/48) = \lfloor(p^2+24)/48\rfloor$
- $p$ 为奇数：$T(p) = \operatorname{round}((p+3)^2/48) = \lfloor((p+3)^2+24)/48\rfloor$

前缀和 $O(N)$ 预处理。

### 方向三：线性筛求 Möbius 函数

使用线性筛在 $O(N)$ 时间内求出 $\mu(1..N)$，然后 $O(N)$ 求和。

### 时间复杂度

$O(N)$，$N=10^7$ 可在 1 秒内完成。
