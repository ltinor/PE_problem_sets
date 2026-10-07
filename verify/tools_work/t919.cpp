// PE919 parametrized enumerator
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char** argv) {
    ll P = (argc > 1) ? stoll(argv[1]) : 100;
    // 生成全部 (x, y, z): x^2 + 15 y^2 = z^2, z <= 4P (z = 4c)
    // shape A: x=|m^2-15n^2|, y=2mn, z=m^2+15n^2 (d 缩放)
    // shape B (m,n 奇): x=|m^2-15n^2|/2, y=mn, z=(m^2+15n^2)/2
    struct Tri { int a, b, c; };
    vector<array<int,3>> tris;
    ll zmax = 4 * P;
    auto try_recover = [&](ll x, ll y, ll z) {
        if (z % 4 != 0) return;
        ll c = z / 4;
        for (int which = 0; which < 3; which++) {
            ll num = which == 0 ? (x + y) : (which == 1 ? (x - y) : (y - x));
            if (num < 4) continue;
            if (num % 4 != 0) continue;
            ll a = num / 4;
            if (a < 1) continue;
            ll b = y;
            // 角色 opp=c: 2|a^2+b^2-c^2| == a*b
            if (2 * llabs(a * a + b * b - c * c) != a * b) continue;
            if (a + b + c > P) continue;
            ll lo = min({a, b, c}), hi = max({a, b, c}), mid = a + b + c - lo - hi;
            if (lo + mid <= hi) continue; // 三角形不等式
            tris.push_back({(int)lo, (int)mid, (int)hi});
        }
    };
    for (ll m = 1; m * m <= zmax; m++) {
        for (ll n = 1; 15 * n * n + m * m <= zmax; n++) {
            if (std::gcd(m, n) != 1) continue;
            ll base = m * m + 15 * n * n;
            ll diff = llabs(m * m - 15 * n * n);
            // shape A: 先除 gcd 得原始解, 再整数缩放 (D=15 非平方, 整点可能需约减, 如 (35,60,235)/5=(7,12,47))
            ll gA = std::gcd(std::gcd(diff, 2 * m * n), base);
            ll bA = base / gA, dA = diff / gA, yA = 2 * m * n / gA;
            for (ll d = 1; d * bA <= zmax; d++) {
                try_recover(d * dA, d * yA, d * bA);
            }
            // shape B: m,n 均奇
            if (m % 2 == 1 && n % 2 == 1) {
                ll b2 = base / 2, df2 = diff / 2, y2 = m * n;
                ll gB = std::gcd(std::gcd(df2, y2), b2);
                b2 /= gB; df2 /= gB; y2 /= gB;
                for (ll d = 1; d * b2 <= zmax; d++) {
                    try_recover(d * df2, d * y2, d * b2);
                }
            }
        }
    }
    sort(tris.begin(), tris.end());
    tris.erase(unique(tris.begin(), tris.end()), tris.end());
    ll S = 0;
    for (auto& t : tris) {
        ll s = (ll)t[0] + t[1] + t[2];
        ll g = std::gcd(std::gcd(t[0], t[1]), t[2]);
        if (g != 1) continue;                    // 倍数由原始种子级数覆盖
        ll T = P / s;
        S += s * (T * (T + 1) / 2);
    }
    printf("P=%lld tris=%zu S=%lld\n", P, tris.size(), S);
    return 0;
}
