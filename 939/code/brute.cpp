#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 939 brute force（验证用）：直接做博弈搜索 + 枚举所有局面。
// 输入 N，输出 E(N) mod 1234567891。仅用于小 N 的对照验证。

const ll MOD = 1234567891LL;

// 用 sorted vector 作为规范形，去掉 0。
vector<int> norm(vector<int> v) {
    v.erase(remove(v.begin(), v.end(), 0), v.end());
    sort(v.begin(), v.end());
    return v;
}

// 局面 -> 结果 的记忆化。key 编码为字符串。
unordered_map<string, int> memo;

// outcome(A, B, turn): A 是否能赢。turn 0=A 先手, 1=B 先手。
// 返回 1 = A 胜，0 = B 胜。
int outcome(vector<int> A, vector<int> B, int turn) {
    A = norm(A);
    B = norm(B);
    string key;
    for (int x : A) { key += to_string(x); key += ','; }
    key += '|';
    for (int x : B) { key += to_string(x); key += ','; }
    key += (turn ? 'B' : 'A');

    auto it = memo.find(key);
    if (it != memo.end()) return it->second;

    if (A.empty() && B.empty()) {
        // 无石子：上一手拿走了最后一枚并获胜。
        // A 先手面对空 -> 上一手是 B -> A 负；B 先手面对空 -> 上一手是 A -> A 胜。
        int res = turn;   // turn==1 时 A 胜
        memo[key] = res;
        return res;
    }

    int res;
    if (turn == 0) {
        // A 的回合：A 有任一制胜走法即可。
        res = 0;
        // 从 B 堆拿走 1 枚
        for (int i = 0; i < (int)B.size() && !res; i++) {
            vector<int> nb = B; nb[i]--;
            if (outcome(A, nb, 1)) res = 1;
        }
        // 移除整个 A 堆
        for (int i = 0; i < (int)A.size() && !res; i++) {
            vector<int> na = A; na[i] = 0;
            if (outcome(na, B, 1)) res = 1;
        }
    } else {
        // B 的回合：B 若存在让 A 输的走法，则 A 输。
        res = 1;
        // B 从 A 堆拿走 1 枚
        for (int i = 0; i < (int)A.size() && res; i++) {
            vector<int> na = A; na[i]--;
            if (!outcome(na, B, 0)) res = 0;
        }
        // B 移除整个 B 堆
        for (int i = 0; i < (int)B.size() && res; i++) {
            vector<int> nb = B; nb[i] = 0;
            if (!outcome(A, nb, 0)) res = 0;
        }
    }
    memo[key] = res;
    return res;
}

// 枚举 n 的所有整数划分（非递增）。n==0 时仅一个空划分。
void gen_partitions(int n, vector<vector<int>>& out) {
    if (n == 0) { out.push_back({}); return; }
    function<void(int, int, vector<int>&)> dfs =
        [&](int rem, int mx, vector<int>& cur) {
            if (rem == 0) { out.push_back(cur); return; }
            for (int k = min(rem, mx); k >= 1; k--) {
                cur.push_back(k);
                dfs(rem - k, k, cur);
                cur.pop_back();
            }
        };
    vector<int> cur;
    dfs(n, n, cur);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    if (!(cin >> N)) return 0;
    if (N < 0) return 0;

    // 预生成 0..N 的划分表
    vector<vector<vector<int>>> parts(N + 1);
    for (int s = 0; s <= N; s++) gen_partitions(s, parts[s]);

    ll ans = 0;
    for (int total = 1; total <= N; total++) {
        for (int sa = 0; sa <= total; sa++) {
            int sb = total - sa;
            for (auto& pa : parts[sa]) {
                for (auto& pb : parts[sb]) {
                    if (outcome(pa, pb, 0) && outcome(pa, pb, 1)) {
                        ans++;
                    }
                }
            }
        }
    }
    cout << ans % MOD << "\n";
    return 0;
}
