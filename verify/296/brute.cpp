#include <bits/stdc++.h>
using namespace std;
#define ll long long

// 暴力验证版：三重循环枚举所有整数边长三角形，直接判断 (a+b) | a*c。
// 仅用于小规模 P 与 std 对拍（check.sh）。

ll gcd_ll(ll a, ll b) { return b ? gcd_ll(b, a % b) : a; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll P;
    cin >> P;

    ll ans = 0;
    for (ll a = 1; a <= P; ++a) {           // BC = a
        for (ll b = a; a + b + 1 <= P; ++b) { // AC = b, a<=b
            ll d = a + b;
            for (ll c = b; c <= P - d && c <= d - 1; ++c) { // AB = c, b<=c<a+b, a+b+c<=P
                // BE = a*c/(a+b) 为整数 <=> (a+b) | a*c
                if ((a * c) % d == 0) ++ans;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
