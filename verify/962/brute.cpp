#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 962 brute：与 std 相同的几何结论，但使用 __int128 大整数，
// 独立实现 gcd / 整数开方，用于交叉验证 std 的 64 位快速实现（防溢出/实现错误）。

i128 isqrt128(i128 x) {
    if (x <= 0) return 0;
    i128 lo = 0, hi = x;
    while (lo < hi) {
        i128 mid = (lo + hi + 1) / 2;
        if (mid <= x / mid) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

i128 gcd128(i128 a, i128 b) {
    while (b) { i128 t = a % b; a = b; b = t; }
    return a;
}

bool ce_integral(ll a, ll b, ll c) {
    i128 t = a + b;
    i128 N1 = (i128)a * a * a * (t - c) * (t + c);
    i128 D1 = (i128)b * t * t;
    i128 g = gcd128(N1, D1);
    i128 P = N1 / g, Q = D1 / g;
    if (Q != 1) return false;
    i128 r = isqrt128(P);
    return r * r == P;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;
    for (ll a = 1; a <= N; a++)
        for (ll b = a; a + b + b <= N; b++)
            for (ll c = b; c <= min(a + b - 1, N - a - b); c++)
                if (ce_integral(a, b, c)) ans++;

    cout << ans << "\n";
    return 0;
}
