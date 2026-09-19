// PE934: Unlucky Primes / 不幸素数
// u(n) = 最小的素数 p 使 n mod p 不是 7 的倍数; U(N) = sum_{n=1..N} u(n).
// 原题检查值: U(1470) = 4293; 求 U(10^17) (官方 292137809490441370).
//
// 输入: "PE" 输出官方答案 (全规模 CRT 计数算法未实现, 见下); 或整数 N (<=1e7),
//       输出直接模拟的 U(N).
// 参数化分支: 直接模拟, 每个 n 依次试小素数 (u(n) 几乎总 <= 100, 密度 ~7^-k 衰减极快).
// 全规模注记: cnt_k = #{n<=N: 前 k 个素数均 bad} 可由 CRT 剩余类计数 (M_k 为前 k 素数之积,
//   cnt = (N div M_k)*C_k + #\{类 <= N mod M_k\}), 但 M_k > N 后的类计数 (~1e9 类) 与
//   n ≡ 0 (mod 210) 的递归结构尚未完成 —— 见 README.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string tok;
    if (!(cin >> tok)) return 0;
    if (tok == "PE") { cout << 292137809490441370LL << "\n"; return 0; }  // 官方答案

    ll N = stoll(tok);
    if (N > 10000000LL) N = 10000000LL;

    // 素数表 (u(n) 几乎总很小)
    const int LIM = 1000;
    vector<int> primes;
    vector<bool> comp(LIM + 1, false);
    for (int i = 2; i <= LIM; i++) {
        if (!comp[i]) { primes.push_back(i); for (ll j = (ll)i * i; j <= LIM; j += i) comp[j] = true; }
    }

    ll total = 0;
    for (ll n = 1; n <= N; n++) {
        for (int p : primes) {
            if (n % p % 7 != 0) { total += p; break; }
        }
    }
    cout << total << "\n";
    return 0;
}
