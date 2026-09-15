# PE878 — XOR Decimals（异或小数）

来源：改编自 Project Euler Problem 878

## 原题意

与 PE877 使用相同的异或积（XOR-product）定义。考虑方程：
$$(a \otimes a) \oplus (2 \otimes a \otimes b) \oplus (b \otimes b) = k$$

定义 $G(N, m)$ 为所有满足 $k \le m$ 且 $0 \le a \le b \le N$ 的方程解的个数。

已知 $G(1000, 100) = 398$。求 $G(10^{17}, 1\\,000\\,000)$。

PE 答案：741406445589310。

## 算法

1. **异或积计算**：与 PE877 相同，通过按位异或实现多项式乘法。
2. **LHS 分布分析**：
   - 方程左侧 $(a \otimes a) \oplus (2 \otimes a \otimes b) \oplus (b \otimes b)$ 的值域。
   - 统计不同 $(a, b)$ 组合产生的 $k$ 值分布。
3. **累积计数**：$G(N, m) = \sum_{k=1}^{m} g_k(N)$，其中 $g_k(N)$ 是 LHS = k 的解数。
4. **GF(2) 多项式解释**：
   - $A^2 \oplus xAB \oplus B^2 = K(x)$。
   - 对于给定的 N（决定多项式的最大次数），枚举所有可能的 $(A, B)$ 对并计数 $K \le m$ 的组合。
5. **优化**：对于大 N（$10^{17}$），无法直接枚举。需利用多项式环 GF(2)[x] 的代数结构：
   - 分析二次型 $Q(A,B) = A^2 \oplus xAB \oplus B^2$ 的像集大小。
   - 对每个可能的 $K$ 值计算解的数量。

## 改编方向

1. 改变不等式约束（如 $k \ge m$ 或 $m_1 \le k \le m_2$）
2. 不限制 $a \le b$，计算所有有序对的解数
3. 推广到三元或更高元的异或积方程
4. 考虑模某个值后的计数
5. 研究 LHS 的值分布规律
