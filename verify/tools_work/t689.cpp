// 689 截断版精确计数: p_D(a) = #{S ⊆ {2..D}: sum_{i∈S} 1/i² > a} / 2^(D-1)
// MITM + i128 精确 (标度 L=lcm(2..D), 值 = L²/i²; L²(D<=42) ~ 5e34 < i128)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

int main(int argc, char** argv) {
    // args: D a(十进制字符串)
    ll D = atoll(argv[1]);
    string astr = argv[2];
    // L = lcm(2..D)
    ll L = 1;
    for (ll i = 2; i <= D; i++) {
        ll g = __gcd(L, i); L = L / g * i;
    }
    // 元素 i=2..D: 权重 (L/i)^2
    int n = (int)D;
    vector<i128> w(n);
    for (int i = 0; i < n; i++) w[i] = (i128)(L / (i + 1)) * (L / (i + 1));
    // 阈值: a = An/10^k -> floor(a * L^2) (i128)
    size_t dot = astr.find('.');
    ll An; int k;
    if (dot == string::npos) { An = stoll(astr); k = 0; }
    else { string ip = astr.substr(0, dot), fp = astr.substr(dot + 1); k = (int)fp.size();
           string all = ip + fp; An = stoll(all); }
    i128 L2 = (i128)L * L;
    i128 thr = (i128)An * L2 / (ll)1; // An * L^2
    { i128 den = 1; for (int i = 0; i < k; i++) den *= 10; thr = (i128)An * L2 / den; }
    // MITM
    int n1 = n / 2, n2 = n - n1;
    vector<i128> A, B;
    A.reserve(1 << n1); B.reserve(1 << n2);
    vector<i128> sums = {0};
    for (int i = 0; i < n1; i++) {
        size_t sz = sums.size();
        for (size_t j = 0; j < sz; j++) sums.push_back(sums[j] + w[i]);
    }
    A = sums;
    sums = {0};
    for (int i = 0; i < n2; i++) {
        size_t sz = sums.size();
        for (size_t j = 0; j < sz; j++) sums.push_back(sums[j] + w[n1 + i]);
    }
    B = sums;
    sort(B.begin(), B.end());
    // count pairs (a1, b): a1 + b > thr  <=>  b > thr - a1
    ll cnt = 0;
    for (i128 a1 : A) {
        i128 need = thr - a1;             // count B > need
        cnt += (ll)(B.end() - upper_bound(B.begin(), B.end(), need));
    }
    // probability = cnt / 2^n ; 输出 12 位小数 (分母是 2 的幂, 十进制有限)
    // 打印: cnt * 10^12 / 2^n 整数部分 + 处理
    printf("D=%lld a=%s cnt=%lld total=%lld p=%.12f\n", D, astr.c_str(), cnt, 1LL << n,
           (double)cnt / (double)(1LL << n));
    return 0;
}
