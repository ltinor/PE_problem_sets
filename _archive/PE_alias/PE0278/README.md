# 半素数线性组合 (Linear Combinations of Semiprimes)

来源：改编自 Project Euler Problem 278

## 原题意

对于所有素数 $p<q<r<5000$，求 $\sum f(pq, pr, qr)$。PE 答案：1228215747273908452。

## 题目

输入 $B$，对 $p<q<r<B$ 求和。

## 数据范围

$5 \le B \le 5000$。

## 算法

### 方向一：闭公式（核心）

对于三个形如 $pq, pr, qr$ 的数（$p<q<r$ 为素数），Frobenius 数有闭公式：

$$f(pq, pr, qr) = 2pqr - pq - pr - qr$$

代入求和：

$$\sum_{p<q<r} f = \sum_{p<q} \Big[(2pq - p - q)\sum_{r>q} r - (cnt_r) \cdot pq\Big]$$

预处理素数后缀和，$O(\pi(B)^2)$ 计算。

### 方向二：DP 暴力验证（仅小数据）

对于小参数集，用 DP 标记所有可表示的数，找到最大不可表示数。

### 方向三：一般 Frobenius 数（研究背景）

对于两个互质数 $a,b$，$f(a,b) = ab - a - b$。三个及以上无通解，但该半素结构恰好退化出闭公式。

### 时间复杂度

$O(\pi(B)^2)$，其中 $\pi(5000) \approx 669$，秒出。
