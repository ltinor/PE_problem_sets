#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 400（缩数据版）：斐波那契树游戏
// T(k) = 根 + T(k-1) + T(k-2)，取走节点及其子树，被迫取整棵树根者输。
// f(k) = 首回合必胜移动数。缩数据：k <= 6。
// 验证点：f(5) = 1。

int n, root;
vector<int> sub;
unordered_map<int,bool> memo;

// win(mask)：mask 含毒药根。返回当前玩家是否必胜。
bool win(int mask) {
    auto it = memo.find(mask);
    if (it != memo.end()) return it->second;
    if (mask == (1 << root)) { memo[mask] = false; return false; } // 只剩毒药根
    int m = mask;
    while (m) {
        int low = m & -m;
        int i = __builtin_ctz(low);
        m ^= low;
        if (i == root) continue; // 取毒药根=输
        if (!win(mask & ~sub[i])) { memo[mask] = true; return true; }
    }
    memo[mask] = false;
    return false;
}

vector<string> tree_paths(int k) {
    if (k == 0) return {};
    if (k == 1) return {""};
    vector<string> res = {""};
    for (auto& p : tree_paths(k-1)) res.push_back("L" + p);
    for (auto& p : tree_paths(k-2)) res.push_back("R" + p);
    return res;
}

ll f(int k) {
    vector<string> paths = tree_paths(k);
    sort(paths.begin(), paths.end());
    n = paths.size();
    sub.assign(n, 0);
    for (int i = 0; i < n; i++) {
        int mask = 0;
        for (int j = 0; j < n; j++)
            if (paths[j].rfind(paths[i], 0) == 0) mask |= (1 << j);
        sub[i] = mask;
    }
    for (int i = 0; i < n; i++) if (paths[i] == "") { root = i; break; }
    memo.clear();
    int full = (1 << n) - 1;
    win(full);
    ll cnt = 0;
    for (int i = 0; i < n; i++) {
        if (i == root) continue;
        if (!win(full & ~sub[i])) cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll k;
    cin >> k;
    if (k > 6) {
        cout << "k 超出缩数据范围（需 k <= 6）\n";
        return 0;
    }
    cout << f((int)k) << "\n";
    return 0;
}
