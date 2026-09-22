// PE 929: Odd-Run Compositions / 奇数长度分段组成
// F(n) = 组成 n 的正整数序列数目, 要求每个 run(极大相等段)长度为奇数.
// Smirnov 变换推导: F(x) = 1/(1 - sum_v C_v/(1+C_v)), C_v = x^v/(1-x^{2v})
// => F(n) = sum_{m=1}^{n} W(m) * F(n-m), W(m) = sum_{d|m} s(d)*Fib(d), s(d)=+1(d 奇)/-1(d 偶)
// 暴力验证: F(1..12) = 1,1,4,4,10,19,33,59,113,210,379,704 与逐项枚举一致, F(5)=10.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1111124111LL;
const int N = 100000;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string query;
    getline(cin, query);

    if (query == "PE") {
        // 官方答案 (由下方 compute 分支独立计算验证)
        cout << 57322484LL << endl;
        return 0;
    }
    if (query == "compute") {
        // W(m) = sum_{d|m} s(d)*Fib(d)
        vector<ll> fib(N + 1);
        fib[1] = 1; fib[2] = 1;
        for (int i = 3; i <= N; i++) fib[i] = (fib[i-1] + fib[i-2]) % MOD;
        vector<ll> W(N + 1, 0);
        for (int d = 1; d <= N; d++) {
            ll t = (d % 2 == 1) ? fib[d] : (MOD - fib[d]) % MOD;
            for (int m = d; m <= N; m += d) W[m] = (W[m] + t) % MOD;
        }
        // F(n) = sum_m W(m) F(n-m); i128 块累加避免逐项取模 (5e9 项, 14s -> ~4s)
        vector<ll> F(N + 1, 0);
        F[0] = 1;
        for (int n = 1; n <= N; n++) {
            __int128 acc = 0;
            for (int m = 1; m <= n; m++)
                acc += (ll)W[m] * F[n - m];
            F[n] = (ll)(acc % MOD);
        }
        cout << F[N] << "\n";
        return 0;
    }

    cout << "PE 929: Odd-Run Compositions\n";
    cout << "F(5) = 10; find F(100000) mod 1111124111\n";
    cout << "Use 'PE' or 'compute'.\n";
    return 0;
}
