#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 949 朴素版：直接枚举所有 k 元组（有序、可重复），不做多重集压缩。
// 用于和 std.cpp 对拍。同样采用记忆化博弈搜索。

static map<string, int> memo;

int outcome(vector<string> words, int turn) {
    int k = (int)words.size();
    sort(words.begin(), words.end());
    string key;
    key.reserve(k * 8 + 2);
    for (auto &w : words) { key += w; key += '|'; }
    key += (turn ? 'R' : 'L');
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;

    bool allOne = true;
    for (auto &w : words) if (w.size() != 1) { allOne = false; break; }
    if (allOne) {
        int L = 0;
        for (auto &w : words) if (w[0] == 'L') L++;
        int res = (2 * L > k) ? 0 : 1;
        memo[key] = res;
        return res;
    }

    int target = (turn == 0) ? 0 : 1;
    vector<string> cur = words;
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
        if (m == 1) { cur[idx] = w; return dfs(idx + 1); }
        if (turn == 0) {
            for (int kk = 1; kk < m; kk++) { cur[idx] = w.substr(kk); if (dfs(idx + 1)) return true; }
            cur[idx] = w;
            return dfs(idx + 1);
        } else {
            for (int kk = 1; kk < m; kk++) { cur[idx] = w.substr(0, m - kk); if (dfs(idx + 1)) return true; }
            cur[idx] = w;
            return dfs(idx + 1);
        }
    };
    int res = dfs(0) ? target : (1 - target);
    memo[key] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<string> words;
    for (int mask = 0; mask < (1 << n); mask++) {
        string w;
        for (int i = n - 1; i >= 0; i--) w += ((mask >> i) & 1) ? 'R' : 'L';
        words.push_back(w);
    }

    // 枚举所有有序 k 元组
    vector<int> idx(k, 0);
    ll cnt = 0;
    while (true) {
        vector<string> cur(k);
        for (int i = 0; i < k; i++) cur[i] = words[idx[i]];
        if (outcome(cur, 0) == 1) cnt++;
        // 下一个元组
        int p = k - 1;
        while (p >= 0 && ++idx[p] >= (int)words.size()) { idx[p] = 0; p--; }
        if (p < 0) break;
    }
    cout << cnt << "\n";
    return 0;
}
