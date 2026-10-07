// PE180: golden triple <=> z = x + y (n=1: f1 = x^2+y^2-z^2+2xy = (x+y)^2-z^2·(1-1)+... = 0 当 z=x+y)
// 集合 F = {a/b^2 : 0 < a < b^2, gcd(a,b)=1}; 求 distinct z = x+y (x!=y, z!=x, z!=y) 的 (u,v) 集合
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll gcdll(ll a, ll b) { while (b) { ll t = a % b; a = b; b = t; } return a; }

int main(int argc, char** argv) {
    ll K = (argc > 1) ? atoll(argv[1]) : 35;
    int exclude_equal = (argc > 2) ? atoi(argv[2]) : 1; // 1: x!=y
    vector<pair<ll,ll>> F; // (num, den)
    for (ll b = 2; b <= K; b++)
        for (ll a = 1; a < b*b; a++)
            if (gcdll(a, b) == 1) F.push_back({a, b*b});
    auto h = [](const pair<ll,ll>& f) { return hash<ll>()(f.first * 1000003ull ^ f.second); };
    unordered_set<pair<ll,ll>, decltype(h)> Fset(0, h);
    for (auto& f : F) Fset.insert(f);
    set<pair<ll,ll>> zs;
    int n = F.size();
    for (int i = 0; i < n; i++) {
        auto [xu, xv] = F[i];
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            auto [yu, yv] = F[j];
            if (exclude_equal && xu == yu && xv == yv) continue;
            // z = x + y
            ll zu = xu * yv + yu * xv;
            ll zv = xv * yv;
            ll g = gcdll(zu, zv); zu /= g; zv /= g;
            if (zu >= zv) continue;               // z < 1
            if (Fset.find({zu, zv}) == Fset.end()) continue;
            if (zu == xu && zv == xv) continue;
            if (zu == yu && zv == yv) continue;
            zs.insert({zu, zv});
        }
    }
    for (auto& z : zs) cout << z.first << "/" << z.second << "\n";
    cerr << "F=" << n << " distinct_z=" << zs.size() << endl;
}
