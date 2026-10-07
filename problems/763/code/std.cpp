#include <bits/stdc++.h>
using namespace std;

// PE 763 (简化版): Amoebas in a 3D grid —— 三维格阵中的阿米巴原虫
//
// 一只位于 (x,y,z) 的阿米巴, 在三个目标方格都为空时, 可以分裂为
// (x+1,y,z), (x,y+1,z), (x,y,z+1) 三只。初始时 (0,0,0) 有一只,
// 经过 N 次分裂后共有 2N+1 只。求不同分布总数 D(N)。
//
// 逆向思考: 对最终分布 S(共 2N+1 个格子) 做"合并"操作:
//   若 (x+1,y,z),(x,y+1,z),(x,y,z+1) 均被占据, 则可合并回 (x,y,z)。
// S 可达当且仅当可一路合并回 {(0,0,0)}。
//
// 这等价于统计"满三叉树"(每个内部节点恰好 3 个孩子, 分别朝 +x/+y/+z):
//   根在 (0,0,0), 共 N 个内部节点, 且所有叶子的位置互不相同。
// 叶子位置 = 从根到该叶子各方向步数的计数 (x 步, y 步, z 步)。
// 两个叶子的位置相同 <=> 它们深度相同(位置坐标和为深度)且 (x,y) 投影相同,
// 所以不同深度的叶子自动不同, 只需保证同一层内的叶子投影互不相同。
//
// 逐层 DP(记忆化搜索):
//   状态 = 当前层所有待处理节点的位置(用 (x,y) 投影表示, z = 深度 - x - y),
//          以及还需要放置的内部节点个数 k。
//   每个位置(按多重集分组)选择若干作为内部节点(分裂), 其余作为叶子;
//   同一层内的叶子必须位置互不相同 => 每个位置至多留下 1 个叶子,
//   其余 (多重数-1) 个必须分裂。
//   分裂 (x,y) 产生 (x+1,y),(x,y+1),(x,y) 三个孩子进入下一层。
//   状态按平移(min x / min y 归零)归一化后作为 key。
//
// 时间复杂度: 与可达状态数同阶; 对 N <= 20 仅约 3.6 万个状态, 瞬间完成。

using u64 = unsigned long long;

unordered_map<string, u64> memo;

// 归一化并编码: 平移使 min x = min y = 0, 排序后编码为字节串。
static string encode(vector<pair<int,int>> v) {
    if (v.empty()) return "";
    int mx = INT_MAX, my = INT_MAX;
    for (auto &p : v) { mx = min(mx, p.first); my = min(my, p.second); }
    sort(v.begin(), v.end());
    string s;
    s.reserve(v.size() * 4);
    for (auto &p : v) {
        int x = p.first - mx, y = p.second - my;
        s.push_back((char)(x & 0xff)); s.push_back((char)((x >> 8) & 0xff));
        s.push_back((char)(y & 0xff)); s.push_back((char)((y >> 8) & 0xff));
    }
    return s;
}

// 当前层节点多重集 M, 还需要放置 k 个内部节点, 返回方案数。
static u64 solve(const vector<pair<int,int>> &M, int k) {
    if (k == 0) {
        // 不再分裂, 全部成为叶子; 必须互不相同。
        vector<pair<int,int>> s = M;
        sort(s.begin(), s.end());
        for (size_t i = 1; i < s.size(); ++i) if (s[i] == s[i - 1]) return 0;
        return 1;
    }
    string key = encode(M);
    key.push_back('#');
    key += to_string(k);
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;

    u64 total = 0;
    map<pair<int,int>, int> cnt;
    for (auto &p : M) cnt[p]++;
    vector<pair<int,int>> vals;
    vector<int> mult;
    for (auto &q : cnt) { vals.push_back(q.first); mult.push_back(q.second); }

    int g = (int)vals.size();
    vector<int> ic(g, 0); // 每个位置分裂的个数

    function<void(int,int)> rec = [&](int gi, int used) {
        if (used > k) return;
        if (gi == g) {
            if (used == 0) return; // k>0 时不能在这里停止
            vector<pair<int,int>> M2;
            for (int i = 0; i < g; ++i) {
                int x = vals[i].first, y = vals[i].second;
                for (int t = 0; t < ic[i]; ++t) {
                    M2.push_back({x + 1, y});
                    M2.push_back({x, y + 1});
                    M2.push_back({x, y});
                }
            }
            total += solve(M2, k - used);
            return;
        }
        int m = mult[gi];
        int lo = max(0, m - 1); // 至多留 1 个做叶子
        for (int iv = lo; iv <= m; ++iv) { ic[gi] = iv; rec(gi + 1, used + iv); }
    };
    rec(0, 0);

    memo[key] = total;
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    cout << solve({{0, 0}}, N) << "\n";
    return 0;
}
