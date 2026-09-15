#include <bits/stdc++.h>
using namespace std;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int G;
    cin >> G;

    // Monte Carlo simulation for small grids
    const int SIMS = 50000;
    srand(time(0));

    double total_steps = 0;
    int all_seeds = (1 << G) - 1;

    for (int sim = 0; sim < SIMS; sim++) {
        int r = G / 2, c = G / 2;
        int bottom = all_seeds;
        int carry = 0;
        int top = 0;
        long long steps = 0;

        while (top < G) {
            // Build valid moves
            vector<pair<int,int>> moves;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr >= 0 && nr < G && nc >= 0 && nc < G)
                    moves.push_back({nr, nc});
            }

            // Random move
            int idx = rand() % moves.size();
            r = moves[idx].first;
            c = moves[idx].second;

            // Pick up seed on bottom row
            if (r == G - 1 && carry == 0) {
                int bit = 1 << c;
                if (bottom & bit) {
                    carry = 1;
                    bottom &= ~bit;
                }
            }

            // Drop seed on top row
            if (r == 0 && carry == 1) {
                carry = 0;
                top++;
            }

            steps++;

            if (steps > 10000000) break; // safety
        }

        total_steps += steps;
    }

    cout << fixed << setprecision(6);
    cout << total_steps / SIMS << "\n";
    return 0;
}
