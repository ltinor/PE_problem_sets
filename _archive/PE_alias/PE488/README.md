# PE488 - 不平衡 Nim

来源：改编自 Project Euler Problem 488

## 原题意

不平衡 Nim 游戏变种。移动受到限制（不能取任意数量）。涉及 Grundy 数的计算和 XOR 组合。

PE 答案：21673752276。

## 题目

给定参数 N 和 M，计算不平衡 Nim 的相关统计量。

## 算法

- 单堆 Nim 的 Grundy 数：G(n) = mex{G(n-m) | m ∈ allowed_moves}
- 多堆 Nim：总 Grundy = G(a₁) ⊕ G(a₂) ⊕ ... ⊕ G(aₙ)
- 必胜局面：Grundy ≠ 0
- Grundy 数通常有周期性，可预计算周期加速
- 使用 DP + 周期检测

## 改编方向

1. **不同移动集合**：斐波那契 Nim、减法 Nim
2. **不同获胜条件**：Misère Nim
3. **带权 Nim**：不同堆有不同价值
4. **多玩家 Nim**：三个玩家轮流
