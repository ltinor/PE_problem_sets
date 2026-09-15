#include <bits/stdc++.h>
using namespace std;

// 独立验证实现：直接枚举 N 阶 Farey 序列，对每对相邻分数 (a/b, c/d)
// 累加三角形面积 1/(2 b d^2)。与 std.cpp 的 (b,d) 双循环公式互为校验。
// 仅用于 check.sh 的小数据对拍（N 较小）。
int main() {
    int N;
    cin >> N;

    // 收集 N 阶 Farey 分数 a/b (0 <= a <= b <= N, gcd(a,b)=1)，含 0/1 与 1/1。
    struct Frac { int a, b; };
    vector<Frac> fr;
    fr.push_back({0, 1});
    for (int b = 1; b <= N; ++b) {
        for (int a = 1; a <= b; ++a) {
            if (std::gcd(a, b) == 1) fr.push_back({a, b});
        }
    }
    sort(fr.begin(), fr.end(), [](const Frac &x, const Frac &y) {
        return (long long)x.a * y.b < (long long)y.a * x.b;
    });

    double sum = 0.0;
    for (size_t i = 0; i + 1 < fr.size(); ++i) {
        const Frac &L = fr[i];
        const Frac &R = fr[i + 1];
        sum += 1.0 / (2.0 * (double)L.b * R.b * R.b);
    }

    cout << fixed << setprecision(13) << sum << "\n";
    return 0;
}
