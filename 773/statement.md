# Problem 773（PE 773）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=773](https://projecteuler.net/problem=773)。

## **Ruff Numbers**

Let $S_k$ be the set containing $2$ and $5$ and the first $k$ primes that end in $7$. For example, $S_3 = \\\{2,5,7,17,37\\\}$.

Define a $k$-<i>Ruff</i> number to be one that is not divisible by any element in $S_k$.

If $N_k$ is the product of the numbers in $S_k$ then define $F(k)$ to be the sum of all $k$-Ruff numbers less than $N_k$ that have last digit $7$. You are given $F(3) = 76101452$.

Find $F(97)$, give your answer modulo $1\ 000\ 000\ 007$.

## **仿粗糙数**

记$S_k$为$2$、$5$和前$k$个以$7$结尾的素数所构成的集合。例如，$S_3 = \\\{2,5,7,17,37\\\}$。

如果一个数不能被$S_k$中的任意元素整除，则称之为$k$-<i class=zh>仿粗糙数</i>。

若$N_k$为$S_k$中的元素之积，则定义$F(k)$为所有小于$N_k$且以$7$结尾的$k$-仿粗糙数之和。已知$F(3) = 76101452$。

求$F(97)$，并将你的答案对$1\ 000\ 000\ 007$取余。

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
参考常量: PE_ANSWER = 55620670LL
