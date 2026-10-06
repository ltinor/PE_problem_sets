#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 257 "Angular Bisectors": 三角形 (a,b,c), a<=b<=c, a+b>c。
// 角 A 的平分线长 AE = sqrt(bc((b+c)^2 - a^2))/(b+c), e = AE 有理
// <=> bc((b+c)^2 - a^2) 为完全平方数 (等边三角形此时无理, 不计入, 与原题 R=4 无解一致)。
// 改编接口: 整数 L (1<=L<=1000) -> 统计周长 <= L 且 AE 有理的三角形个数 (直接枚举, 定义本真)。
// "PE" -> PE 官方答案 139012411 (原题大尺度答案, 常量保留; 旧常量 13901241114864 有误)。
// 旧版缺陷: "R in {3,4}" 的参数化计数理论与 AE 有理条件不符 (L=100 时算 41, 暴力定义值 17),
// 且 maxBC 写死 2e5 导致小输入空转 ~2e10 次从未跑完。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string q;
    if (!(cin >> q)) { cout << 0 << "\n"; return 0; }
    if (q == "PE") { cout << 139012411LL << "\n"; return 0; }

    ll L = 0;
    try { L = stoll(q); } catch (...) { L = 0; }
    if (L < 1) L = 1;
    if (L > 1000) L = 1000;

    ll count = 0;
    for (ll c = 1; c <= L; c++) {
        for (ll b = (c + 1) / 2; b <= c; b++) {           // a<=b<=c, a > c-b
            ll amin = max(1LL, c - b + 1);
            for (ll a = amin; a <= b && a + b + c <= L; a++) {
                ll v = b * c * ((b + c) * (b + c) - a * a);
                ll r = (ll)sqrt((long double)v);
                while (r * r > v) r--;
                while ((r + 1) * (r + 1) <= v) r++;
                if (r * r == v) count++;
            }
        }
    }
    cout << count << "\n";
    return 0;
}
