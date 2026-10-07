#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;

// PE 957 简单版本 —— 暴力参考实现（独立于 std.cpp 的写法）
// 用 gcd 归一化 + set 去重，而非 std.cpp 的叉积零向量判同，
// 作为交叉验证的独立实现。

struct V { i128 x, y, z; };

V cross(V a, V b) {
    return {a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x};
}

bool isZero(V a) { return a.x == 0 && a.y == 0 && a.z == 0; }

i128 igcd(i128 a, i128 b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) { i128 t = a % b; a = b; b = t; }
    return a;
}

// 归一化：除以 gcd，并规范化符号（首个非零分量为正）
V norm(V a) {
    i128 d = igcd(igcd(a.x, a.y), a.z);
    if (d == 0) return a;
    V r = {a.x / d, a.y / d, a.z / d};
    if (r.x < 0 || (r.x == 0 && (r.y < 0 || (r.y == 0 && r.z < 0)))) {
        r.x = -r.x; r.y = -r.y; r.z = -r.z;
    }
    return r;
}

struct Cmp {
    bool operator()(V a, V b) const {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    }
};

long long compute_g(int n) {
    set<V, Cmp> red = {norm({0, 0, 1}), norm({1, 0, 1}), norm({0, 1, 1})};
    set<V, Cmp> blue = {norm({2, 3, 1}), norm({3, 1, 1})};

    for (int day = 0; day < n; day++) {
        // 所有红-蓝直线（去重）
        set<V, Cmp> lines;
        for (auto& r : red)
            for (auto& b : blue) {
                V l = norm(cross(r, b));
                if (!isZero(l)) lines.insert(l);
            }

        // 所有直线对交点 -> 新蓝点
        vector<V> L(lines.begin(), lines.end());
        set<V, Cmp> newpts;
        for (size_t i = 0; i < L.size(); i++)
            for (size_t j = i + 1; j < L.size(); j++) {
                V p = norm(cross(L[i], L[j]));
                if (isZero(p)) continue;
                if (p.z == 0) continue;                 // 无穷远点（平行线交点）
                if (red.count(p) || blue.count(p)) continue; // 红点或已有蓝点
                newpts.insert(p);
            }

        for (auto& p : newpts) blue.insert(p);
    }
    return (long long)blue.size();
}

void print_i128(i128 v) {
    if (v == 0) { cout << "0"; return; }
    if (v < 0) { cout << "-"; v = -v; }
    string s;
    while (v) { s.push_back(char('0' + v % 10)); v /= 10; }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string line;
    if (!getline(cin, line)) return 0;

    if (line == "verify") {
        for (int n = 1; n <= 4; n++) {
            cout << "g(" << n << ") = " << compute_g(n) << "\n";
        }
        return 0;
    }

    stringstream ss(line);
    int n;
    if (!(ss >> n) || n < 1 || n > 4) {
        cout << "0\n";
        return 0;
    }
    cout << compute_g(n) << "\n";
    return 0;
}
