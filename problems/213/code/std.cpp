#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 213: Flea Circus - expected unoccupied squares
// Original: 30×30 grid, 50 rings, answer = 330.721154
// Adapted: parameterized N (grid size) and R (rings)
// N ≤ 30, R ≤ 50

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, R;
    cin >> N >> R;

    int total = N * N;
    // dp[pos][step] = probability distribution for a flea starting at a given position
    // We'll compute for each start position independently
    vector<vector<double>> prob(total, vector<double>(total, 0.0));

    // Precompute neighbors for each position
    vector<vector<int>> neighbors(total);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int idx = i * N + j;
            if (i > 0) neighbors[idx].push_back((i-1) * N + j);
            if (i < N-1) neighbors[idx].push_back((i+1) * N + j);
            if (j > 0) neighbors[idx].push_back(i * N + (j-1));
            if (j < N-1) neighbors[idx].push_back(i * N + (j+1));
        }
    }

    // For each start position, compute probability after R steps
    for (int start = 0; start < total; start++) {
        vector<double> cur(total, 0.0);
        cur[start] = 1.0;

        for (int step = 0; step < R; step++) {
            vector<double> nxt(total, 0.0);
            for (int pos = 0; pos < total; pos++) {
                if (cur[pos] == 0.0) continue;
                int deg = neighbors[pos].size();
                double p = cur[pos] / deg;
                for (int nb : neighbors[pos]) {
                    nxt[nb] += p;
                }
            }
            cur = std::move(nxt);
        }

        for (int pos = 0; pos < total; pos++) {
            prob[start][pos] = cur[pos];
        }
    }

    // Expected empty squares = sum over squares of P(square empty)
    double ans = 0.0;
    for (int pos = 0; pos < total; pos++) {
        double p_empty = 1.0;
        for (int start = 0; start < total; start++) {
            p_empty *= (1.0 - prob[start][pos]);
        }
        ans += p_empty;
    }

    cout << fixed << setprecision(6) << ans << "\n";
}
