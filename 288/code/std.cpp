// PE288: 巨大的阶乘 NF(p,q) mod p^e
// N(p,q) = sum_{n=0..q} T_n * p^n (T_n = S_n mod p, S 递推), NF(p,q) = v_p(N(p,q)!)
// Legendre: NF = sum_{j>=1} floor(N/p^j). N 为 base-p 数, floor(N/p^j) mod p^e
//   = 数位窗口 sum_{d=0..e-1} T[j+d] * p^d => 滑动窗口 O(q).
//   窗口递推: w_{j+1} = (w_j - T[j])/p + p^(e-1)*T[j+e] (差值必为 p 的倍数, 精确整除).
// 验证: NF(3,10000) mod 3^20 = 624955285 (原题检查值);
//       NF(61,1e7)  mod 61^10 = 605857431263981935 (PE 官方答案);
//       (5,100,3)/(7,1000,5) 与大整数直接 Legendre 对拍一致.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

int main() {
    ll p, q, e;
    if (!(cin >> p >> q >> e)) return 0;
    ll MOD = 1;
    for (ll i = 0; i < e; i++) MOD *= p;

    const ll M = 50515093;
    vector<ll> T(q + e + 1, 0);
    ll S = 290797;
    for (ll n = 0; n <= q; n++) { T[n] = S % p; S = (__int128)S * S % M; }

    // j = 1 的窗口
    i128 w = 0, pe1 = 1;
    ll pw = 1;
    for (ll d = 0; d < e; d++) { w += (i128)T[1 + d] * pw; pw *= p; }
    for (ll i = 0; i < e - 1; i++) pe1 *= p;

    i128 tot = w % MOD;
    for (ll j = 1; j < q; j++) {
        i128 diff = w - T[j];                 // 必为 p 的倍数
        w = diff / p + pe1 * T[j + e];
        tot = (tot + w) % MOD;
    }
    cout << (ll)tot << "\n";
    return 0;
}
