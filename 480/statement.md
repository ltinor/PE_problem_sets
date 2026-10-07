# 最后一问（PE 480）

## 题目描述

考虑所有从下面这个词组中选取字母并任意排列所能构成的词汇：

**thereisasyetinsufficientdataforameaningfulanswer**

（每个字母使用的次数不能超过它在词组中出现的次数。）

将其中包括少于或等于 15 个字母的单词按照**字典序**排列，并且从 1 开始逐个编号。例如：

```
1  : a
2  : aa
6  : aaaaaa
10 : aaaaaacdee
115246685191495243 : euler
525069350231428029 : ywuuttttssssrrr
```

记 $P(w)$ 是单词 $w$ 在列表中的位置，$W(p)$ 是列表中位置 $p$ 上的单词，两者互为反函数。

给定位置 $p$，输出 $W(p)$。

原题（PE480）求

$$W\big(P(\text{legionary}) + P(\text{calorimeters}) - P(\text{annihilate}) + P(\text{orchestrated}) - P(\text{fluttering})\big)$$

其值为位置 $451023621685297214$ 上的单词，官方答案为 `turnthestarson`。

---

## 输入格式

第一行一个 token：

- 若为 `PE`，输出原题官方答案 `turnthestarson`；
- 否则为整数 $p$（$1 \le p \le 525069350231428029$），表示列表中的位置。

---

## 输出格式

一行一个字符串：位置 $p$ 上的单词（仅小写字母）。

---

## 样例

### 输入

```
115246685191495243
```

### 输出

```
euler
```

---

## 数据范围

- 若输入为 `PE`，输出 `turnthestarson`；
- 否则 $1 \le p \le 525069350231428029$（单词总数）。
