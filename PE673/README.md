# PE673 — 床与桌 (Beds and Desks)

来源：改编自 Project Euler Problem 673

## 原题意

"Beds and Desks"（床与桌）是 Young 图（杨表）中钩长（hook length）公式的形象化称呼。在一个 Young 图中，每个格子的"钩"（hook）由该格子自身、其右侧所有格子（"桌" / arm）和其下方所有格子（"床" / leg）组成。

问题涉及统计满足特定钩长约束的 Young 图数量，或计算与钩长公式相关的计数问题。

PE 答案：70032538033373。

## 算法

1. **钩长公式（Hook-length Formula）**：
   对于形状 λ 的标准杨表数量：
   f^λ = n! / ∏_{c∈λ} h(c)
   其中 h(c) 是格子 c 的钩长

2. 枚举 Young 图（整数划分），计算钩长乘积
3. 使用动态规划或递推高效枚举满足约束的划分
4. 大数运算处理阶乘和钩长乘积

## 改编方向

1. 限制 Young 图的形状（如最多 k 行 k 列）
2. 统计满足钩长约束的划分数量
3. 考虑半标准杨表（semistandard Young tableaux）
4. 推广到斜杨表（skew Young tableaux）
