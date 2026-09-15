#include<bits/stdc++.h>
using namespace std;

// PE 232: The Race
// dp1[a][b] = prob P2 wins, P1's turn, needs a vs b
// dp2[a][b] = prob P2 wins, P2's turn, needs a vs b

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S;
    cin >> S;

    vector<vector<double>> dp1(S + 2, vector<double>(S + 2, 0.0));
    vector<vector<double>> dp2(S + 2, vector<double>(S + 2, 0.0));

    // Base
    for (int a = 0; a <= S; a++) {
        for (int b = 0; b <= S; b++) {
            if (a == 0 && b == 0) dp1[a][b] = dp2[a][b] = 0.0;
            else if (a == 0) dp1[a][b] = dp2[a][b] = 0.0; // P1 won
            else if (b == 0) dp1[a][b] = dp2[a][b] = 1.0; // P2 won
        }
    }

    // Bottom-up
    for (int a = 1; a <= S; a++) {
        for (int b = 1; b <= S; b++) {
            // Compute dp2[a][b] = max_T [ p_T*dp1[a][max(0,b-score)] + (1-p_T)*dp1[a][b] ]
            // dp1[a][b] = 0.5*dp2[a-1][b] + 0.5*dp2[a][b]
            // Substitute and solve for dp2[a][b] = X.
            // Two cases: score > b (b'=0, use base) and score ≤ b (b'>0, use general).

            double best = 0.0;
            for (int T = 1; ; T++) {
                int score = 1 << (T - 1);
                if (score > S) break;
                double pT = 1.0 / (1 << T);
                int bp = max(0, b - score);

                double X;
                if (bp == 0) {
                    // b'=0: dp1[a][0] = 1 (base)
                    // dp1[a][b] = 0.5*dp2[a-1][b] + 0.5*X
                    // X = pT*1 + (1-pT)*(0.5*dp2[a-1][b] + 0.5*X)
                    // X*(1 - 0.5*(1-pT)) = pT + 0.5*(1-pT)*dp2[a-1][b]
                    // X*(0.5+0.5*pT) = pT + 0.5*(1-pT)*dp2[a-1][b]
                    // X = (2*pT + (1-pT)*dp2[a-1][b]) / (1 + pT)
                    X = (2.0 * pT + (1.0 - pT) * dp2[a-1][b]) / (1.0 + pT);
                } else {
                    // b'>0: use general substitution
                    // X = [ pT*(dp2[a-1][bp]+dp2[a][bp]) + (1-pT)*dp2[a-1][b] ] / (1+pT)
                    X = (pT * (dp2[a-1][bp] + dp2[a][bp]) + (1.0 - pT) * dp2[a-1][b]) / (1.0 + pT);
                }

                if (X > best) best = X;
            }
            dp2[a][b] = best;
            dp1[a][b] = 0.5 * dp2[a-1][b] + 0.5 * dp2[a][b];
        }
    }

    cout << fixed << setprecision(8) << dp1[S][S] << "\n";
    return 0;
}
