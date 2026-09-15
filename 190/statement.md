# 最大化加权乘积

## 题目描述

对于正整数 $m$，设 $x_1, x_2, \ldots, x_m$ 为 $m$ 个正实数，满足 $\sum_{i=1}^m x_i = m$。定义加权乘积：

$$P_m = \prod_{i=1}^m x_i^i = x_1^1 \times x_2^2 \times \cdots \times x_m^m$$

记 $P_m$ 的最大值为 $[P_m]$。

给定 $M$，求 $\sum_{m=2}^{M} \lfloor P_m \rfloor$。

---

## 输入格式

一行，一个正整数 $M$。

---

## 输出格式

一行，一个整数，表示 $\sum_{m=2}^{M} \lfloor P_m \rfloor$。

---

## 样例

### 输入
```
15
```

### 输出
```
371048281
```

---

## 数据范围

- $2 \le M \le 15$
