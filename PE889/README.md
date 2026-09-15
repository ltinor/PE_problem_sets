# PE889 — Rational Blancmange（有理牛奶冻）

来源：改编自 Project Euler Problem 889

## 原题意

牛奶冻函数（Blancmange function，也称 Takagi 曲线）定义为：
$$B(x) = \sum_{n=0}^{\infty} \frac{s(2^n x)}{2^n}$$
其中 $s(x) = \min_{k \in \mathbb{Z}} |x - k|$ 是到最近整数的距离。

在有理数 $x = p/q$ 处求 $B(p/q)$ 的值。由于分母 $q$ 可分解为 $q = 2^a \cdot b$（$b$ 为奇数），序列 $2^n p/q \bmod 1$ 最终会周期化。

## 算法

1. **周期分析**：
   - 对 $n \geq a$，$2^n p/q \bmod 1$ 以 2 模 $b$ 的乘法阶为周期

2. **直接求和**：
   - 前 $a$ 项直接计算
   - 剩余部分利用周期性加速

3. **已知精确值**：
   - $B(1/3) = B(2/3) = 2/3$
   - $B(1/5) = 9/25 = 0.36$
   - $B(p/q)$ 总是有理数

## 改编方向

1. 计算 $B(p/q)$ 对所有约化分数的和
2. 研究 $B(x)$ 在有理点的最大值
3. 推广到其他底数的 Takagi 曲线
4. 与 Stern 二项序列的联系
