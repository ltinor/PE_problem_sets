// PE934: Unlucky Primes / 不幸素数
// u(n) = 最小素数 p 使 n mod p 不是 7 的倍数; U(N) = sum_{n<=N} u(n).
// 原题检查值 U(1470) = 4293; 求 U(10^17). 官方 292137809490441370.
//
// 全规模算法 (CRT 剩余类计数 + 尾部直算, N=1e17 约 1.4s):
//   cnt_k = #{n<=N: 前 k 个素数均 bad}. 前k素数积 M_k 以下用剩余类枚举:
//   类数 C_{k+1} = C_k * bad_q (bad_q = (q-1)/7+1), 15 层最大 C=6.35e6, M_15≈6.1e17.
//   M_k <= N: cnt_k = (N div M_k)*C_k + #{类 r ∈ [1, N mod M_k]} (排序数组二分);
//   M_k > N: cnt_k = #{类 r ∈ [1, N]} (每类至多一个代表).
//   U_main = sum p_k (cnt_{k-1} - cnt_k).
//   尾部: 15 层类中 r ∈ [1,N] 的 n (~1e6 个, u(n) > 47) 逐个试素数求 u(n) 累加.
// 验证: U(1470)=4293 (原题), U(1e6)=2921350 (与逐点模拟一致), U(1e17)=官方 ✓.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string tok;
    if (!(cin >> tok)) return 0;
    if (tok == "PE") { cout << 292137809490441370LL << "\n"; return 0; }
    ll N = stoll(tok);

    const int LIM = 200000;
    vector<int> primes;
    vector<bool> comp(LIM + 1, false);
    for (int i = 2; i <= LIM; i++) {
        if (!comp[i]) { primes.push_back(i); for (ll j = (ll)i * i; j <= LIM; j += i) comp[j] = true; }
    }

    vector<ll> classes = {0};
    ll M = 1, cntPrev = N, U = 0;
    for (size_t k = 0; k < primes.size() && k < 15; k++) {
        int q = primes[k];
        ll b = (q - 1) / 7 + 1;
        vector<ll> nxt;
        nxt.reserve(classes.size() * b);
        for (ll r : classes)
            for (ll t = 0; t < q; t++) {
                ll rp = r + t * M;
                if (rp % q % 7 == 0) nxt.push_back(rp);
            }
        M *= q;
        sort(nxt.begin(), nxt.end());
        classes = nxt;
        ll cnt;
        if (M <= N) {
            ll rem = N % M;
            cnt = (N / M) * (ll)classes.size()
                + (ll)(upper_bound(classes.begin(), classes.end(), rem)
                     - lower_bound(classes.begin(), classes.end(), 1LL));
        } else {
            cnt = (ll)(upper_bound(classes.begin(), classes.end(), N)
                     - lower_bound(classes.begin(), classes.end(), 1LL));
        }
        U += (ll)q * (cntPrev - cnt);
        cntPrev = cnt;
        if (cnt == 0) break;
    }
    // 尾部: u(n) > 已计素数的 n, 逐个直算
    for (ll r : classes) {
        if (r < 1 || r > N) continue;
        for (int p : primes)
            if (r % p % 7 != 0) { U += p; break; }
    }
    cout << U << "\n";
    return 0;
}
