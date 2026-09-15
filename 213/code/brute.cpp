#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 213: Brute force - Monte Carlo simulation
// Independent implementation for small N, R

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, R;
    cin >> N >> R;

    int total = N * N;
    mt19937 rng(42); // fixed seed for reproducibility

    // Precompute neighbors
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

    int trials = (N <= 5 && R <= 5) ? 50000 : 10000;
    double total_empty = 0;

    for (int t = 0; t < trials; t++) {
        vector<int> positions(total);
        iota(positions.begin(), positions.end(), 0); // initial: one per square

        for (int step = 0; step < R; step++) {
            for (int i = 0; i < total; i++) {
                int deg = neighbors[positions[i]].size();
                uniform_int_distribution<int> dist(0, deg - 1);
                positions[i] = neighbors[positions[i]][dist(rng)];
            }
        }

        // Count occupied squares
        vector<bool> occ(total, false);
        for (int p : positions) occ[p] = true;
        int empty_count = total - count(occ.begin(), occ.end(), true);
        total_empty += empty_count;
    }

    cout << fixed << setprecision(6) << total_empty / trials << "\n";
}
