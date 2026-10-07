# Problem 572（PE 572）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=572](https://projecteuler.net/problem=572)。

## **Idempotent matrices**

A matrix $M$ is called idempotent if $M^2 = M$.
Let $M$ be a three by three matrix : 
$M=\begin{pmatrix} 
  a & b & c\\\ 
  d & e & f\\\
  g &h &i\\\
\end{pmatrix}$.
Let C($n$) be the number of idempotent three by three matrices $M$ with integer elements such that
$ -n \le a,b,c,d,e,f,g,h,i \le n$.

C(1)=164 and C(2)=848.

Find C(200).

## **幂等矩阵**

若矩阵$M$满足$M^2 = M$，则称其为幂等矩阵。
令$M$为三阶矩阵：
$M=\begin{pmatrix} 
  a & b & c\\\
  d & e & f\\\
  g &h &i\\\
\end{pmatrix}$。
记C($n$)为满足以下条件的三阶幂等矩阵$M$的数目：其元素均为整数且满足
$ -n \le a,b,c,d,e,f,g,h,i \le n$.

已知C(1)=164和C(2)=848。

求C(200)。

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
