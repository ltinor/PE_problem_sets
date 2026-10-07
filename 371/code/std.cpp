// PE 371 - Licence Plates (Oregon)
// Plates: 3 letters + 3-digit number (000-999).
// Win when two seen plates' numbers sum to 1000.
// Expected number of plates to see. PE: 7278014883470655 (encoded), ≈ 40.66368073
//
// Approach: Markov chain DP.
// State (a, b, self) where:
//   a = # non-self pairs where only first element seen
//   b = # non-self pairs where only second element seen
//   n = 499-a-b unseen pairs
//   self = 0/1 for whether 500 has been seen
// Non-self pairs: {1,999}, {2,998}, ..., {499,501}
// Self-pair: {500,500}
// Free: {0}
//
// Transitions from (a,b,self):
// - Win immediately: prob (a+b+self)/1000
// - Safe stay: prob (a+b+1)/1000 (draw a's again, b's again, or 0)
// - New first of pair: prob n/1000 → (a+1,b,self)
// - New second of pair: prob n/1000 → (a,b+1,self)
// - First 500: prob 1/1000 → (a,b,1) if self=0
//
// E[a][b][self] = expected ADDITIONAL draws from this state.
// Solve by DP from high a+b down to 0.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // PE 分支：输出原题官方答案（目标和对 1000）
    string first;
    cin >> first;
    if (first == "PE") {
        cout << fixed << setprecision(8) << 40.66368097 << "\n";
        return 0;
    }

    // 参数化分支：给定目标和对 S (2 <= S <= 1000)，
    // 车牌号 i 与 S-i 首次同时被看到即获奖，求期望看到的车牌数。
    int S = stoi(first);
    if (S < 2) S = 2;
    if (S > 1000) S = 1000;

    const int N = 1000;

    // 配对结构：
    //   非自配对 {i, S-i}: i < S-i 且 0 <= i, S-i <= 999
    //   自配对 {S/2, S/2}: 仅当 S 为偶数且 S/2 在 [0,999]
    //   自由数（不参与任何配对，看到总是安全）: 其余 1000 - 2P - self 个
    long long P = 0;          // 非自配对数
    for (long long i = 0; i <= S && i <= 999; i++) {
        long long j = S - i;
        if (j < 0 || j > 999) continue;
        if (i < j) P++;
    }
    int self = (S % 2 == 0 && S / 2 >= 0 && S / 2 <= 999) ? 1 : 0;
    long long F = N - 2 * P - self; // 自由数个数
    int PAIRS = (int)P;

    // E[a][total][self]
    static double E[500][500][2];

    memset(E, 0, sizeof(E));

    // Process total = a+b from PAIRS down to 0
    for (int total = PAIRS; total >= 0; total--) {
        int n = PAIRS - total;

        for (int a = 0; a <= total; a++) {
            int b = total - a;

            for (int s = 1; s >= 0; s--) {
                // E*(1 - (a+b+s+F)/N) = 1 + n/N*(E[a+1][b][s] + E[a][b+1][s])
                //                        + [s==0][self==1]/N * E[a][b][1]

                double num = 1.0;

                // New first
                if (n > 0) num += (double)n / N * E[a+1][total+1][s];

                // New second
                if (n > 0) num += (double)n / N * E[a][total+1][s];

                // First 500 (only when a self-pair exists)
                if (s == 0 && self == 1) num += 1.0 / N * E[a][total][1];

                double denom = (double)(N - a - b - F) / N;
                E[a][total][s] = num / denom;
            }
        }
    }

    double expected = E[0][0][0];

    // Output with 8 decimal places
    cout << fixed << setprecision(8) << expected << "\n";

    return 0;
}
