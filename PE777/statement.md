# 约数和的LCM

## 题目描述

记 $\sigma(n)$ 为 $n$ 的所有正约数之和。考虑序列 $\sigma(1), \sigma(2), \dots$ 的最小公倍数的渐近行为。

问题要求：计算某个与 $\operatorname{lcm}\{\sigma(1), \dots, \sigma(N)\}$ 相关的极限值或概率。

例如：
- $\sigma(1) = 1$
- $\sigma(2) = 1 + 2 = 3$
- $\sigma(3) = 1 + 3 = 4$
- $\sigma(4) = 1 + 2 + 4 = 7$
- $\operatorname{lcm}(1, 3, 4, 7) = 84$

## 输入格式

一行字符串：`PE`、`verify` 或 `compute`。

## 输出格式

- `PE`：输出 PE 原题答案 0.000238077（9 位小数）。
- `verify`：输出小 $n$ 的 $\sigma(n)$ 值、前 10 项的 LCM、质因子分布。
- `compute`：扩展到 $n \le 1000$ 的 $\sigma(n)$ 统计，讨论渐近行为。

## 样例

### 输入
```
PE
```

### 输出
```
0.000238077
```

### 验证
```
verify
```

输出内容包括：
- $\sigma(1)$ 到 $\sigma(30)$ 的值
- $N=1$ 到 $10$ 的 $\operatorname{lcm}(\sigma(1..N))$ 及其增长因子
- LCM 中出现的质数幂次

## 数据范围

- 验证范围：$n \le 100$（LCM 快速增长，受限于精度）
- 统计范围：$n \le 1000$（计算 $\sigma(n)$ 的分布）
- 完整问题：极限值 $\approx 2.38 \times 10^{-4}$
