# PE829 — Integral Fusion（积分融合）

来源：改编自 Project Euler Problem 829

## 原题意

研究形如 $\int_0^1 x^a (1-x)^b (\ln x)^c \, dx$ 的定积分，当结果经过适当规范化后为整数时，称该积分为"融合"的（Integral Fusion）。

这类积分与 Beta 函数、Gamma 函数、调和数以及多重 zeta 值密切相关。当 $c=0$ 时退化为 Beta 积分 $B(a+1, b+1)$；$c>0$ 时涉及 digamma、trigamma 等多伽马函数。

PE 答案：883344930。

## 算法

1. **Beta 积分**：$\int_0^1 x^a (1-x)^b dx = \frac{a! \, b!}{(a+b+1)!}$。
2. **对数导数**：对参数求导可得含 $\ln x$ 的积分：$\frac{\partial^c}{\partial a^c} B(a+1, b+1) = \int_0^1 x^a (1-x)^b (\ln x)^c dx$。
3. **调和数表示**：结果可用调和数 $H_n$ 和广义调和数表示。
4. **整数条件**：乘以 $(a+b+1)!$ 或类似规范化因子后检查是否为整数。

## 改编方向

1. 推广到多重积分（Dirichlet 积分）
2. 引入其他权重函数（如 $e^{-x}$、三角函数）
3. 研究积分结果的有理逼近
4. 考虑反常积分和围道积分
5. 在复平面上考察解析延拓
