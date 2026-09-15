# PE831 — Chinese Remainder Twice（二次中国剩余）

来源：改编自 Project Euler Problem 831

## 原题意

将中国剩余定理（CRT）应用两次。第一轮将一部分同余方程合并为一个模数 $M$；第二轮再将此结果与剩余的同余方程联立求解。

形式化：给定两组同余方程：
- 组 A：$x \equiv a_i \pmod{p_i},\; i=1..k$
- 组 B：$x \equiv b_j \pmod{q_j},\; j=1..l$

第一轮 CRT 合并组 A 得 $x \equiv X_A \pmod{P}$（其中 $P = \operatorname{lcm}(p_i)$）；第二轮将 $(X_A, P)$ 与组 B 联立，得到最终解模 $\operatorname{lcm}(P, q_1, \dots, q_l)$。

PE 答案：223153684303778（约 $2.2 \times 10^{14}$）。

## 算法

1. **扩展欧几里得算法**：求模逆元，用于两两合并同余方程。
2. **CRT 合并**：$x \equiv r_1 \pmod{m_1}$ 与 $x \equiv r_2 \pmod{m_2}$ 合并为 $x \equiv x_0 \pmod{\operatorname{lcm}(m_1,m_2)}$。
3. **两阶段策略**：先将部分同余方程预合并，简化后续计算。
4. **多模数联立**：循环调用两两合并，处理任意数量的同余方程。

## 改编方向

1. 嵌套多层 CRT（$n$ 阶段而非仅两阶段）
2. 同余方程的分组策略优化
3. 不同分组对最终解的影响
4. 推广到多项式同余（中国剩余定理在多项式环上的推广）
5. 与 Garner 算法和混合基数表示的联系
