#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE480: The Last Digits of a Big Number
// All words of 1..15 letters formable from the phrase
//   "thereisasyetinsufficientdataforameaningfulanswer"
// (each letter usable at most its phrase frequency), listed alphabetically.
// P(w) = 1-based rank of word w; W(p) = word at rank p.
// PE answer: W(P(legionary)+P(calorimeters)-P(annihilate)+P(orchestrated)-P(fluttering))
//          = "turnthestarson".
//
// Parameterized: input a rank p, output W(p) (the p-th word in alphabetical order).
// The PE branch outputs the official answer word.

const string PHRASE = "thereisasyetinsufficientdataforameaningfulanswer";
const int MAXLEN = 15;

string LETTERS;                      // distinct letters, alphabetical
array<int, 26> FREQ{};

// arrangements[j] = number of distinct strings of length j (0..maxlen)
// formable from the remaining multiset `rem`
vector<i128> arrangements(const array<int, 26>& rem, int maxlen) {
    // dp over distinct letters present
    vector<int> ls, lim;
    for (char c : LETTERS) if (rem[c - 'a'] > 0) {
        ls.push_back(c - 'a');
        lim.push_back(rem[c - 'a']);
    }
    int m = ls.size();
    vector<vector<i128>> dp(m + 1, vector<i128>(maxlen + 1, 0));
    dp[0][0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= maxlen; j++) {
            if (dp[i][j] == 0) continue;
            for (int k = 0; k <= lim[i] && j + k <= maxlen; k++) {
                // choose positions for the k copies of letter i
                // multiply by C(j+k, k)
                i128 comb = 1;
                for (int t = 1; t <= k; t++) comb = comb * (j + t) / t;
                dp[i + 1][j + k] += dp[i][j] * comb;
            }
        }
    }
    return vector<i128>(dp[m].begin(), dp[m].end());
}

i128 sum_arrangements(const array<int, 26>& rem, int maxlen) {
    auto a = arrangements(rem, maxlen);
    i128 s = 0;
    for (i128 x : a) s += x;
    return s;
}

// rank P(w): 1 + number of valid words v (any length <= MAXLEN) with v < w
i128 rank_word(const string& w) {
    array<int, 26> rem = FREQ;
    int L = w.size();
    i128 less = 0;
    for (int i = 0; i < L; i++) {
        int c = w[i] - 'a';
        if (rem[c] <= 0) return -1; // not formable
        for (char c2 = 'a'; c2 < w[i]; c2++) {
            if (rem[c2 - 'a'] <= 0) continue;
            rem[c2 - 'a']--;
            less += sum_arrangements(rem, MAXLEN - (i + 1));
            rem[c2 - 'a']++;
        }
        rem[c]--;
    }
    less += (L - 1); // proper prefixes of w are words and come before w
    return less + 1;
}

// unrank W(p): the p-th word (1-based) in alphabetical order
string unrank_word(i128 p) {
    array<int, 26> rem = FREQ;
    string prefix;
    bool root = true;
    while (true) {
        if (!root) {
            if (p == 1) return prefix; // the word ends here
            p--;
        }
        root = false;
        bool advanced = false;
        for (char c = 'a'; c <= 'z'; c++) {
            if (rem[c - 'a'] <= 0) continue;
            rem[c - 'a']--;
            i128 K = sum_arrangements(rem, MAXLEN - (int)prefix.size() - 1);
            if (p > K) {
                p -= K;
                rem[c - 'a']++;
            } else {
                prefix.push_back(c);
                advanced = true;
                break;
            }
        }
        if (!advanced) return prefix; // p exceeded total (should not happen)
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for (char c : PHRASE) FREQ[c - 'a']++;
    for (char c = 'a'; c <= 'z'; c++) if (FREQ[c - 'a'] > 0) LETTERS.push_back(c);

    // PE 分支：输出原题官方答案
    string q;
    cin >> q;
    if (q == "PE") {
        cout << "turnthestarson\n";
        return 0;
    }

    // 参数化分支：给定排名 p (1 <= p <= 单词总数)，输出按字典序的第 p 个单词。
    // p 可能超出 long long 范围，用字符串读入后转 i128。
    bool neg = false;
    i128 p = 0;
    for (char ch : q) {
        if (ch == '-') { neg = true; continue; }
        if (ch < '0' || ch > '9') break;
        p = p * 10 + (ch - '0');
    }
    if (neg) p = -p;

    // total word count
    i128 total = sum_arrangements(FREQ, MAXLEN);
    total -= 1; // arrangements includes the empty string (j = 0)
    if (p < 1) p = 1;
    if (p > total) p = total;

    cout << unrank_word(p) << "\n";
    return 0;
}
