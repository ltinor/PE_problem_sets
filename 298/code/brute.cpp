#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, M, K;
    cin >> T >> M >> K;

    // Fewer simulations for brute
    const int SIMS = 20000;
    double total_diff = 0;

    mt19937 rng(123);

    for (int sim = 0; sim < SIMS; sim++) {
        vector<int> larry_mem, robin_mem;
        vector<int> larry_last(K+1, -100), robin_enter(K+1, -100);
        int L = 0, R = 0;

        for (int turn = 0; turn < T; turn++) {
            int x = rng() % K + 1;

            auto lit = find(larry_mem.begin(), larry_mem.end(), x);
            if (lit != larry_mem.end()) {
                L++;
                larry_last[x] = turn;
            } else {
                if ((int)larry_mem.size() == M) {
                    int oldest = -1, oldest_time = turn + 1;
                    for (int v : larry_mem) {
                        if (larry_last[v] < oldest_time) {
                            oldest_time = larry_last[v];
                            oldest = v;
                        }
                    }
                    larry_mem.erase(find(larry_mem.begin(), larry_mem.end(), oldest));
                }
                larry_mem.push_back(x);
                larry_last[x] = turn;
            }

            auto rit = find(robin_mem.begin(), robin_mem.end(), x);
            if (rit != robin_mem.end()) {
                R++;
            } else {
                if ((int)robin_mem.size() == M) {
                    int longest = -1, longest_time = turn + 1;
                    for (int v : robin_mem) {
                        if (robin_enter[v] < longest_time) {
                            longest_time = robin_enter[v];
                            longest = v;
                        }
                    }
                    robin_mem.erase(find(robin_mem.begin(), robin_mem.end(), longest));
                }
                robin_mem.push_back(x);
                robin_enter[x] = turn;
            }
        }
        total_diff += abs(L - R);
    }

    cout << fixed << setprecision(8) << total_diff / SIMS << "\n";
    return 0;
}
