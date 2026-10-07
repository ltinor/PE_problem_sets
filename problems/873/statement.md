# Problem 873（PE 873）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=873](https://projecteuler.net/problem=873)。

## **Words with Gaps**

Let $W(p,q,r)$ be the number of words that can be formed using the letter A $p$ times, the letter B $q$ times and the letter C $r$ times with the condition that every A is separated from every B by at least two Cs. For example, CACACCBB is a valid word for $W(2,2,4)$ but ACBCACBC is not.

You are given $W(2,2,4)=32$ and $W(4,4,44)=13908607644$.

Find $W(10^6,10^7,10^8)$. Give your answer modulo $1\ 000\ 000\ 007$.

## **带间隔的单词**

记$W(p,q,r)$为由$p$个A、$q$个B和$r$个C构成、且任意A和B之间间隔至少两个C的单词数目。例如，对于$W(2,2,4)$，CACACCBB是一个合法单词，而ACBCACBC不是。

已知$W(2,2,4)=32$，$W(4,4,44)=13908607644$。

求$W(10^6,10^7,10^8)$, 并对$1\ 000\ 000\ 007$取余作为你的答案。

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
参考常量: PE_ANSWER = 644288016LL
