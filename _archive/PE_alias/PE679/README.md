# PE679 — FREEFAREA (自由区)

来源：改编自 Project Euler Problem 679

## 原题意

记 $S = \{\text{'A'},\text{'E'},\text{'F'},\text{'R'}\}$。对于 $n \ge 0$，记 $S^*(n)$ 为仅包含 $S$ 中字母且长度为 $n$ 的字符串集合。

定义四个关键词：FREE、FARE、AREA、REEF。

记 $f(n)$ 为 $S^*(n)$ 中恰好包含四个关键词各一次的字符串数目。

已知 $f(9)=1$（唯一的字符串为 FREEFAREA），$f(15)=72863$。

求 $f(30)$。

PE 答案：644997092988678。

## 算法

1. **Aho-Corasick 自动机**：
   - 将四个关键词插入 Trie 树
   - 构建失败链接（failure links）
   - 每个结点维护一个 bitmask 表示以此结点结尾的关键词集合

2. **动态规划**：
   - 状态：`dp[pos][state][mask]` = 长度为 pos、处于自动机状态 state、已包含关键词集合 mask 的字符串数目
   - 转移：枚举下一个字符（A/E/F/R），沿自动机转移，更新 mask
   - 约束：若新匹配的关键词与已有关键词重叠（mask 对应的位已设置），则该转移无效（保证恰好一次）

3. **关键词重叠分析**：
   - FREE: F,R,E,E
   - FARE: F,A,R,E
   - AREA: A,R,E,A
   - REEF: R,E,E,F
   - 关键词之间有后缀-前缀重叠（如 FREE 和 REEF 共享 REE）

4. **复杂度**：
   - 自动机状态数 $S \approx 20$（关键词总长度 = 16）
   - DP 复杂度：$O(n \cdot S \cdot 2^4 \cdot 4)$
   - 对于 $n=30$，计算量约为 $30 \times 20 \times 16 \times 4 \approx 38400$，非常快

## 改编方向

1. 参数化 $n$ 的范围（可达 $10^5$ 或更大）
2. 改变字母表大小或关键词集合
3. 允许关键词出现任意次（非恰好一次）
4. 要求关键词按特定顺序出现
