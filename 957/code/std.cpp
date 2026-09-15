#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 957: Point Genesis / 点·创世纪  (简单版本 / simple version)
//
// 原题：求 g(16)（迭代 16 天，点数呈超指数增长，需要刻画无穷远的入射结构）。
// 简单版本：用精确的齐次坐标几何模拟，计算小 n 的 g(n)。
//
// 问题：平面上初始有 3 个红点、2 个蓝点，其余为白点。每一天，
//   1) 构造所有经过一个红点与一个蓝点的直线；
//   2) 任意两条这样的不同直线相交处的白点变为蓝点。
// g(n) = n 天后的最大蓝点数（取一般位置时的计数）。
//
// 算法（精确几何模拟，齐次坐标）：
//   用齐次坐标 (x:y:z) 表示点与直线（ax+by+cz=0）。
//   - 过两点 P,Q 的直线 = P × Q（叉积）；
//   - 两直线 ℓ1,ℓ2 的交点 = ℓ1 × ℓ2；
//   - 两点相同  <=> 叉积为零向量；z=0 表示无穷远点（平行线交点，不计）。
//   全整数运算，无浮点误差。选一般位置初始点保证达到最大计数。
//
// 验证点：g(1) = 8，g(2) = 28。
//
// 缩数据范围：1 <= n <= 4（g(4)=1643；点数按超指数增长，更大 n 需高阶方法）。

struct V { i128 x, y, z; };

V cross(V a, V b) {
    return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
}
bool isZero(V a) { return a.x == 0 && a.y == 0 && a.z == 0; }
// 两齐次坐标点/直线是否相同（成比例 <=> 叉积为零）
bool same(V a, V b) { return isZero(cross(a, b)); }

vector<ll> compute_g(int max_days) {
    // 初始 3 红 2 蓝（一般位置：无三点共线）
    vector<V> red = {{0,0,1},{1,0,1},{0,1,1}};
    vector<V> blue = {{2,3,1},{3,1,1}};
    vector<ll> g;

    for (int day = 1; day <= max_days; day++) {
        // 所有红-蓝直线（去重）
        vector<V> lines;
        for (auto &r : red) for (auto &b : blue) {
            V l = cross(r, b);
            if (isZero(l)) continue;
            bool dup = false;
            for (auto &t : lines) if (same(t, l)) { dup = true; break; }
            if (!dup) lines.push_back(l);
        }

        // 所有直线对的交点 -> 新蓝点
        vector<V> newpts;
        for (size_t i = 0; i < lines.size(); i++) {
            for (size_t j = i + 1; j < lines.size(); j++) {
                V p = cross(lines[i], lines[j]);
                if (isZero(p)) continue;
                if (p.z == 0) continue;      // 无穷远点（平行线），非平面白点
                bool skip = false;
                for (auto &r : red) if (same(r, p)) { skip = true; break; }
                if (skip) continue;
                for (auto &b : blue) if (same(b, p)) { skip = true; break; }
                if (skip) continue;
                bool innew = false;
                for (auto &q : newpts) if (same(q, p)) { innew = true; break; }
                if (!innew) newpts.push_back(p);
            }
        }
        for (auto &p : newpts) blue.push_back(p);
        g.push_back((ll)blue.size());
    }
    return g;
}

void verify() {
    cout << "PE 957: Point Genesis / 点·创世纪  (简单版本)\n\n";
    auto g = compute_g(4);
    cout << "=== 验证点 ===\n";
    cout << "g(1) = " << g[0] << "（期望 8）" << (g[0] == 8 ? "  ✓" : "  ✗") << "\n";
    cout << "g(2) = " << g[1] << "（期望 28）" << (g[1] == 28 ? "  ✓" : "  ✗") << "\n\n";
    cout << "=== 继续迭代（额外结果） ===\n";
    for (size_t i = 2; i < g.size(); i++) {
        cout << "g(" << (i + 1) << ") = " << g[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string line;
    if (!getline(cin, line)) return 0;

    if (line == "verify") { verify(); return 0; }

    int n;
    stringstream ss(line);
    if (!(ss >> n) || n < 1 || n > 4) {
        cout << "用法: 输入整数 n (1<=n<=4)，输出 g(n)。\n";
        cout << "或输入 'verify' 运行验证。\n";
        return 0;
    }
    auto g = compute_g(n);
    cout << g[n - 1] << "\n";
    return 0;
}
