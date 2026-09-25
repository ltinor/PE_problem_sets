# 最后一问（PE 480）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=480](https://projecteuler.net/problem=480)。

考虑所有从下面这个词组中选取字母并任意排列所能构成的词汇：

<center>**thereisasyetinsufficientdataforameaningfulanswer**</center>

将其中包括少于或等于15个字母的单词按照**字典序**排列，并且从1开始逐个编号。
这个列表大致如下所示：

1 : a
2 : aa
3 : aaa
4 : aaaa
5 : aaaaa
6 : aaaaaa
7 : aaaaaac
8 : aaaaaacd
9 : aaaaaacde
10 : aaaaaacdee
11 : aaaaaacdeee
12 : aaaaaacdeeee
13 : aaaaaacdeeeee
14 : aaaaaacdeeeeee
15 : aaaaaacdeeeeeef
16 : aaaaaacdeeeeeeg
17 : aaaaaacdeeeeeeh
...
28 : aaaaaacdeeeeeey
29 : aaaaaacdeeeeef
30 : aaaaaacdeeeeefe
...
115246685191495242: euleoywuttttsss
115246685191495243: euler
115246685191495244: eulera
...
525069350231428029: ywuuttttssssrrr

记P(w)是单词w在列表中的位置。
记W(p)是列表中位置p上的单词。
可以看出P(w)和W(p)互为反函数：P(W(p)) = p且W(P(w)) = w。

举例如下：

W(10) = aaaaaacdee
P(aaaaaacdee) = 10
W(115246685191495243) = euler
P(euler) = 115246685191495243

求W(P(legionary) + P(calorimeters) - P(annihilate) + P(orchestrated) - P(fluttering))。
你的答案中应只包含小写字母，没有空格和标点符号。

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
