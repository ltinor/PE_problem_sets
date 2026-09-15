# 无同树

来源：改编自 Project Euler Problem 936（Peerless Trees）

## 原题意

A *peerless tree* is a tree with no edge between two vertices of the same degree.
Let $P(n)$ be the number of peerless trees on $n$ unlabelled vertices.
Given $P(7)=6$ and $S(10)=74$ where $S(N)=\sum_{n=3}^{N}P(n)$, find $S(50)$.

## 题目

给定整数 $N$，求 $S(N) = \sum_{n=3}^{N} P(n)$，其中 $P(n)$ 为 $n$ 个无标记顶点上的无同树数量。

## 数据范围

$3 \le N \le 15$（原题为 $N=50$，此处缩小数据，使得枚举可行）。

## 算法

无标记树的计数采用「中心分解」：

- 单中心树：以根为唯一中心的根树，要求根的每个子树大小 $\le (n-1)/2$；
- 双中心树（$n$ 为偶数）：两棵 $n/2$ 个顶点的根树的根用一条边相连，等价于 $\binom{R(n/2)+1}{2}$ 种无序对。

先用括号表示法生成所有非同构根树（子树按「大小降序、串升序」排序得到规范形式，保证每类恰好一次），再按上述分解还原出所有自由树，最后逐一检查「无同」条件（相邻顶点度数不同）并累加。
