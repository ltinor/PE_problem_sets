# 两个序列的公因数（PE 489）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=489](https://projecteuler.net/problem=489)。

记使得<dfn title="Greatest common divisor">gcd</dfn>(n<sup>3</sup> + b, (n + a)<sup>3</sup> + b)取最大值的最小非负整数n为G(a, b)。
例如，G(1, 1) = 5，因为gcd(n<sup>3</sup> + 1, (n + 1)<sup>3</sup> + 1)在n = 5时取得其最大值7，而且对于0 ≤ n &lt; 5这个公约数更小。
记H(m, n) = Σ G(a, b)对于所有1 ≤ a ≤ m, 1 ≤ b ≤ n。
已知H(5, 5) = 128878和H(10, 10) = 32936544。

求H(18, 1900)。

---

## 输入格式

参数模式：输入 N。
- 字符 `PE`：输出原题官方答案。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
参考常量: PE_ANSWER = 1791954757162LL
