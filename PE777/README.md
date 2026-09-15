# PE777 — LCM of sum of divisors（约数和的LCM）

来源：改编自 Project Euler Problem 777

## 原题意

定义 $\sigma(n)$ 为 $n$ 的所有正约数之和。问题涉及对一系列 $\sigma(n)$ 值取最小公倍数（LCM）。

可能的形式包括：
- $\operatorname{lcm}\{\sigma(1), \sigma(2), \dots, \sigma(N)\}$ 的渐近行为
- 某种与 $\sigma$-LCM 相关的概率或密度

PE 答案：0.000238077（一个极小的正数，约 $2.38 \times 10^{-4}$）。

## 算法

1. **计算 $\sigma(n)$**：通过质因数分解，$\sigma(n) = \prod (p_i^{e_i+1} - 1) / (p_i - 1)$。
2. **LCM 计算**：维护各质因子的最大幂次，$\operatorname{lcm}(a, b) = a \cdot b / \gcd(a, b)$。
3. **渐近分析**：$\sigma(n)$ 的增长与除数函数相关，LCM 的增长速度极快。
4. **极限比值**：答案 $0.000238077$ 可能是某种极限比值，如 $\lim_{N \to \infty} \frac{\log \operatorname{lcm}(\sigma(1..N))}{N \log N}$ 的倒数。

## 改编方向

1. 推广到 $\sigma_k(n)$（约数的 $k$ 次幂之和）
2. 计算 $\gcd$ 而非 $\operatorname{lcm}$ 的极限行为
3. 对特定数论函数族（如 $\varphi(n)$）做类似分析
4. 在模 $M$ 下计算 LCM（避免溢出）
5. 研究 $\sigma$-LCM 中出现的质数分布
