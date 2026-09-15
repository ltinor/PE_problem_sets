#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// PE 764: 16x^2 + y^4 = z^2, 正整数, gcd(x,y,z)=1.
// (z-4x)(z+4x) = y^4. 设 a=z-4x, b=z+4x, 则 ab=y^4, gcd(a,b)∈{1,2,4,8}.
// 实际解只有 gcd(a,b)=1 和 gcd(a,b)=8 两种（暴力证实）。
//
// g=1: a=u^4, b=v^4, gcd(u,v)=1, u<v 均奇.
//      x=(v^4-u^4)/8, y=uv, z=(u^4+v^4)/2.
// g=8: a=8u, b=8v, gcd(u,v)=1. 解得 u=S^4,v=4R^4 (或对称), S 奇, gcd(R,S)=1.
//      x=|4R^4-S^4|, y=4RS, z=4S^4+16R^4.
//
// 验证: S(10^2)=81, S(10^4)=112851, S(10^7)≡248876211 (mod 1e9).
// 答案: S(10^16) mod 1e9 = 255228881.

const i64 MOD = 1000000000LL;

i64 gcd(i64 a, i64 b) { return b ? gcd(b, a%b) : a; }

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    i64 N;
    cin >> N;

    i64 ans = 0;
    i64 maxv = (i64)pow((long double)(2*N), 0.25L) + 2;

    // g=1
    for (i64 v = 1; v <= maxv; v++) {
        i64 v4 = v*v*v*v;
        if (v4 > 2*N) break;
        for (i64 u = 1; u < v; u++) {
            if (gcd(u, v) != 1) continue;
            i64 u4 = u*u*u*u;
            if ((v4 - u4) % 8 != 0) continue;
            i64 x = (v4 - u4) / 8;
            i64 y = u * v;
            i64 z = (u4 + v4) / 2;
            if (x <= 0 || x > N || y > N || z > N) continue;
            if (gcd(gcd(x, y), z) != 1) continue;
            ans = (ans + x + y + z) % MOD;
        }
    }

    // g=8
    i64 maxS = (i64)pow((long double)(N/4), 0.25L) + 2;
    i64 maxR = (i64)pow((long double)(N/16), 0.25L) + 2;
    for (i64 S = 1; S <= maxS; S++) {
        if (S % 2 == 0) continue;  // S 必须为奇
        i64 S4 = S*S*S*S;
        for (i64 R = 1; R <= maxR; R++) {
            if (gcd(R, S) != 1) continue;
            i64 R4 = R*R*R*R;
            i64 x = llabs(4*R4 - S4);
            i64 y = 4*R*S;
            i64 z = 4*S4 + 16*R4;
            if (x <= 0 || x > N || y > N || z > N) continue;
            if (gcd(gcd(x, y), z) != 1) continue;
            ans = (ans + x + y + z) % MOD;
        }
    }

    cout << ans << "\n";
    return 0;
}
