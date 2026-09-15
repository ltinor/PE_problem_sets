#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 949: Left vs Right II / 小左对小右（二）
// 缩数据版（OJ）：读入 n 和 k（k 为奇数），输出 G(n, k)。
//
// 规则：
//   有 k 个长度为 n 的、由 L/R 组成的单词。
//   小左回合：可以对每个单词从其左侧移除任意个字母（可为 0），但不能移除
//             全部字母，且整回合至少要从某个单词移除一个字母。
//   小右回合：类似地从每个单词右侧移除字母。
//   每个单词只剩 1 个字母时结束。剩余 L 比 R 多则小左胜，反之小右胜。
//   k 为奇数，无平局。
//   G(n,k) = 小左先手时小右有必胜策略的 k 元组（有序）数目。
//
// 算法：直接枚举 + 记忆化博弈搜索。
//   1. 生成全部 2^n 个长度为 n 的单词；
//   2. 枚举所有 k 个单词的有序组合（可重复，用多重集 + 多项式系数计数）；
//   3. 对每个多重集用极小极大博弈树判断小右是否必胜（记忆化）。
//
// 验证点：G(2,3)=14，G(4,3)=496。

static map<string, int> memo; // key = 排序后单词拼接 + 回合 -> 胜者 (0=左,1=右)

// words 为当前各单词；turn=0 小左走，turn=1 小右走。
// 返回 0 表示小左必胜，1 表示小右必胜。
int outcome(vector<string> words, int turn) {
    int k = (int)words.size();
    sort(words.begin(), words.end());

    string key;
    key.reserve(k * 8 + 2);
    for (auto &w : words) { key += w; key += '|'; }
    key += (turn ? 'R' : 'L');

    auto it = memo.find(key);
    if (it != memo.end()) return it->second;

    // 终局：所有单词都是单字母
    bool allOne = true;
    for (auto &w : words) if (w.size() != 1) { allOne = false; break; }
    if (allOne) {
        int L = 0;
        for (auto &w : words) if (w[0] == 'L') L++;
        int res = (2 * L > k) ? 0 : 1; // L > R 则左胜，否则右胜
        memo[key] = res;
        return res;
    }

    int target = (turn == 0) ? 0 : 1; // 当前走棋方希望达到的结果

    vector<string> cur = words;
    // 逐单词枚举本回合可做的选择（乘积），跳过“全部不变”的走法
    function<bool(int)> dfs = [&](int idx) -> bool {
        if (idx == k) {
            bool changed = false;
            for (int i = 0; i < k; i++) {
                if (cur[i] != words[i]) { changed = true; break; }
            }
            if (!changed) return false;
            return outcome(cur, 1 - turn) == target;
        }
        const string &w = words[idx];
        int m = (int)w.size();
        if (m == 1) {
            cur[idx] = w;
            return dfs(idx + 1);
        }
        if (turn == 0) {
            // 小左：取后缀 w[kk..]（移除左侧 kk 个字母），以及“不变”
            for (int kk = 1; kk < m; kk++) {
                cur[idx] = w.substr(kk);
                if (dfs(idx + 1)) return true;
            }
            cur[idx] = w;
            return dfs(idx + 1);
        } else {
            // 小右：取前缀 w[0..m-kk)（移除右侧 kk 个字母），以及“不变”
            for (int kk = 1; kk < m; kk++) {
                cur[idx] = w.substr(0, m - kk);
                if (dfs(idx + 1)) return true;
            }
            cur[idx] = w;
            return dfs(idx + 1);
        }
    };

    int res = dfs(0) ? target : (1 - target);
    memo[key] = res;
    return res;
}

// 枚举 k 个单词的多重集（可重复、不计顺序），用多项式系数累计有序排列数
ll count_multiset(const vector<string> &words, int idx, int k,
                  vector<string> &cur, const vector<ll> &fact) {
    if ((int)cur.size() == k) {
        if (outcome(cur, 0) == 1) { // 小右必胜
            // 计算多重集的有序排列数 k! / prod(cnt!)
            map<string, int> cnt;
            for (auto &w : cur) cnt[w]++;
            ll ways = fact[k];
            for (auto &p : cnt) ways /= fact[p.second];
            return ways;
        }
        return 0;
    }
    if (idx >= (int)words.size()) return 0;
    ll total = 0;
    // 单词 words[idx] 取 0..remaining 个
    int remaining = k - (int)cur.size();
    for (int t = 0; t <= remaining; t++) {
        for (int j = 0; j < t; j++) cur.push_back(words[idx]);
        total += count_multiset(words, idx + 1, k, cur, fact);
        for (int j = 0; j < t; j++) cur.pop_back();
    }
    return total;
}

ll G(int n, int k) {
    vector<string> words;
    for (int mask = 0; mask < (1 << n); mask++) {
        string w;
        for (int i = n - 1; i >= 0; i--) w += ((mask >> i) & 1) ? 'R' : 'L';
        words.push_back(w);
    }
    sort(words.begin(), words.end());

    vector<ll> fact(k + 1, 1);
    for (int i = 2; i <= k; i++) fact[i] = fact[i - 1] * i;

    vector<string> cur;
    return count_multiset(words, 0, k, cur, fact);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    cout << G(n, k) << "\n";
    return 0;
}
