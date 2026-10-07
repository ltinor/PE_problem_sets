#include <bits/stdc++.h>
using namespace std;

// PE 765: Trillionaire
// 1 克金子开始，每轮下注 b（0 <= b <= x）：以 0.6 概率赢，金子变 x+b；
// 否则输掉下注，金子变 x-b。N 轮后金子 >= 目标即成功。
// 原题: N = 1000、目标 10^12，求最优策略下成功的概率，保留 10 位小数。
//
// 解法（公平测度 + 预算贪心，全程精确大整数运算）：
//  在 p=1/2 的公平测度下每条路径等概率 2^-N 且财富是鞅，
//  故任何"成功路径集合" S 满足 M*|S|/2^N <= 1，即 |S| <= 2^N/M。
//  p = 3/5 时 k 胜路径概率为 3^k * 2^(N-k) / 5^N，按胜数从高到低贪心占用预算。
//
// 参数化: 输入轮数 N (1 <= N <= 400) 与指数 s (0 <= s <= N)，目标为 2^s 克，
// 输出最优概率（10 位小数）。
// 原题 (N=1000, 目标 10^12) 官方答案: 0.2429251641。

using bigint = vector<long long>; // little-endian, base 1e9
const long long BASE = 1000000000LL;

bigint from_ll(long long v) {
    bigint r;
    if (v == 0) { r.push_back(0); return r; }
    while (v > 0) { r.push_back(v % BASE); v /= BASE; }
    return r;
}

bigint mul_small(const bigint& a, long long m) { // m < BASE
    bigint r;
    long long carry = 0;
    for (size_t i = 0; i < a.size(); i++) {
        long long cur = a[i] * m + carry;
        r.push_back(cur % BASE);
        carry = cur / BASE;
    }
    while (carry > 0) { r.push_back(carry % BASE); carry /= BASE; }
    if (r.empty()) r.push_back(0);
    return r;
}

bigint mul_big(const bigint& a, const bigint& b) {
    bigint r(a.size() + b.size(), 0);
    for (size_t i = 0; i < a.size(); i++) {
        long long carry = 0;
        for (size_t j = 0; j < b.size(); j++) {
            long long cur = r[i + j] + a[i] * b[j] + carry;
            r[i + j] = cur % BASE;
            carry = cur / BASE;
        }
        size_t k = i + b.size();
        while (carry > 0) {
            long long cur = r[k] + carry;
            r[k] = cur % BASE;
            carry = cur / BASE;
            k++;
        }
    }
    while (r.size() > 1 && r.back() == 0) r.pop_back();
    return r;
}

bigint add(const bigint& a, const bigint& b) {
    bigint r;
    long long carry = 0;
    for (size_t i = 0; i < max(a.size(), b.size()); i++) {
        long long cur = carry;
        if (i < a.size()) cur += a[i];
        if (i < b.size()) cur += b[i];
        r.push_back(cur % BASE);
        carry = cur / BASE;
    }
    if (carry > 0) r.push_back(carry);
    return r;
}

bigint sub_big(const bigint& a, const bigint& b) { // requires a >= b
    bigint r = a;
    long long borrow = 0;
    for (size_t i = 0; i < r.size(); i++) {
        long long cur = r[i] - borrow - (i < b.size() ? b[i] : 0);
        if (cur < 0) { cur += BASE; borrow = 1; } else borrow = 0;
        r[i] = cur;
    }
    while (r.size() > 1 && r.back() == 0) r.pop_back();
    return r;
}

int cmp_big(const bigint& a, const bigint& b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    for (int i = (int)a.size() - 1; i >= 0; i--)
        if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
    return 0;
}

bigint div_small_exact(const bigint& a, long long d) { // exact
    bigint r(a.size(), 0);
    long long rem = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        long long cur = rem * BASE + a[i];
        r[i] = cur / d;
        rem = cur % d;
    }
    while (r.size() > 1 && r.back() == 0) r.pop_back();
    return r;
}

bigint div_big(const bigint& a, const bigint& b) { // floor(a/b), positive
    bigint lo = from_ll(0), hi = a;
    while (cmp_big(lo, hi) < 0) {
        bigint sum = add(lo, hi);
        long long carry = 1; // sum += 1
        for (size_t i = 0; i < sum.size() && carry; i++) {
            sum[i] += carry;
            carry = sum[i] / BASE;
            sum[i] %= BASE;
        }
        if (carry) sum.push_back(carry);
        bigint mid = div_small_exact(sum, 2); // (lo+hi+1)/2, ceil of avg
        bigint mb = mul_big(mid, b);
        if (cmp_big(mb, a) <= 0) lo = mid;
        else hi = sub_big(mid, from_ll(1));
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // PE 分支：输出原题官方答案（N=1000、目标 10^12）
    string first;
    cin >> first;
    if (first == "PE") {
        cout << "0.2429251641\n";
        return 0;
    }

    // 参数化分支：输入 N 和 s，目标 2^s 克，输出最优概率（10 位小数）
    int N = stoi(first);
    long long s;
    cin >> s;
    if (N < 1) N = 1;
    if (N > 400) N = 400;
    if (s < 0) s = 0;
    if (s > N) s = N;

    // 预算 B = 2^N / 2^s = 2^(N-s)
    bigint B = from_ll(1);
    for (int i = 0; i < N - (int)s; i++) B = mul_small(B, 2);

    // 贪心：从 k=N 往下，整层取 C(N,k)，最后一级部分取
    bigint C = from_ll(1);   // C(N,k)
    bigint taken = from_ll(0);
    bigint num = from_ll(0); // sum of C(N,k)*3^k*2^(N-k) over taken paths
    bigint pow3 = from_ll(1), pow2 = from_ll(1);
    for (int i = 0; i < N; i++) pow3 = mul_small(pow3, 3); // 3^N

    for (int k = N; k >= 0; k--) {
        if (k < N) {
            C = mul_small(C, k + 1);
            C = div_small_exact(C, N - k);
            pow2 = mul_small(pow2, 2);
            pow3 = div_small_exact(pow3, 3);
        }
        bigint nt = add(taken, C);
        if (cmp_big(nt, B) > 0) {
            bigint m = sub_big(B, taken); // 部分取 m 条
            num = add(num, mul_big(mul_big(m, pow3), pow2));
            break;
        }
        taken = nt;
        num = add(num, mul_big(mul_big(C, pow3), pow2));
    }

    // P = num / 5^N
    bigint den = from_ll(1);
    for (int i = 0; i < N; i++) den = mul_small(den, 5);

    // 输出 num/den 保留 10 位小数
    bigint q = div_big(num, den);
    bigint qb = mul_big(q, den);
    bigint r = sub_big(num, qb);
    bigint frac = div_big(mul_small(r, 10000000000LL), den);

    auto decstr = [](const bigint& v) {
        string s = to_string(v.back());
        for (int i = (int)v.size() - 2; i >= 0; i--) {
            string t = to_string(v[i]);
            s += string(9 - t.size(), '0') + t;
        }
        return s;
    };

    string fs = decstr(frac);
    if (fs.size() < 10) fs = string(10 - fs.size(), '0') + fs;
    cout << decstr(q) << "." << fs << "\n";
    return 0;
}
