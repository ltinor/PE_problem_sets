// PE198 暴力 (定义忠实, 用于小规模对拍)
// 对每个 x = p/q (既约, 0 < x < 1/100, q <= QB):
//   沿 Stern-Brocot 树走 x 的祖先对 (L, R): L < x < R, 互为 Farey 邻居.
//   不变量: L = a/b, R = c/d, bc-ad = 1, (L,R) 之间没有分母 < b+d 的分数.
//   对每个可实现的对 (取分母上限 d0 = max(b,d) < q) 检查 L + R == 2x (等距).
//   mediant 步进; 一旦 max(b,d) >= q, 后续祖先对的分母上限超出 q-1, 终止.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll QB;
    if (!(cin >> QB)) return 0;
    ll count = 0;
    for (ll q = 2; q <= QB; q++) {
        for (ll p = 1; 100 * p < q; p++) {
            if (std::gcd(p, q) != 1) continue;
            ll a = 0, b = 1, c = 1, d = 1; // L = 0/1, R = 1/1
            bool amb = false;
            while (max(b, d) < q) {
                // L + R == 2p/q  <=>  q*(a*d + c*b) == 2*p*b*d
                __int128 lhs = (__int128)q * (a * d + c * b);
                __int128 rhs = (__int128)2 * p * b * d;
                if (lhs == rhs) { amb = true; break; }
                ll ma = a + c, mb = b + d;
                if ((__int128)ma * q < (__int128)p * mb) { a = ma; b = mb; }
                else                                     { c = ma; d = mb; }
            }
            if (amb) count++;
        }
    }
    cout << count << endl;
    return 0;
}
