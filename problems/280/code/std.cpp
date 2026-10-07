#include <bits/stdc++.h>
using namespace std;

struct State {
    int r, c;       // ant position (0 to G-1)
    int bottom;     // bitmask of seeds on bottom row (G bits)
    int carry;      // 0 = not carrying, 1 = carrying
    int top;        // number of seeds placed on top row (0 to G)
};

int G; // grid size
int total_states;
vector<double> E_old, E_new;

int encode(int r, int c, int bottom, int carry, int top) {
    // G*G positions, 2^G bottom masks, 2 carry, G+1 top counts
    int idx = top;
    idx = idx * 2 + carry;
    idx = idx * (1 << G) + bottom;
    idx = idx * G + c;
    idx = idx * G + r;
    return idx;
}

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(6);

    cin >> G;

    int all_seeds = (1 << G) - 1;

    total_states = G * G * (1 << G) * 2 * (G + 1);

    E_old.assign(total_states, 0.0);
    E_new.assign(total_states, 0.0);

    // Value iteration
    const double EPS = 1e-14;
    for (int iter = 0; iter < 200000; iter++) {
        double max_diff = 0.0;

        for (int r = 0; r < G; r++) {
            for (int c = 0; c < G; c++) {
                int deg = 0;
                if (r > 0) deg++;
                if (r < G - 1) deg++;
                if (c > 0) deg++;
                if (c < G - 1) deg++;

                for (int bottom = 0; bottom < (1 << G); bottom++) {
                    for (int carry = 0; carry <= 1; carry++) {
                        for (int top = 0; top <= G; top++) {
                            if (top == G) {
                                // absorbing state
                                int idx = encode(r, c, bottom, carry, top);
                                E_new[idx] = 0.0;
                                continue;
                            }

                            double expected = 0.0;

                            for (int d = 0; d < 4; d++) {
                                int nr = r + dr[d];
                                int nc = c + dc[d];
                                if (nr < 0 || nr >= G || nc < 0 || nc >= G)
                                    continue;

                                int nbottom = bottom;
                                int ncarry = carry;
                                int ntop = top;

                                // If moving to bottom row (nr == G-1) and not carrying, pick up seed if present
                                if (nr == G - 1 && ncarry == 0) {
                                    int bit = 1 << nc;
                                    if (nbottom & bit) {
                                        ncarry = 1;
                                        nbottom &= ~bit;
                                    }
                                }

                                // If moving to top row (nr == 0) and carrying, drop seed
                                if (nr == 0 && ncarry == 1) {
                                    ncarry = 0;
                                    ntop++;
                                }

                                int nidx = encode(nr, nc, nbottom, ncarry, ntop);
                                expected += E_old[nidx] / deg;
                            }

                            expected += 1.0;

                            int idx = encode(r, c, bottom, carry, top);
                            E_new[idx] = expected;
                            max_diff = max(max_diff, fabs(E_new[idx] - E_old[idx]));
                        }
                    }
                }
            }
        }

        swap(E_old, E_new);

        if (max_diff < EPS) {
            cerr << "Converged after " << iter + 1 << " iterations\n";
            break;
        }
    }

    // Initial state: center of grid (G/2, G/2), all seeds on bottom, not carrying, 0 on top
    int init_idx = encode(G / 2, G / 2, all_seeds, 0, 0);
    cout << E_old[init_idx] << "\n";

    return 0;
}
