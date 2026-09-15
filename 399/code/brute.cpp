#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost::multiprecision;

// PE 399 暴力（独立实现）：逐个生成斐波那契数，用试除法判无平方因子，
// 不依赖 Wall 猜想。用于 check.sh 与 std.cpp 对拍（小 K）。

bool squarefree(const cpp_int& n) {
    if (n == 0) return false;
    if (n == 1) return true;
    for (cpp_int i = 2; i * i <= n; i++) {
        if (n % (i * i) == 0) return false;
    }
    return true;
}

// 与 std.cpp 相同的输出格式化
string format(const cpp_int& x) {
    string s = x.convert_to<string>();
    string last16 = s;
    if ((int)last16.size() > 16) last16 = last16.substr(last16.size() - 16);
    else last16 = string(16 - last16.size(), '0') + last16;
    int E = (int)s.size() - 1;
    int d1 = s[0] - '0';
    int d2 = (s.size() >= 2) ? s[1] - '0' : 0;
    int d3 = (s.size() >= 3) ? s[2] - '0' : 0;
    if (d3 >= 5) {
        d2++;
        if (d2 == 10) { d2 = 0; d1++; if (d1 == 10) { d1 = 1; E++; } }
    }
    ostringstream oss;
    oss << last16 << "," << d1 << "." << d2 << "e" << E;
    return oss.str();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long K;
    if (!(cin >> K)) return 0;
    if (K <= 0) return 0;

    cpp_int ans = 0;
    if (K == 1 || K == 2) {
        // F_1 = F_2 = 1，均为无平方因子
        ans = 1;
    } else {
        long long cnt = 2;      // 已计入 F_1、F_2 两个 1
        cpp_int fa = 1, fb = 1; // F_1, F_2
        long long n = 2;
        while (cnt < K) {
            cpp_int fc = fa + fb; // F_{n+1}
            n++;
            if (squarefree(fc)) {
                cnt++;
                if (cnt == K) { ans = fc; break; }
            }
            fa = fb;
            fb = fc;
        }
    }

    cout << format(ans) << "\n";
    return 0;
}
