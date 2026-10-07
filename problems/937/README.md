# 等积划分

来源：改编自 Project Euler Problem 937（Equiproduct Partition）

## 原题意

令 $\theta=\sqrt{-2}$。定义 $T$ 为形如 $a+b\theta$（$a,b$ 为整数，且 $a>0$ 或 $a=0$ 且 $b>0$）的数构成的集合。
对 $S\subseteq T$ 与 $z\in T$，定义 $p(S,z)$ 为「从 $S$ 中选两个**不同**元素，其乘积为 $z$ 或 $-z$」的方案数。

记 $A,B$ 满足 $1\in A$、$A\cap B=\varnothing$、$A\cup B=T$，且对任意 $z\in T$ 有 $p(A,z)=p(B,z)$。
这四个条件唯一确定 $A,B$。令 $F_n=\{1!,2!,\dots,n!\}$，$G(n)$ 为 $F_n\cap A$ 中所有元素之和。

已知 $G(4)=25$，$G(7)=745$，$G(100)\equiv 709772949\pmod{10^9+7}$。原题求 $G(10^8)$（取模 $10^9+7$）。

## 题目（简单版本）

输入一个整数 $n$，输出 $G(n)\bmod(10^9+7)$。

## 数据范围

$1\le n\le 10^6$（原题为 $n=10^8$，此处缩小数据，使得 $O(n)$ 直接递推可行）。

## 算法

环 $\mathbb{Z}[\sqrt{-2}]$ 是唯一分解整环（UFD），单位只有 $\pm 1$。等积划分由「各素因子指数的二进制 1 的个数之和的奇偶性」决定：

- 记 $\chi(x)=(-1)^{\sum_i \mathrm{popcount}(e_i)}$，其中 $x=\prod_i \pi_i^{e_i}$ 是 $\mathbb{Z}[\sqrt{-2}]$ 中的素分解，$\mathrm{popcount}$ 为二进制中 1 的个数；
- 则 $A=\{x:\chi(x)=+1\}$，$B=\{x:\chi(x)=-1\}$。

（对单个素数 $\pi$ 的幂 $\pi^e$，由等积条件可推得 $b_e=\chi(\pi^e)$ 满足 $b_0=1$、$b_{2e}=b_e$、$b_{2e+1}=-b_e$，即 Thue-Morse 序列 $b_e=(-1)^{\mathrm{popcount}(e)}$。）

整数 $n$ 在 $\mathbb{Z}[\sqrt{-2}]$ 中的素分解为：

- $2$ 分歧：$2=-\theta^2$，贡献 $\mathrm{popcount}(v_2(n))$；
- $p\equiv 1,3\pmod 8$ 分裂为两个共轭素元，各贡献 $\mathrm{popcount}(v_p(n))$，合计恒为偶数，不影响奇偶性；
- $p\equiv 5,7\pmod 8$ 惰性，贡献 $\mathrm{popcount}(v_p(n))$。

因此 $n\in A\iff \mathrm{popcount}(v_2(n))+\sum_{p\equiv 5,7\pmod 8}\mathrm{popcount}(v_p(n))$ 为偶数。

对 $n!$ 用勒让德公式 $v_p(n!)=\sum_{j\ge1}\lfloor n/p^j\rfloor$，并按 $n!=(n-1)!\cdot n$ 增量维护各素数指数与奇偶性，同时累加 $n!\bmod(10^9+7)$。总复杂度 $O(n\log\log n)$。

验证：$G(4)=25$，$G(7)=745$，$G(100)\equiv 709772949\pmod{10^9+7}$。
