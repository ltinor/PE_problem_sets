#include <bits/stdc++.h>
using namespace std;

// PE 762 朴素暴力（对拍用）：
// 状态 = 当前占据方格的「有序列表」，每个方格编码为 x*4+y。
// 用 std::set 去重，与 std.cpp 的 bitset 编码相互独立，仅用于小 N 对拍。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    set<vector<int>> cur, nxt;
    cur.insert({0}); // 方格 (0,0)

    for (int step = 0; step < N; step++) {
        nxt.clear();
        for (const auto& st : cur) {
            for (int cell : st) {
                int x = cell / 4, y = cell % 4;
                int b1 = (x + 1) * 4 + y;
                int b2 = (x + 1) * 4 + ((y + 1) & 3);
                if (binary_search(st.begin(), st.end(), b1) ||
                    binary_search(st.begin(), st.end(), b2))
                    continue;
                vector<int> ns;
                ns.reserve(st.size() + 1);
                for (int c : st)
                    if (c != cell) ns.push_back(c);
                ns.push_back(b1);
                ns.push_back(b2);
                sort(ns.begin(), ns.end());
                nxt.insert(ns);
            }
        }
        cur.swap(nxt);
    }

    cout << cur.size() << "\n";
    return 0;
}
