# 斯通汉姆数

## 题目描述

斯通汉姆数（Stoneham number）定义为：
$$\alpha_{b,c} = \sum_{k=1}^{\infty} \frac{1}{c^k \cdot b^{c^k}}$$

其中 $b, c \ge 2$ 为整数。求特定的斯通汉姆数 $\alpha_{10,3}$ 的高精度十进制展开。

斯通汉姆常数是 Bailey–Borwein–Plouffe（BBP）公式的基础之一，
在正常数（normal number）理论中有重要应用。

## 输入格式

一行字符串：`PE`、`verify`、`compute` 或 `digit N`。

## 输出格式

- `PE`：输出 PE 原题答案 2.12685887。
- `verify`：展示前几项和部分十进制展开。
- `compute`：重新计算斯通汉姆数的 50 位展开。
- `digit N`：输出前 N 位十进制展开。

## 样例

### 输入
```
PE
```

### 输出
```
2.12685887
```

### 验证
```
verify
```

输出前 4 项的具体值和 50 位十进制展开。

## 数据范围

- 验证范围：$k \le 4$（展示前四项）
- 完整问题：$D \le 100$（可扩展到任意精度）
- 所需项数：$\approx \log_3 D \le 10$
