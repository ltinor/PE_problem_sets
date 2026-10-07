#include<bits/stdc++.h>
using namespace std;

// Brute force: simulate all possible game paths via recursion
// Only feasible for very small S (<= 6 or so)
// This is a simplified brute that enumerates all possible T choices too

double solve_brute(int a, int b, int turn, int S, vector<vector<vector<double>>>& memo);

double solve_brute(int a, int b, int turn, int S) {
    if (a <= 0 && b <= 0) return 0.0; // draw
    if (a <= 0) return 0.0; // P1 won
    if (b <= 0) return 1.0; // P2 won

    if (turn == 1) {
        // P1's turn
        double hit = solve_brute(a - 1, b, 2, S);
        double miss = solve_brute(a, b, 2, S);
        return 0.5 * hit + 0.5 * miss;
    } else {
        // P2's turn: try all T
        double best = 0.0;
        for (int T = 1; T <= 6; T++) {
            double prob = 1.0 / (1 << T);
            int score = 1 << (T - 1);
            int new_b = max(0, b - score);
            double val = prob * solve_brute(a, new_b, 1, S) +
                         (1.0 - prob) * solve_brute(a, b, 1, S);
            best = max(best, val);
        }
        return best;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S;
    cin >> S;

    double ans = solve_brute(S, S, 1, S);
    cout << fixed << setprecision(8) << ans << "\n";
    return 0;
}
