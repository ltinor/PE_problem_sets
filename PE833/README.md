# PE833 — Square Triangle Products（三角平方乘积）

来源：改编自 Project Euler Problem 833

## 原题意

研究能够表示为平方数与三角数之积的数，即形如 $a^2 \times \frac{b(b+1)}{2}$ 的数。平方数 $a^2$ 与三角数 $T_b = b(b+1)/2$ 的乘积构成了一类特殊的整数集合。

进一步，可以考察既是平方数又是三角数的数（square-triangular numbers），它们对应 Pell 方程 $x^2 - 8y^2 = 1$ 的解。

PE 答案：928306910。

## 算法

1. **生成三角数**：$T_b = b(b+1)/2 \leq N$。
2. **枚举乘积**：对每个三角数 $t$，枚举平方数 $a^2$，计算 $a^2 \cdot t \leq N$。
3. **去重**：不同的 $(a, b)$ 可能产生相同的乘积，需使用集合或标记数组去重。
4. **复杂度**：约为 $O(\sqrt{N} \log N)$——每个三角数 $t \sim k^2/2$ 对应约 $\sqrt{N/t} \sim \sqrt{2N}/k$ 个平方数。

## 改编方向

1. 推广到三个或多个因子的乘积（如 square × triangular × prime）
2. 计数乘积的不同表示方式数
3. 研究同时为平方数和三角数的数（square-triangular numbers）
4. 高次方推广：$a^3 \times b(b+1)/2$ 等
5. 区间查询优化
