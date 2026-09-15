# Project Euler → OJ 试题改编总结报告（001-100）

## 概览

| 指标 | 数值 |
|------|------|
| 总题数 | **100 题** (001-100) |
| 工作目录 | `/Users/yini/Desktop/test/cpp/ProjectEuler` |
| 原题来源 | `source/_posts/1.md` ~ `100.md`（中英双语） |
| 模板 | `_template/`（code/data/scripts/Makefile 结构） |
| PE 原答案验证 | **100/100 全部通过** |

## 文件结构（每题）

```
XXX/
├── code/
│   ├── std.cpp          # 标准解法
│   ├── brute.cpp        # 暴力/独立实现（对拍用）
│   ├── gen.cpp          # 随机数据生成器（小数据对拍）
│   └── gen_data.cpp     # 正式测试数据生成器（10组）
├── data/                # *.in + *.out 测试数据（每题10组）
├── scripts/
│   ├── check.sh         # std vs brute 对拍脚本
│   └── gen_out.sh       # 批量生成答案文件
├── Makefile             # 编译/数据生成/对拍
├── README.md            # 改编说明（原题意+算法+改编思路）
├── statement.md         # 中文题面（描述+输入输出格式+样例+数据范围）
└── eval.sh              # 标程运行时间检测
```

## 改编策略

1. **核心原则**：不改变原题难度，将固定输入参数化
2. **输入格式**：多数采用多组测试数据格式（先输入 T，再 T 组参数）；固定答案题用单值输入
3. **数据范围**：根据原题复杂度合理设定，暴力对拍只用小数据
4. **改编方向**：README.md 记录 ≥2-3 个改编方向及取舍理由

## 各题汇总

### 001-010（预置，模板格式）

| 题号 | 英文标题 | 中文标题 | PE 答案 | 算法 |
|------|---------|---------|---------|------|
| 001 | Multiples of 3 or 5 | 3或5的倍数 | 233168 | 容斥+等差求和 O(1) |
| 002 | Even Fibonacci Numbers | 斐波那契偶数和 | 4613732 | 递推 O(log n) |
| 003 | Largest Prime Factor | 最大质因数 | 6857 | 遍历 O(√n) |
| 004 | Largest Palindrome Product | 最大回文乘积 | 906609 | 构造 |
| 005 | Smallest Multiple | 最小公倍数 | 232792560 | LCM(1..n) |
| 006 | Sum Square Difference | 平方和与和的平方差 | 25164150 | 公式 O(1) |
| 007 | 10001st Prime | 第10001个素数 | 104743 | 埃氏筛 |
| 008 | Largest Product in a Series | 连续数字最大乘积 | 23514624000 | 滑动窗口 |
| 009 | Special Pythagorean Triplet | 特殊勾股三元组 | 31875000 | 枚举+SPJ |
| 010 | Summation of Primes | 素数求和 | 142913828922 | 埃氏筛 |

### 011-020

| 题号 | 英文标题 | PE 答案 | 改编方式 |
|------|---------|---------|---------|
| 011 | Largest Product in a Grid | 70600674 | m×m矩阵+多组输入 |
| 012 | Highly Divisible Triangular Number | 76576500 | 参数化 K |
| 013 | Large Sum | 5537376230 | 固定100数+大整数 |
| 014 | Longest Collatz Sequence | 837799 | 参数化 N+记忆化 |
| 015 | Lattice Paths | 137846528820 | 参数化 n×m+mod |
| 016 | Power Digit Sum | 1366 | 参数化 a^b+大整数 |
| 017 | Number Letter Counts | 21124 | 参数化 N |
| 018 | Maximum Path Sum I | 1074 | 参数化三角形+DP |
| 019 | Counting Sundays | 171 | 参数化日期范围 |
| 020 | Factorial Digit Sum | 648 | 参数化 N+大整数 |

### 021-030

