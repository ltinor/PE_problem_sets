# B-三除数 (B-Trivisible Numbers)

来源：改编自 Project Euler Problem 967

## 原题意

如果正整数 $n$ 所有不大于 $B$ 的不同质因数之和能被 $3$ 整除，则称 $n$ 为 $B$-三除数。

设 $F(N,B)$ 为不大于 $N$ 的 $B$-三除数的数目。已知 $F(10,4)=5$、$F(10,10)=3$、$F(100,10)=41$。

原题求 $F(10^{18}, 120)$。

## 题目

给定 $N$ 和 $B$，求不大于 $N$ 的 $B$-三除数的数目 $F(N,B)$。

## 数据范围

$1 \le N \le 10^{18}$，$1 \le B \le 40$

## 算法

容斥（莫比乌斯反演）+ 子集枚举

记 $P$ 为所有不超过 $B$ 的质数集合。对每个 $n$，记 $D(n)=\{p\in P : p\mid n\}$。令

$$g(T)=\left\lfloor \frac{N}{\prod_{p\in T}p} \right\rfloor,\qquad h(T)=\sum_{\substack{S\subseteq T\\ \sum_{p\in S}p\,\equiv\,0\pmod 3}}(-1)^{|S|}$$

则由莫比乌斯反演有

$$F(N,B)=\sum_{T\subseteq P}(-1)^{|T|}\,g(T)\,h(T).$$

$h(T)$ 即生成多项式 $\prod_{p\in T}(1-x^{p\bmod 3})$ 在模 $3$ 意义下的零次项系数，可用长度 $3$ 的系数数组递推。

时间复杂度：$O(2^{\pi(B)})$，其中 $\pi(B)$ 为不超过 $B$ 的质数个数（$B\le40$ 时最多 $12$ 个）。

空间复杂度：$O(1)$
