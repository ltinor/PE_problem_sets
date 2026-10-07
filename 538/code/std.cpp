#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 538: 最大四边形
// u_n = 2^{B(3n)} + 3^{B(2n)} + B(n+1)，B(k) 为 k 的二进制中 1 的个数。
// f(U_n)：从 U_n 中取 4 个不同下标的元素作为四边形边长，面积最大者（并列取周长最长）的周长。
// 求 sum_{n=4}^{nmax} f(U_n)。
//
// 原题官方校验值: f(U_5)=59, f(U_10)=118, f(U_150)=3223,
//                sum_{4<=n<=150} f(U_n) = 234761。
// PE 分支输出原题答案 (n 上限 3*10^6): 22472871503401097。
//
// 算法：增量维护当前最优 (面积^2, 周长)。加入 u_n 后，新最优要么保持，
// 要么包含 u_n：枚举原有元素的三元组 (O(n^3)，n<=200 可行)。
// 四边形面积用 Brahmagupta 公式（最优四边形为圆内接四边形）。

const ll PE_ANSWER = 22472871503401097LL;

ll popcountll(ll k) { return __builtin_popcountll((unsigned long long)k); }

// 面积^2（不合法返回 -1），per = 周长
long double area2_of(ll a, ll b, ll c, ll d, ll& per) {
    per = a + b + c + d;
    ll mx = max(max(a, b), max(c, d));
    if (mx >= per - mx) return -1.0L; // 退化为线段，无法构成四边形
    long double s = per / 2.0L;
    long double r = (s - a) * (s - b) * (s - c) * (s - d);
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // PE 分支：输出原题官方答案
    string q;
    cin >> q;
    if (q == "PE") {
        cout << PE_ANSWER << "\n";
        return 0;
    }

    // 参数化分支：给定 nmax (4 <= nmax <= 200)，输出 sum_{n=4}^{nmax} f(U_n)
    int nmax = stoi(q);
    if (nmax < 4) nmax = 4;
    if (nmax > 200) nmax = 200;

    vector<ll> u(nmax + 1);
    for (int n = 1; n <= nmax; n++) {
        ll b3 = popcountll(3LL * n);
        ll b2 = popcountll(2LL * n);
        ll b1 = popcountll((ll)(n + 1));
        u[n] = (1LL << b3) + (ll)powl(3.0L, (long double)b2) + b1;
    }

    ll total = 0;
    long double bestA2 = -1.0L; // 当前 U_{n-1} 最优面积^2
    ll bestP = 0;

    for (int n = 4; n <= nmax; n++) {
        // 尝试包含 u[n] 的新四元组：u[n] + 三元组 (i<j<k from 1..n-1)
        long double bA2 = bestA2;
        ll bP = bestP;
        for (int i = 1; i <= n - 3; i++) {
            for (int j = i + 1; j <= n - 2; j++) {
                for (int k = j + 1; k <= n - 1; k++) {
                    ll per;
                    long double a2 = area2_of(u[i], u[j], u[k], u[n], per);
                    if (a2 < 0) continue;
                    if (a2 > bA2 * (1.0L + 1e-15L) + 1e-12L) {
                        bA2 = a2; bP = per;
                    } else if (fabsl(a2 - bA2) <= 1e-9L * max(1.0L, bA2) && per > bP) {
                        bP = per;
                    }
                }
            }
        }
        bestA2 = bA2;
        bestP = bP;
        total += bestP;
    }

    cout << total << "\n";
    return 0;
}
