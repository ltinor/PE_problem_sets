# PE 647 — Linear Transformations of Polygonal Numbers（多边形数线性变换）

## 原题

[Project Euler #647](https://projecteuler.net/problem=647)

对于任意三角形数 T_n，存在正整数 A、B 使得对任意 n，AT_n + B 仍是三角形数。对所有满足 max(A, B) ≤ N 的 (A, B) 对，记 (A+B) 之和为 F₃(N)。例如 F₃(100) = 184。

k 边形数的公式为：P_k(n) = ½ n(n(k-2) + 4 - k)，其中 n ≥ 1。k = 3 时即为三角形数。

对所有奇数 k = 3, 5, 7, … 定义 F_k(N)。已知 Σ_k F_k(10³) = 14993。

求 Σ_k F_k(10¹²)（对所有奇数 k）。

**答案：563132994**

## 算法

- 参数化：设 T = k - 2（奇数）。令 m = a·n - b，代入恒等式 A·P_k(n) + B = P_k(m)，匹配 n 的各次幂系数。
- 导出约束：A = a²，其中 a ≡ 1 (mod T)。设 a = 2t·T + 1（t ≥ 1）。
- T = 1 特例：A = (2t+1)²，B = t(t+1)/2。
- T > 1 一般情况：b = (T-2)t，B = b(T·b + T - 2) / 2。
- 枚举 t 累加 A+B 直到 max(A, B) > N。

## 文件

| 文件 | 说明 |
|------|------|
| `code/std.cpp` | 标准解法（PE 模式输出答案，verify 模式验证样例） |

## 编译运行

```bash
g++ -std=c++17 -O2 code/std.cpp -o code/std
echo "PE" | ./code/std        # 输出 PE 答案
echo "verify" | ./code/std    # 验证已知样例
```
