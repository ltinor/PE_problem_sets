#include<bits/stdc++.h>
using namespace std;

// Markov chain for The Chase
// N players (even), 2 dice start opposite
// State: signed difference d = (p2-p1+N) mod N, initially N/2
// Game ends when d = 0
// 
// Each die: P(left)=-1: 1/6, P(right)=+1: 1/6, P(keep)=0: 2/3
// d' = (d + d2_move - d1_move) mod N
// 
// Transition probs for d (mod N):
// d -> d:     1/2
// d -> d+1:   2/9
// d -> d-1:   2/9  
// d -> d+2:   1/36
// d -> d-2:   1/36

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // E[0] = 0, E[d] for d=1..N-1
    vector<double> E(N, 0.0);
    for (int i = 1; i < N; i++) E[i] = (double)N * N / 4.0; // initial guess

    // Iterate until convergence
    for (int iter = 0; iter < 100000; iter++) {
        double max_diff = 0.0;
        for (int d = 1; d < N; d++) {
            int dp1 = (d + 1) % N;
            int dm1 = (d - 1 + N) % N;
            int dp2 = (d + 2) % N;
            int dm2 = (d - 2 + N) % N;

            double new_E = 2.0 
                + (4.0/9.0) * E[dp1]
                + (4.0/9.0) * E[dm1]
                + (1.0/18.0) * E[dp2]
                + (1.0/18.0) * E[dm2];

            max_diff = max(max_diff, fabs(new_E - E[d]));
            E[d] = new_E;
        }
        if (max_diff < 1e-12) break;
    }

    cout << fixed << setprecision(6) << E[N/2] << "\n";
    return 0;
}
