// PE180: Golden Triplets
// 恒等式(多项式展开验证): f_n(x,y,z) = (x+y+z)(x^n+y^n-z^n), 对所有整数 n 成立
// => golden triple ⟺ x^n+y^n=z^n; FLT 排除 |n|>=3, n=0 无解 => n ∈ {-2,-1,1,2}:
//    n=1: z=x+y | n=-1: z=xy/(x+y) | n=2: z=sqrt(x^2+y^2) | n=-2: z=xy/sqrt(x^2+y^2)
// x,y,z 均为 0<a<b<=K 既约分数; s=x+y+z 去重求和 t=u/v, 输出 u+v.
// 验证: K=35 -> 285196020571078987 (官方); K=5/10/20 -> 296/12519/19408891927 (参考 doctest)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u128 = __uint128_t;

ll gcdll(ll a, ll b) { while (b) { ll t = a % b; a = b; b = t; } return a; }
ll isqrtll(ll n) { ll r = (ll)sqrtl((long double)n); while (r > 0 && r*r > n) r--; while ((r+1)*(r+1) <= n) r++; return r; }

string u128str(u128 x) {
    if (x == 0) return "0";
    string s;
    while (x) { s += char('0' + (int)(x % 10)); x /= 10; }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string first; cin >> first;
    bool pe = (first == "PE");
    ll K = pe ? 35 : stoll(first);

    set<pair<ll,ll>> uniq;
    for (ll xn = 1; xn <= K; xn++)
    for (ll xd = xn+1; xd <= K; xd++)
    for (ll yn = 1; yn <= K; yn++)
    for (ll yd = yn+1; yd <= K; yd++) {
        pair<ll,ll> cases[4];
        int nc = 0;
        cases[nc++] = {xn*yd + xd*yn, xd*yd};                                          // n=1
        ll zn = xn*xn*yd*yd + xd*xd*yn*yn, zd = xd*xd*yd*yd;                           // n=2
        ll r1 = isqrtll(zn), r2 = isqrtll(zd);
        if (r1*r1 == zn && r2*r2 == zd) cases[nc++] = {r1, r2};
        cases[nc++] = {xn*yn, xd*yn + xn*yd};                                          // n=-1
        zn = xn*xn*yn*yn; zd = xd*xd*yn*yn + xn*xn*yd*yd;                              // n=-2
        r1 = isqrtll(zn); r2 = isqrtll(zd);
        if (r1*r1 == zn && r2*r2 == zd) cases[nc++] = {r1, r2};
        for (int i = 0; i < nc; i++) {
            ll zu = cases[i].first, zv = cases[i].second;
            ll g = gcdll(zu, zv); zu /= g; zv /= g;
            if (!(0 < zu && zu < zv && zv <= K)) continue;
            // s = x+y+z
            ll sn = xn*yd*zv + yn*xd*zv + zu*xd*yd;
            ll sd = xd*yd*zv;
            ll g2 = gcdll(sn, sd); sn /= g2; sd /= g2;
            uniq.insert({sn, sd});
        }
    }
    auto gcd128 = [](u128 a, u128 b) { while (b) { u128 t = a % b; a = b; b = t; } return a; };
    u128 U = 0, V = 0;
    for (auto& [u, v] : uniq) {
        if (V == 0) { U = u; V = v; continue; }
        U = U * (u128)v + (u128)u * V;
        V = V * (u128)v;
        u128 g = gcd128(U, V);
        U /= g; V /= g;
    }
    cout << u128str(U + V) << endl;
    return 0;
}