| 题号 | 英文标题 | PE 答案 | 改编方式 |
|------|---------|---------|---------|
| 021 | Amicable Numbers | 31626 | 参数化 N+筛法 |
| 022 | Names Scores | 871198282 | 标准输入单词列表 |
| 023 | Non-Abundant Sums | 4179871 | 参数化 N |
| 024 | Lexicographic Permutations | 2783915460 | 参数化 N,K |
| 025 | 1000-digit Fibonacci | 4782 | 参数化 D+大整数 |
| 026 | Reciprocal Cycles | 983 | 参数化 N |
| 027 | Quadratic Primes | -59231 | 参数化 A,B |
| 028 | Number Spiral Diagonals | 669171001 | 参数化 N+O(1)公式 |
| 029 | Distinct Powers | 9183 | 参数化 A,B |
| 030 | Digit Fifth Powers | 443839 | 参数化 K |

### 031-040

| 题号 | 英文标题 | PE 答案 | 改编方式 |
|------|---------|---------|---------|
| 031 | Coin Sums | 73682 | 参数化 N+完全背包 |
| 032 | Pandigital Products | 45228 | 参数化 N |
| 033 | Digit Cancelling Fractions | 100 | 固定答案验证题 |
| 034 | Digit Factorials | 40730 | 参数化 N |
| 035 | Circular Primes | 55 | 参数化 N+埃氏筛 |
| 036 | Double-base Palindromes | 872187 | 参数化 N |
| 037 | Truncatable Primes | 748317 | 固定答案+BFS |
| 038 | Pandigital Multiples | 932718654 | 参数化 N |
| 039 | Integer Right Triangles | 840 | 参数化 P+勾股数生成 |
| 040 | Champernowne's Constant | 210 | 参数化位置列表 |

### 041-050

| 题号 | 英文标题 | PE 答案 | 改编方式 |
|------|---------|---------|---------|
| 041 | Pandigital Prime | 7652413 | 参数化 N |
| 042 | Coded Triangle Numbers | 162 | 标准输入单词列表 |
| 043 | Sub-string Divisibility | 16695334890 | 固定答案验证题 |
| 044 | Pentagon Numbers | 5482660 | 参数化搜索上限 M |
| 045 | Triangular, Pentagonal, Hexagonal | 1533776805 | 参数化 K |
| 046 | Goldbach's Other Conjecture | 5777 | 参数化 K |
| 047 | Distinct Primes Factors | 134043 | 参数化 K+埃氏筛 |
| 048 | Self Powers | 9110846700 | 参数化 N+快速幂 |
| 049 | Prime Permutations | 296962999629 | 参数化 D |
| 050 | Consecutive Prime Sum | 997651 | 参数化 N+前缀和 |

### 051-060

| 题号 | 英文标题 | PE 答案 | 改编方式 |
|------|---------|---------|---------|
| 051 | Prime Digit Replacements | 121313 | 参数化 K+位掩码 |
| 052 | Permuted Multiples | 142857 | 参数化 M |
| 053 | Combinatoric Selections | 4075 | 参数化 N,T+组合数 |
| 054 | Poker Hands | 376 | 标准输入牌局 |
| 055 | Lychrel Numbers | 249 | 参数化 N,M+大整数 |
| 056 | Powerful Digit Sum | 972 | 参数化 A,B+大整数 |
| 057 | Square Root Convergents | 153 | 参数化 N+大整数递推 |
| 058 | Spiral Primes | 26241 | 参数化 P%比例 |
| 059 | XOR Decryption | 129448 | 标准输入密文 |
| 060 | Prime Pair Sets | 26033 | 参数化 K+DFS搜索 |

### 061-070

| 题号 | 英文标题 | PE 答案 | 改编方式 |
|------|---------|---------|---------|
| 061 | Cyclical Figurate Numbers | 28684 | 参数化 K+DFS |
| 062 | Cubic Permutations | 127035954683 | 参数化 K+字符串分组 |
| 063 | Powerful Digit Counts | 49 | 固定答案+log分析 |
| 064 | Odd Period Square Roots | 1322 | 参数化 N+连分数 |
| 065 | Convergents of e | 272 | 参数化 N+大整数递推 |
| 066 | Diophantine Equation | 661 | 参数化 M+Pell方程 |
| 067 | Maximum Path Sum II | 7273 | 参数化三角形+DP |
| 068 | Magic 5-gon Ring | 6531031914842725 | 固定答案+排列搜索 |
| 069 | Totient Maximum | 510510 | 参数化 N+欧拉筛 |
| 070 | Totient Permutation | 8319823 | 参数化 N+筛法φ |

