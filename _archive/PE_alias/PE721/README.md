# PE721 — High powers of irrational numbers (无理数高次幂)

来源：改编自 Project Euler Problem 721

## 原题意

考虑函数 $f(a,n)=\lfloor(\lceil\sqrt{a}\rceil+\sqrt{a})^n\rfloor$，其中 $\lfloor\cdot\rfloor$ 代表下取整，$\lceil\cdot\rceil$ 代表上取整。

已知 $f(5,2)=27$，$f(5,5)=3935$。

定义 $G(n)=\sum_{a=1}^n f(a,a^2)$。已知 $G(1000)\bmod 999999937=163861845$。

求 $G(5000000)\bmod 999999937$。

PE 答案：700792959。

## 算法

1. **共轭技巧**：令 $r=\lceil\sqrt{a}\rceil$。则 $(r+\sqrt{a})^n+(r-\sqrt{a})^n=2X_n$ 为整数，其中 $X_n$ 满足递推：
   $$X_{n+1}=rX_n+aY_n,\quad Y_{n+1}=X_n+rY_n,\quad X_0=1,Y_0=0$$

2. **取整公式**：由于 $0\leq r-\sqrt{a}<1$（非完全平方数时严格），有 $(r-\sqrt{a})^{a^2}\in[0,1)$。
   - 若 $a$ 为完全平方数：$f(a,a^2)=(2\sqrt{a})^{a^2}$
   - 否则：$f(a,a^2)=2X_{a^2}-1$

3. **矩阵快速幂**：递推可写为矩阵形式 $\begin{bmatrix}X_{n+1}\\Y_{n+1}\end{bmatrix}=\begin{bmatrix}r&a\\1&r\end{bmatrix}\begin{bmatrix}X_n\\Y_n\end{bmatrix}$。使用矩阵快速幂计算 $M^{a^2}\bmod 999999937$，每次 $O(\log a^2)$。

4. **按 $r$ 分组处理**：$r=\lceil\sqrt{a}\rceil$，$a\in[(r-1)^2+1,r^2]$。共约 $2\sqrt{N}\approx 4472$ 组。

5. **复杂度**：对 $N=5\times 10^6$，约 $5\times 10^6\times 45$ 次 $2\times 2$ 矩阵乘法（模 $10^9$ 级素数），可在数分钟内完成。

## 改编方向

1. 改变指数形式（如 $f(a,n)=\lfloor(\lceil\sqrt{a}\rceil+\sqrt{a})^k\rfloor$ 其中 $k$ 为其他函数）
2. 使用不同的取整方式或模数
3. 考虑 $\lfloor(a+\sqrt{b})^n\rfloor$ 的更一般形式
4. 求序列的周期或特定项而非前缀和
