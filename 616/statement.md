# Problem 616（PE 616）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=616](https://projecteuler.net/problem=616)。

## **Creative numbers**

Alice plays the following game, she starts with a list of integers $L$ and on each step she can either:
- remove two elements $a$ and $b$ from $L$ and add $a^b$ to $L$
- or conversely remove an element $c$ from $L$ that can be written as $a^b$, with $a$ and $b$ being two integers such that $a, b > 1$, and add both $a$ and $b$ to $L$

For example starting from the list $L=\{8\}$, Alice can remove $8$ and add $2$ and $3$ resulting in $L=\{2,3\}$ in a first step. Then she can obtain $L=\{9\}$ in a second step.

Note that the same integer is allowed to appear multiple times in the list.

An integer $n>1$ is said to be <i>creative</i> if for any integer $m>1$ Alice can obtain a list that contains $m$ starting from $L=\{n\}$.

Find the sum of all creative integers less than or equal to $10^{12}$.

## **创意数**

爱丽丝正在这样一个游戏：她从整数列表$L$开始，每一步她可以：
- 从$L$中去除两个元素$a$和$b$，并将$a^b$加入$L$
- 或者相反地，从$L$中去除一个可以写成$a^b$形式的元素$c$，其中$a$和$b$均为整数且$a, b > 1$，然后将$a$和$b$加入$L$

例如，从整数列表$L=\{8\}$开始，第一步爱丽丝可以去除$8$并加入$2$和$3$，得到$L=\{2,3\}$。然后第二步她可以得到$L=\{9\}$。

注意在列表中同一整数允许重复出现多次。

称整数$n>1$为<i class=zh>创意数</i>，如果对于任意整数$m>1$，爱丽丝都能从$L=\{n\}$开始得到一个包含有$m$的整数列表。

找出所有小于或等于$10^{12}$的创意数之和。

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
参考常量: PE_ANSWER = 310884668312456458LL