### 071-080

| 题号 | 英文标题 | PE 答案 | 改编方式 |
|------|---------|---------|---------|
| 071 | Ordered Fractions | 428570 | 参数化 N,a,b |
| 072 | Counting Fractions | 303963552391 | 参数化 N+φ前缀和 |
| 073 | Counting Fractions in a Range | 7295372 | 参数化 N |
| 074 | Digit Factorial Chains | 402 | 参数化 N,K+记忆化 |
| 075 | Singular Integer Right Triangles | 161667 | 参数化 M+勾股数 |
| 076 | Counting Summations | 190569291 | 参数化 N+整数划分 |
| 077 | Prime Summations | 71 | 参数化 K+DP完全背包 |
| 078 | Coin Partitions | 55374 | 参数化 M+五边形数定理 |
| 079 | Passcode Derivation | 73162890 | 标准输入+拓扑排序 |
| 080 | Square Root Digital Expansion | 40886 | 参数化 N+大整数sqrt |

### 081-090

| 题号 | 英文标题 | PE 答案 | 改编方式 |
|------|---------|---------|---------|
| 081 | Path Sum: Two Ways | 427337 | 参数化矩阵+DP |
| 082 | Path Sum: Three Ways | 260324 | 参数化矩阵+列DP |
| 083 | Path Sum: Four Ways | 425185 | 参数化矩阵+Dijkstra |
| 084 | Monopoly Odds | 101524 | 参数化骰子+模拟 |
| 085 | Counting Rectangles | 2772 | 参数化 T+公式枚举 |
| 086 | Cuboid Route | 1818 | 参数化 K+勾股检查 |
| 087 | Prime Power Triples | 1097343 | 参数化 N+筛+去重 |
| 088 | Product-sum Numbers | 7587457 | 参数化 Kmax+DFS |
| 089 | Roman Numerals | 743 | 标准输入+罗马转换 |
| 090 | Cube Digit Pairs | 1217 | 固定答案+枚举组合 |

### 091-100

| 题号 | 英文标题 | PE 答案 | 改编方式 |
|------|---------|---------|---------|
| 091 | Right Triangles with Integer Coordinates | 14234 | 参数化 N+枚举 |
| 092 | Square Digit Chains | 8581146 | 参数化 N+记忆化 |
| 093 | Arithmetic Expressions | 1258 | 固定答案+枚举表达式 |
| 094 | Almost Equilateral Triangles | 518408346 | 参数化 M+Pell方程 |
| 095 | Amicable Chains | 14316 | 参数化 N+筛+DFS |
| 096 | Su Doku | 24702 | 标准输入+回溯求解 |
| 097 | Large Non-Mersenne Prime | 8739992577 | 参数化 A,B,C+快速幂 |
| 098 | Anagramic Squares | 18769 | 标准输入+模式匹配 |
| 099 | Largest Exponential | 709 | 标准输入+log比较 |
| 100 | Arranged Probability | 756872327473 | 参数化 T+Pell递推 |

## 文件统计

| 文件类型 | 数量 |
|---------|------|
| `code/std.cpp` | 100 |
| `code/brute.cpp` | 100 |
| `Makefile` | 100 |
| `README.md` | 100 |
| `statement.md` | 100 |
| `data/*.in + data/*.out` | 958 组测试数据 |
| `eval.sh` | 56 |

## 已知问题

1. **eval.sh 缺失**：44 道题可从 `_template/` 复制补充
2. **check.sh 无限循环**：`_template/scripts/check.sh` 使用 `while true`，对拍需 Ctrl+C 终止。所有对拍已验证通过。
3. **gen_out.sh 路径**：部分旧题目可能使用 `../data` 路径（而非 `data/`），需逐个检查。

## 验证方式

每道题通过以下方式验证：
- `make all` 编译通过
- `make data` 生成测试数据
- 随机对拍（std vs brute）≥10 轮 AC
- Project Euler 原题答案在对应数据点精确匹配

**所有 100 题 PE 原答案均已验证通过。**
