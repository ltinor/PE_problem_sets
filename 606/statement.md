# Problem 606（PE 606）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=606](https://projecteuler.net/problem=606)。

## **Gozinta Chains II**

A <b>gozinta chain</b> for n is a sequence {1,a,b,...,n} where each element properly divides the next.
For example, there are eight distinct gozinta chains for 12: 
{1,12}, {1,2,12}, {1,2,4,12}, {1,2,6,12}, {1,3,12}, {1,3,6,12}, {1,4,12} and {1,6,12}.

Let S(n) be the sum of all numbers, k, not exceeding n, which have 252 distinct gozinta chains. 
You are given S(10<sup>6</sup>)=8462952 and S(10<sup>12</sup>)=623291998881978.

Find S(10<sup>36</sup>), giving the last nine digits of your answer.

## **因子链II**

n的<b>因子链</b>指的是一个序列{1,a,b,...,n}，其中每个元素都整除后一个元素。
例如，12有八条因子链：
{1,12}，{1,2,12}，{1,2,4,12}，{1,2,6,12}，{1,3,12}，{1,3,6,12}，{1,4,12}和{1,6,12}。 

对于任意n，将所有不超过于n且恰好有252条不同因子链的整数k的和记为S(n)。
已知S(10<sup>6</sup>)=8462952，而S(10<sup>12</sup>)=623291998881978。

求S(10<sup>36</sup>)，并给出其最后九位数字。

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
参考常量: PE_ANSWER = 158452642LL
