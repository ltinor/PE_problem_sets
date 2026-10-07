# Problem 678（PE 678）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=678](https://projecteuler.net/problem=678)。

## **Fermat-like Equations**

If a triple of positive integers $(a, b, c)$ satisfies $a^2+b^2=c^2$, it is called a Pythagorean triple. No triple $(a, b, c)$ satisfies $a^e+b^e=c^e$ when $e \ge 3$ (Fermat's Last Theorem). However, if the exponents of the left-hand side and right-hand side differ, this is not true. For example, $3^3+6^3=3^5$.

Let $a, b, c, e, f$ be all positive integers, $0 \lt a \lt b$, $e \ge 2$, $f \ge 3$ and $c^f \le N$. Let $F(N)$ be the number of $(a, b, c, e, f)$ such that $a^e+b^e=c^f$. You are given $F(10^3) = 7$, $F(10^5) = 53$ and $F(10^7) = 287$.

Find $F(10^{18})$.

## **费马式方程**

若正整数三元组$(a, b, c)$满足$a^2+b^2=c^2$，则称之为毕达哥拉斯三元组。根据费马大定理，对于任意$e \ge 3$，不存在三元组$(a, b, c)$满足$a^e+b^e=c^e$。不过，若等号左侧和右侧所选择的指数不同，则方程可能有解。例如，$3^3+6^3=3^5$。

令$a, b, c, e, f$为正整数，且$0 \lt a \lt b$，$e \ge 2$，$f \ge 3$，$c^f \le N$。记$F(N)$为使得$a^e+b^e=c^f$的数组$(a, b, c, e, f)$总数。已知$F(10^3) = 7$，$F(10^5) = 53$，$F(10^7) = 287$。

求$F(10^{18})$。

---

## 输入格式

字符 `PE`：输出原题官方答案。

## 输出格式

原题官方答案。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
参考常量: PE_ANSWER = 1986065
