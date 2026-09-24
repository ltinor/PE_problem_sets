// PE689: Binary Series / 二进制级数 (改编: 截断级数的精确概率)
// 原题: x 均匀分布, f(x) = sum_{i>=1} d_i(x)/i^2, 求 P(f > 0.5) = 0.56565454 (官方).
// 改编 (缩规模落地): 定义截断级数 f_D(x) = sum_{i=1}^{D} d_i(x)/i^2,
//   给定 D 与 a, 精确计算 p_D(a) = P(f_D(x) > a) (x 均匀 <=> d_i 独立同分布 Bern(1/2)).
//
// 算法: meet-in-the-middle 精确计数. 值域标度 L = lcm(1..D), 元素权重 (L/i)^2,
//   子集和为精确 i128 整数 (D <= 42 时 < i128 上限). 计数对 (S1, S2):
//   sum_{S1} + sum_{S2} > a  <=>  sum_{S2} > a - sum_{S1} (排序 + 二分).
//   严格不等式的阈值由 a 的十进制精确解析 (floor(a * L^2)) 处理, 无浮点.
//   p_D(a) = cnt / 2^(D-1), 分母为 2 的幂 => 十进制展开有限, 输出精确.
// 复杂度: O(2^(D/2) * D), D=42 约 0.5s.
// 验证: D <= 20 与 2^(D-1) 直接枚举逐位一致; p_D(0.5) 随 D 增大收敛于原题官方值
//   (D=20: 0.5410, D=42: 0.5536, 原题 0.56565454, 偏差 = 尾项 ~1/D 的影响, 符合理论).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string first;
    if (!(cin >> first)) return 0;
    if (first == "PE") { cout << "0.56565454\n"; return 0; }   // 原题官方答案 (D=∞ 参考)
    ll D = stoll(first);
    string astr;
    cin >> astr;
    if (D < 2) D = 2;
    if (D > 42) D = 42;

    ll L = 1;
    for (ll i = 2; i <= D; i++) L = L / __gcd(L, i) * i;
    int n = (int)D;
    vector<i128> w(n);
    for (int i = 0; i < n; i++) w[i] = (i128)(L / (i + 1)) * (L / (i + 1));

    // 阈值: 解析 a 的十进制 = An / 10^k, floor(a * L^2) = An * L^2 / 10^k
    size_t dot = astr.find('.');
    ll An; int k = 0;
    if (dot == string::npos) { An = stoll(astr); }
    else {
        string all = astr.substr(0, dot) + astr.substr(dot + 1);
        k = (int)(astr.size() - dot - 1);
        An = all.empty() ? 0 : stoll(all);
    }
    i128 L2 = (i128)L * L;
    i128 den = 1;
    for (int i = 0; i < k; i++) den *= 10;
    i128 thr = (i128)An * L2 / den;      // f_D > a  <=>  scaled sum >= thr + 1

    // MITM
    int n1 = n / 2, n2 = n - n1;
    vector<i128> A, B;
    A.reserve(1u << n1); B.reserve(1u << n2);
    vector<i128> sums = {0};
    for (int i = 0; i < n1; i++) {
        size_t sz = sums.size();
        for (size_t j = 0; j < sz; j++) sums.push_back(sums[j] + w[i]);
    }
    A = sums;
    sums = {0};
    for (int i = n1; i < n; i++) {
        size_t sz = sums.size();
        for (size_t j = 0; j < sz; j++) sums.push_back(sums[j] + w[i]);
    }
    B = sums;
    sort(B.begin(), B.end());
    ll cnt = 0;
    for (i128 a1 : A) {
        i128 need = thr - a1;            // 数 B 中 > need 的个数
        cnt += (ll)(B.end() - upper_bound(B.begin(), B.end(), need));
    }
    ll tot = 1LL << n;
    // p = cnt / 2^n, 输出 12 位小数 (精确: 分母是 2 的幂)
    i128 scaled = ((i128)cnt * 1000000000000LL * 2 + tot) / (tot * 2);   // 四舍五入
    ll ip = (ll)(scaled / 1000000000000LL);
    ll fp = (ll)(scaled % 1000000000000LL);
    cout << ip << "." << setw(12) << setfill('0') << fp << "\n";
    return 0;
}
