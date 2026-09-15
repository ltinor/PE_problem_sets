#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 955: Finding Triangles / 寻找三角形数  (简单版本 / simple version)
//
// 原题：求数列中第 70 个三角形数的下标 n（数据量极大，需要 Pell 方程等高阶方法）。
// 简单版本：缩小数据范围，给定 k（第几个三角形数），直接模拟求出其下标 n。
//
// 数列 (a_n)_{n>=0}，a_0 = 3：
//   - 若 a_n 是三角形数，则 a_{n+1} = a_n + 1；
//   - 否则 a_{n+1} = 2*a_n - a_{n-1} + 1。
// 三角形数：形如 m(m+1)/2。
//
// 算法（直接模拟，O(下标)）：
//   维护当前值 a 与相邻项差 d = a_n - a_{n-1}。
//   - 若 a 是三角形数，下一项差重置为 1；
//   - 否则差加 1（因为 a_{n+1} - a_n = a_n - a_{n-1} + 1）。
//   每走一步检查新值是否为三角形数，计数。
//
// 验证点（来自题面）：第 10 个三角形数是 a_2964 = 1439056。
//
// 缩数据范围：1 <= k <= 20（第 20 个下标约 1.66e7，直接模拟毫秒级完成）。

// 判断 x 是否为三角形数，若是返回 m（使 x = m(m+1)/2），否则返回 -1。
ll is_triangle(i128 x) {
    // m(m+1)/2 = x  =>  (2m+1)^2 = 8x+1
    i128 d = 8 * x + 1;
    i128 s = (i128)sqrtl((long double)d);
    while (s * s < d) s++;
    while (s * s > d) s--;
    if (s * s == d && (s - 1) % 2 == 0) {
        return (ll)((s - 1) / 2);
    }
    return -1;
}

// 返回第 k 个三角形数在数列中的下标 n 及其值 a_n。
pair<ll,ll> kth_triangle_index(ll k) {
    if (k <= 1) return {0, 3};          // a_0 = 3 = T_2 是第 1 个
    ll a = 3;            // 当前值
    ll d = 1;            // 当前相邻项差
    ll idx = 0;          // 当前下标
    ll tri_count = 1;    // 已发现的三角形数个数
    while (tri_count < k) {
        if (is_triangle(a) >= 0) d = 1;
        else d++;
        a += d;
        idx++;
        if (is_triangle(a) >= 0) tri_count++;
    }
    return {idx, a};
}

void verify() {
    cout << "PE 955: Finding Triangles / 寻找三角形数  (简单版本)\n\n";
    cout << "=== 验证点 ===\n";
    cout << "题面给出：第 10 个三角形数是 a_2964 = 1439056\n\n";

    cout << "前若干三角形数（#: a_下标 = 值 = T_m）：\n";
    for (ll k = 1; k <= 15; k++) {
        auto [idx, val] = kth_triangle_index(k);
        ll m = is_triangle(val);
        cout << "  #" << setw(2) << k << ": a_" << idx << " = " << val
             << " = T_" << m << "\n";
    }
    cout << "\n";

    auto [idx10, val10] = kth_triangle_index(10);
    cout << "=== 验证结果 ===\n";
    cout << "第 10 个三角形数下标 = " << idx10 << "（期望 2964）"
         << (idx10 == 2964 ? "  ✓" : "  ✗") << "\n";
    cout << "第 10 个三角形数值   = " << val10 << "（期望 1439056）"
         << (val10 == 1439056 ? "  ✓" : "  ✗") << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string line;
    if (!getline(cin, line)) return 0;

    if (line == "verify") { verify(); return 0; }

    // 参数化：读入 k（第几个三角形数），输出其下标 n。
    ll k;
    stringstream ss(line);
    if (!(ss >> k)) {
        cout << "用法: 输入整数 k (1<=k<=20)，输出第 k 个三角形数的下标 n。\n";
        cout << "或输入 'verify' 运行验证。\n";
        return 0;
    }
    auto [idx, val] = kth_triangle_index(k);
    cout << idx << "\n";   // 输出下标 n
    return 0;
}
