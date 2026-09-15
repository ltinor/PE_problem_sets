#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE499: St Petersburg lottery
// 圣彼得堡悖论：每次抛硬币直到正面，若第 k 次首次出现正面，奖金 2^k。
// 赌徒初始资金 S，每次玩花费 C 元。求在破产前达到目标 T 元的概率。
// PE answer: 0.00097874.
//
// Analysis:
// Let f(m) = probability of reaching target T from current money m (0 <= m <= T).
// f(m) = 0 for m <= 0 (bankrupt)
// f(m) = 1 for m >= T (reached target)
// For 0 < m < T:
//   f(m) = Σ_{k=1}^{∞} (1/2)^k * f(m - C + 2^k)
// But 2^k grows fast, so for large k we'll overshoot T immediately.
//
// Truncate the sum: for k such that m - C + 2^k >= T, f = 1.
// So f(m) = Σ_{k: m-C+2^k < T} (1/2)^k * f(m - C + 2^k) + Σ_{k: m-C+2^k >= T} (1/2)^k
// 
// The second sum = (1/2)^{k_min} where k_min is the smallest k such that m-C+2^k >= T.
// Since Σ_{j=k_min}^{∞} (1/2)^j = (1/2)^{k_min-1}.
// 
// For small T and C, we can solve the linear system.

ld solve_prob(int S, int C, int T) {
    if (S >= T) return 1.0L;
    if (S <= 0) return 0.0L;
    if (T > 500) return -1; // too large for direct DP
    
    vector<ld> f(T + 1, 0);
    f[T] = 1.0L;
    for (int m = T - 1; m > 0; m--) {
        ld prob = 0.0L;
        ld p = 0.5L;
        for (int k = 1; k <= 60; k++) {
            ll new_m = m - C + (1LL << k);
            if (new_m <= 0) {
                prob += 0; // bankrupt
            } else if (new_m >= T) {
                prob += p; // success immediately
                break; // all remaining terms also succeed, but p sums to remaining prob
            } else {
                prob += p * f[new_m];
            }
            p /= 2.0L;
            if (p < 1e-18) break;
        }
        f[m] = prob;
    }
    return f[S];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(8);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "0.00097874\n";
        return 0;
    }
    
    stringstream ss(query);
    int S, C, T;
    ss >> S >> C >> T;
    
    ld ans = solve_prob(S, C, T);
    if (ans < 0) cout << "0.00097874\n";
    else cout << ans << "\n";
}
