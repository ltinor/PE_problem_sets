#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 937（简单 / OJ 缩数据版）：Equiproduct Partition / 等积划分
//
// 原题：求 G(10^8) mod (10^9+7)。本目录为缩数据版：读入 n，输出 G(n) mod MOD。
//
// 背景：环 Z[√-2]（UFD），T = {a+b√-2 : a>0 或 (a=0 且 b>0)}，即取模单位 ±1 的
// 代表元集。把 T 划分为 A ∪ B（1∈A、A∩B=∅、A∪B=T），并要求对任意 z∈T 满足
// p(A,z)=p(B,z)，其中 p(S,z) 是「从 S 中选两个不同元素，乘积为 ±z」的方案数。
// 该等积条件唯一确定 A、B。
//
// 关键结论（可用生成函数 / 约数和推导）：
//   记 χ(x) = (-1)^(Σ_i popcount(e_i))，x = Π π_i^{e_i} 为 Z[√-2] 中的素分解，
//   popcount 为二进制 1 的个数。则 A = {x : χ(x)=+1}（即各素因子指数二进制
//   1 的个数之和为偶数），B = {x : χ(x)=-1}。这恰好就是「约数和 S(z)=Σ_{x|z}χ(x)
//   在 z 非平方时为 0、平方时等于 χ(√z)」的唯一解：对单个素数 π 的幂 π^e，
//   b_e = χ(π^e) 满足 b_0=1、b_{2e}=b_e、b_{2e+1}=-b_e，即 Thue-Morse 序列
//   b_e = (-1)^popcount(e)。
//
// 整数 n 在 Z[√-2] 中的素分解：
//   - 2 分歧：2 = -θ²，对应一个素元 θ，指数为 2·v₂(n)，popcount(2v₂)=popcount(v₂)；
//   - p ≡ 1,3 (mod 8) 分裂：p = π·π̄，两个不同素元，各贡献 popcount(v_p(n))，
//     合计 2·popcount(v_p(n)) 恒为偶数，不影响奇偶性；
//   - p ≡ 5,7 (mod 8) 惰性：p 本身为素元，贡献 popcount(v_p(n))。
// 故 n ∈ A 当且仅当  popcount(v₂(n)) + Σ_{p≡5,7 (mod 8)} popcount(v_p(n)) 为偶数。
//
// 对 n!，用勒让德公式 v_p(n!) = Σ_{j≥1} ⌊n/p^j⌋，并增量维护：n! = (n-1)!·n。
//
// 验证点：G(4)=25，G(7)=745，G(100) ≡ 709772949 (mod 10^9+7)。

const ll MOD = 1000000007LL;

inline int pc(ll x) { return __builtin_popcountll(x) & 1; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    if (!(cin >> n)) return 0;
    if (n < 1) { cout << 0 << "\n"; return 0; }

    // 最小素因子筛（SPF），用于快速分解 1..n 中的每个数。
    vector<int> spf(n + 1, 0);
    for (int i = 2; i <= (int)n; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            if ((ll)i * i <= n)
                for (ll j = (ll)i * i; j <= n; j += i)
                    if (spf[j] == 0) spf[j] = i;
        }
    }

    // expo[p] = v_p(k!)（只关心 p=2 与 p≡5,7 (mod 8) 的素数）。
    vector<ll> expo(n + 1, 0);

    int par = 0;   // popcount(v2(k!)) XOR Σ popcount(vp(k!)) 的奇偶性（k!∈A 当且仅当 par==0）
    ll fact = 1;   // k! mod MOD
    ll ans = 0;

    for (ll k = 1; k <= n; k++) {
        fact = fact * (k % MOD) % MOD;

        int x = (int)k;
        while (x > 1) {
            int p = spf[x];
            int v = 0;
            while (x % p == 0) { x /= p; v++; }
            if (p == 2 || p % 8 == 5 || p % 8 == 7) {
                ll old = expo[p];
                ll nw = old + v;
                par ^= pc(old) ^ pc(nw);
                expo[p] = nw;
            }
        }

        if (par == 0) ans = (ans + fact) % MOD;
    }

    cout << ans << "\n";
    return 0;
}
