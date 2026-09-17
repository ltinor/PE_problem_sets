# Problem 868（PE 868）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=868](https://projecteuler.net/problem=868)。

## **Belfry Maths**

There is a method that is used by Bell ringers to generate all variations of the order that bells are rung.

The same method can be used to create all permutations of a set of letters. Consider the letters to be permuted initially in order from smallest to largest. At each step swap the largest letter with the letter on its left or right whichever generates a permutation that has not yet been seen. If neither gives a new permutation then try the next largest letter and so on. This procedure continues until all permutations have been generated.

For example, $3$ swaps are required to reach the permutation CBA when starting with ABC.<br />
The swaps are ABC $\to$ ACB $\to$ CAB $\to$ CBA.<br />
Also $59$ swaps are required to reach BELFRY when starting with these letters in alphabetical order.

Find the number of swaps that are required to reach NOWPICKBELFRYMATHS when starting with these letters in alphabetical order.

## **钟楼数学**

敲钟人常常使用一种特别的方法来给出所有可能的敲钟顺序。

这种方法也可以用于生成一系列字母所有可能的排列。一开始，所有字母按照字典序从小到大排列。接下来的每一步中，先尝试将最大的字母和其左侧或右侧的字母交换以生成一个新的排列；若无法进行，则转而尝试交换次大的字母，依此类推。不断重复上述步骤即可生成所有可能的排列。

例如，从ABC开始，经过$3$次交换可以得到排列CBA。<br />
交换的过程为ABC $\to$ ACB $\to$ CAB $\to$ CBA。<br />
类似地，从按字典序排列的初始状态开始，经过$59$次交换，可以得到排列BELFRY。

求从按字典序排列的初始状态开始，得到排列NOWPICKBELFRYMATHS所需的交换次数。

---

## 输入格式

（待人工补充：请对照 code/std.cpp 的读取约定描述。）

## 输出格式

（待人工补充。）

## 样例

（无 data 数据，待人工补充。）

---

## 数据范围

（待人工补充；原题参数范围见上方原题描述。）

