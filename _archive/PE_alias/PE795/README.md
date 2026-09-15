# PE795 — Alternating gcd sum（交替GCD和）

来源：改编自 Project Euler Problem 795

## 原题意

计算带有交替符号的 $\gcd$ 求和：
$$S(N) = \sum_{i=1}^{N} \sum_{j=1}^{N} (-1)^{i+j} \cdot \gcd(i, j)$$
或类似的交替形式（仅在 $i$ 上交替、或仅考虑 $i=j$ 等）。问题可能要求对某个大 $N$ 求出该和的值。

PE 答案：955892601788276（约 $9.56 \times 10^{14}$）。

## 算法

1. **朴素 $\gcd$ 和**：$\sum_{i,j=1}^N \gcd(i,j) \approx \frac{6}{\pi^2} N^2 \log N$（渐近估计）。
2. **交替符号处理**：利用 $(-1)^{i+j} = (-1)^i \cdot (-1)^j$ 分离变量，可优化为 $O(N)$ 或更快。
3. **Pillai 函数**：$P(n) = \sum_{k=1}^n \gcd(k, n)$，是乘性函数，可用 Dirichlet 卷积表示。
4. **数论分块**：利用 $\lfloor N/d \rfloor$ 的分段常值性质加速求和。
5. **莫比乌斯反演**：$\gcd(i,j) = \sum_{d|\gcd(i,j)} \varphi(d)$，可转化为对 $\varphi$ 函数的求和。

## 改编方向

1. 推广到 $\sum (-1)^{i+j+k} \gcd(i,j,k)$ 三元版本
2. 用 $\text{lcm}$ 或 $\text{lcm}/\gcd$ 代替 $\gcd$
3. 改变交替模式（如 $(-1)^{\gcd(i,j)}$）
4. 加权交替：$\sum w_i w_j (-1)^{i+j} \gcd(i,j)$
5. 限制在 $i,j$ 互质的条件下
