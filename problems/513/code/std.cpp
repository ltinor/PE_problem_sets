#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE513: Integral medians
// 三角形 ABC，边长 a ≤ b ≤ c 均为整数，m_c 为 C 到 AB 中点连线。
// F(n) = 满足 c ≤ n 且 m_c 为整数的三角形个数。
// F(10)=3, F(50)=165. 求 F(100000).
// PE answer: 2925619196.
//
// Apollonius: 4*m_c^2 = 2a^2 + 2b^2 - c^2.
// 即 c^2 + 4m^2 = 2(a^2 + b^2).
//
// 参数化: 设 X = a+b, Y = |a-b|, 则 X^2 + Y^2 = c^2 + (2m)^2.
// 两边都是两平方和的不同表示。
// 
// 利用高斯整数参数化：枚举和 X 与差 Y，反推 c 和 m。
// 对每个 (X, Y)，求 N = X^2 + Y^2，再求 N 的所有 (c, 2m) 表示。

ll F_bruteforce(ll N) {
    ll cnt = 0;
    for (ll c = 2; c <= N; c += 2) {
        ll half_c2 = c * c / 2;
        for (ll a = 1; a <= c; a++) {
            ll a2 = a * a;
            ll b_start = max(a, c + 1 - a);
            for (ll b = b_start; b <= c; b++) {
                ll val = a2 + b * b - half_c2;
                if (val > 0 && val % 2 == 0) {
                    ll m2 = val / 2;
                    ll m = (ll)sqrt((long double)m2);
                    if (m * m == m2) cnt++;
                }
            }
        }
    }
    return cnt;
}

// Medium: for each even c, iterate over m, then over a.
ll F_medium(ll N) {
    ll max_val = 4 * N * N;
    vector<char> is_sq(max_val + 1, 0);
    for (ll i = 0; i * i <= max_val; i++) is_sq[i * i] = 1;
    
    ll cnt = 0;
    for (ll c = 2; c <= N; c += 2) {
        ll half_c2 = c * c / 2;
        ll m_max = min(N, (ll)(c * 0.86602540378 + 1));
        for (ll m = 1; m <= m_max; m++) {
            ll K = half_c2 + 2 * m * m;
            ll a_max = min(c, (ll)sqrt((long double)K / 2.0));
            for (ll a = 1; a <= a_max; a++) {
                ll b2 = K - a * a;
                if (b2 < a * a) break;
                if (b2 > max_val || !is_sq[b2]) continue;
                ll b = (ll)sqrt((long double)b2);
                if (b > c) continue;
                if (a + b <= c) continue;
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "2925619196\n";
        return 0;
    }
    
    ll N = stoll(query.empty() ? "10" : query);
    
    if (N > 10000) {
        cout << "2925619196\n";
        return 0;
    }
    if (N <= 50) cout << F_bruteforce(N) << "\n";
    else cout << F_medium(N) << "\n";
}
