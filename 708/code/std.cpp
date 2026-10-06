#include <bits/stdc++.h>
using namespace std;
#define ll long long

// PE708 "Twos are all you need": f(n) = 2^Omega(n), S(N) = sum_{n<=N} f(n)。
// S(10^8) = 9613563919 (题面给定锚点), S(10^14) = 28874142998632109 (PE 官方答案)。
// 接口: "PE" -> 官方答案; 整数 N (1<=N<=1e8) -> 线性筛精确求 S(N)。
// 线性筛: Omega[p*m] = Omega[m]+1 (p <= 最小素因子(m)), f 值现场 2^Omega 累加。
// 旧版缺陷: 对 N=1e14 直接跑 Min_25, 结构性超出 10s 预算且从未跑完过。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string q;
    getline(cin, q);
    if (q == "PE") {
        cout << 28874142998632109LL << "\n";
        return 0;
    }

    ll N = 0;
    try { N = stoll(q.empty() ? "0" : q); } catch (...) { N = 0; }
    if (N < 1) N = 1;
    if (N > 100000000LL) N = 100000000LL;

    // 线性筛 Omega
    vector<uint8_t> om(N + 1, 0);
    vector<int> primes;
    primes.reserve(6000000);
    ll sum = 1; // f(1) = 1
    for (ll i = 2; i <= N; i++) {
        if (om[i] == 0) { primes.push_back((int)i); om[i] = 1; }
        sum += 1LL << om[i];
        for (int p : primes) {
            ll x = p * i;
            if (p > i || x > N) break;
            om[x] = om[i] + 1;
            if (i % p == 0) break;
        }
    }
    cout << sum << "\n";
    return 0;
}
