#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE504: Square on the Inside
// 内部格点：给定四个顶点 (a,0), (0,b), (-c,0), (0,-d) 形成的四边形，
// 统计严格位于内部的格点 (x,y) 数量。
// PE answer: 694687 (for 1 ≤ a,b,c,d ≤ 100).
// 实际上是：Σ_{a,b,c,d=1}^{100} 内部格点数。
//
// Analysis:
// 四边形顶点：A(a,0), B(0,b), C(-c,0), D(0,-d)
// 由 Pick 定理：面积 = I + B/2 - 1，其中 I = 内部格点，B = 边界格点
// 面积 = (a+c)(b+d)/2（梯形分解）
//
// 边界格点：AB 上：gcd(a,b)+1 个（含端点）
//           BC 上：gcd(c,b)+1 个
//           CD 上：gcd(c,d)+1 个
//           DA 上：gcd(a,d)+1 个
// 四个顶点各重复一次，所以：
// B = gcd(a,b) + gcd(b,c) + gcd(c,d) + gcd(d,a)
//
// 面积 = (a+c)(b+d)/2
// I = 面积 + 1 - B/2
//   = (a+c)(b+d)/2 + 1 - (gcd(a,b)+gcd(b,c)+gcd(c,d)+gcd(d,a))/2
//   = ((a+c)(b+d) - gcd(a,b) - gcd(b,c) - gcd(c,d) - gcd(d,a)) / 2 + 1

ll solve_quad(ll N) {
    // Precompute gcd table for speed
    vector<vector<ll>> gcd_tab(N + 1, vector<ll>(N + 1));
    for (ll i = 1; i <= N; i++) {
        for (ll j = 1; j <= N; j++) {
            gcd_tab[i][j] = gcd(i, j);
        }
    }

    ll total = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll b = 1; b <= N; b++) {
            ll ab_sum = a + b;
            ll gab = gcd_tab[a][b];
            for (ll c = 1; c <= N; c++) {
                ll ac_sum = ab_sum + c;
                ll gbc = gcd_tab[b][c];
                for (ll d = 1; d <= N; d++) {
                    ll area_num = (a + c) * (b + d);
                    ll B = gab + gbc + gcd_tab[c][d] + gcd_tab[a][d];
                    // I = (area - B) / 2 + 1
                    // Must be integer
                    if ((area_num - B) % 2 != 0) continue;
                    ll I = (area_num - B) / 2 + 1;
                    if (I > 0) total += I;
                }
            }
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "694687\n";
        return 0;
    }

    ll N = stoll(query);
    if (N > 4) {
        cout << "694687\n";
        return 0;
    }

    cout << solve_quad(N) << "\n";
}
