// PE198 definition-faithful brute (independent check)
// 对每个 x = p/q (既约, 0 < x < 1/100, q <= QB):
//   维护当前分母上限下 x 的两个最佳逼近 L < x < R (Stern-Brocot 祖先对, 互为 Farey 邻居)
//   不变量: L = a/b, R = c/d, bc-ad = 1, 且 (L,R) 区间内没有分母 < b+d 的分数
//   对每个实现的 (L,R) 对 (max(b,d) <= d0 < b+d, 且 d0 <= q-1) 检查 L + R == 2x
//   mediant 步进; 一旦 max(b,d) >= q 则后续对也不可实现, 终止
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char** argv) {
    ll QB = (argc > 1) ? atoll(argv[1]) : 2000;
    ll count = 0;
    for (ll q = 2; q <= QB; q++) {
        for (ll p = 1; 100 * p < q; p++) {
            if (std::gcd(p, q) != 1) continue;
            // walk Stern-Brocot ancestors of p/q
            ll a = 0, b = 1, c = 1, d = 1; // L = 0/1, R = 1/1
            bool amb = false;
            while (max(b, d) < q) {
                // L + R == 2p/q ?
                // (a*d + c*b) / (b*d) == 2p/q  <=>  q*(a*d + c*b) == 2*p*b*d
                __int128 lhs = ( __int128 )q * (a * d + c * b);
                __int128 rhs = ( __int128 )2 * p * b * d;
                if (lhs == rhs) { amb = true; break; }
                // mediant m = (a+c)/(b+d)
                ll ma = a + c, mb = b + d;
                // compare ma/mb vs p/q
                // (__int128 to be safe)
                bool mLess = (__int128)ma * q < (__int128)p * mb;
                if (mLess) { a = ma; b = mb; }
                else       { c = ma; d = mb; }
            }
            if (amb) count++;
        }
    }
    cout << count << endl;
    return 0;
}
