#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // PE 分支：输出原题官方答案（两个 3 位数乘积的最大回文）
    string first;
    cin >> first;
    if (first == "PE") {
        cout << 906609 << "\n";
        return 0;
    }

    // 参数化分支：给定因子的位数 n (2 <= n <= 7)，
    // 求能表示为两个 n 位数乘积的最大回文数（2n 位）。
    int n = stoi(first);
    if (n < 2) n = 2;
    if (n > 7) n = 7;

    long long lo = 1, hi = 9;
    for (int i = 1; i < n; i++) { lo *= 10; hi = hi * 10 + 9; }

    // 按从大到小枚举 2n 位回文数（由前半 h 镜像生成）
    for (long long h = hi; h >= lo; h--) {
        long long pal = h, t = h;
        for (int i = 0; i < n; i++) { pal = pal * 10 + t % 10; t /= 10; }

        // 因子 d 须满足 lo <= d <= hi 且 lo <= pal/d <= hi
        long long dmin = (pal + hi - 1) / hi; if (dmin < lo) dmin = lo;
        long long dmax = pal / lo;            if (dmax > hi) dmax = hi;

        for (long long d = dmax; d >= dmin; d--) {
            if (pal % d == 0) {
                cout << pal << "\n";
                return 0;
            }
        }
    }

    cout << -1 << "\n";
    return 0;
}
