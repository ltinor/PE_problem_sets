# PE700 — Eulercoin (欧拉币)

来源：改编自 Project Euler Problem 700

## 原题意

考虑如下线性同余生成器：
$$E_1 = 1504170715041707$$
$$E_{k+1} = (E_k + 1504170715041707) \bmod 4503599627370517$$

等价地，$E_k = k \cdot 1504170715041707 \bmod 4503599627370517$。

一个"Eulercoin"定义为某个 $E_k$，它严格小于所有之前的 $E_j$（$j < k$）。
求所有 Eulercoin 的和。

PE 答案：1517926517777556。

## 算法

1. **问题转化**：我们需要找序列 $\{k \cdot A \bmod M\}$ 中所有"纪录低点"（record low），
   即比之前所有值都小的那些值。

2. **欧几里得算法**：纪录低点与 $A$ 和 $M$ 的欧几里得算法紧密相关。
   令 $(\text{cur}, \text{prev}) = (A, M)$。
   纪录低点为 $\text{cur}$。
   下一纪录低点为 $\text{prev} \bmod \text{cur}$，如果为 $0$ 则终止。
   但实际上还需要中间的"互补值"：$\text{cur} - (\text{prev} \bmod \text{cur})$。

3. **正确算法**：
   ```
   cur = A, prev = M
   sum = 0
   while cur > 0:
       sum += cur
       r = prev % cur
       if r == 0: break
       cur = cur - r
       prev = prev_before_update  // 即原来的 cur
   ```

4. **示例**：对于 $A=7, M=17$：
   - cur=7, prev=17 → sum=7, r=17%7=3
   - cur=7-3=4, prev=7 → sum=7+4=11, r=7%4=3
   - cur=4-3=1, prev=4 → sum=11+1=12, r=4%1=0 → 终止
   - 欧拉币：$7, 4, 1$，和 $= 12$。

5. **复杂度**：欧几里得算法的步数为 $O(\log M)$，极为高效。

## 改编方向

1. 参数化 $A$ 和 $M$ 的值
2. 改为统计 Eulercoin 的个数而非求和
3. 使用不同的递推公式
4. 求所有纪录高点（record high）之和
5. 在 GF(p) 上考虑类似问题
