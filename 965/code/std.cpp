#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 965 (简单版 / reduced): Expected Minimal Fractional Value / 最小分数期望值
//
// {x} = x 的小数部分。
// f_N(x) = min_{0 < n <= N} {n·x}，即 N 个点 {x},{2x},...,{Nx} 中最小的正小数部分。
// F(N) = E[f_N(x)]，x ~ Uniform[0,1]。
//
// 解析推导（三间隙定理 / three-gap theorem）：
//   把 {0, {x}, {2x}, ..., {Nx}} 在 [0,1) 上排序。对 x 落在两个相邻的 N 阶
//   Farey 分数 a/b < c/d（满足 bc - ad = 1，b,d <= N，b+d > N）之间时，
//   0 右侧最近的间隙长度恒为  b·x - a（它随 x 从 0 线性增大到 1/d）。
//   因此 f_N(x) = b·x - a，在该区间上是一段底长 1/(b d)、高 1/d 的三角形，
//   面积 = (1/2)·(1/(b d))·(1/d) = 1/(2 b d^2)。
//
//   枚举所有这样的 (b,d) 对（gcd(b,d)=1 且 b+d>N，1<=b,d<=N）即可：
//       F(N) = (1/2) * sum_{b,d} [gcd(b,d)==1 && b+d>N] 1/(b * d^2)
//
// 验证点：F(1)=0.5, F(2)=0.375, F(4)=0.25, F(10)≈0.1319444444444。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // long double (80-bit) + Kahan 求和，保证 13 位小数精度。
    long double sum = 0.0L;
    long double c = 0.0L; // Kahan 补偿项

    for (int b = 1; b <= N; ++b) {
        for (int d = 1; d <= N; ++d) {
            if (b + d <= N) continue;        // b+d > N 才对应相邻 Farey 分数
            if (std::gcd(b, d) != 1) continue; // bc - ad = 1 有解 ⇔ gcd(b,d)=1
            long double term = 1.0L / ((long double)b * d * d);
            // Kahan 求和
            long double y = term - c;
            long double t = sum + y;
            c = (t - sum) - y;
            sum = t;
        }
    }

    long double ans = sum * 0.5L;
    cout << fixed << setprecision(13) << (double)ans << "\n";
    return 0;
}
