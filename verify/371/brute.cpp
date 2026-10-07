#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S;
    cin >> S;

    // Monte Carlo simulation for verification
    const int TRIALS = 5000000;
    mt19937 rng(42);
    uniform_int_distribution<int> dist(0, S - 1);

    long long total = 0;
    for (int t = 0; t < TRIALS; t++) {
        vector<int> seen(S, 0);
        int draws = 0;
        while (true) {
            int x = dist(rng);
            draws++;
            if (x == 0) continue;
            if (x == S / 2) {
                seen[x]++;
                if (seen[x] >= 2) break;
            } else if (seen[S - x]) break;
            else seen[x]++;
        }
        total += draws;
    }

    double ans = (double)total / TRIALS;
    cout << fixed << setprecision(8) << ans << "\n";
    return 0;
}
