# PE877 — XOR Problem（异或问题）

来源：改编自 Project Euler Problem 877

## 原题意

定义 **异或积**（XOR-product）$x \otimes y$：模仿二进制长乘法，但将中间结果的相加替换为按位异或（XOR）。

例如：$7 \otimes 3 = 9$，即 $111_2 \otimes 11_2 = 1001_2$。

考虑方程：
$$(a \otimes a) \oplus (2 \otimes a \otimes b) \oplus (b \otimes b) = 5$$

定义 $X(N)$ 为所有满足 $0 \le a \le b \le N$ 的方程解中 $b$ 取值的按位异或结果。

已知 $X(10) = 5$。求 $X(10^{18})$。

PE 答案：178741697。

## 算法

1. **异或积计算**：对整数 x, y，遍历 y 的每一位，若该位为 1 则将 x 左移相应位数后与结果异或。
2. **GF(2) 多项式解释**：
   - 异或积对应于 GF(2)[x] 中的多项式乘法。
   - $a \otimes a$ 对应 $A(x)^2$，$b \otimes b$ 对应 $B(x)^2$。
   - $2 \otimes a \otimes b$ 对应 $x \cdot A(x) \cdot B(x)$。
3. **方程简化**：
   - 在特征为 2 的域中：$(A \oplus B)^2 = A^2 \oplus B^2$。
   - 方程变为：$(A \oplus B)^2 \oplus x \cdot A \cdot B = x^2 + 1$。
4. **求解策略**：在 GF(2)[x] 中分析二次型的解结构，通过遍历 GF(2) 多项式空间或使用代数方法计算。
5. **XOR 汇总**：对满足条件的解，将所有 $b$ 值异或起来。

## 改编方向

1. 改变方程右侧的常数（如 $k=3, 7, 15$ 等）
2. 推广到 GF(p)[x]（p 为奇素数）
3. 研究异或积的代数性质（结合律、分配律等）
4. 与 Nim 乘法（Nim-product）的关系
5. 扩展到高维的多项式环
