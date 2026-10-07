#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;

        int best_d = 0, best_len = 0;

        for (int d = 2; d < N; d++) {
            int x = d;
            while (x % 2 == 0) x /= 2;
            while (x % 5 == 0) x /= 5;
            if (x == 1) continue;

            // Find cycle length by tracking remainders
            vector<int> seen(x, -1);
            int rem = 1 % x;
            seen[rem] = 0;
            int step = 0;

            while (true) {
                rem = (rem * 10) % x;
                step++;
                if (seen[rem] != -1) {
                    int cycle_len = step - seen[rem];
                    if (cycle_len > best_len) {
                        best_len = cycle_len;
                        best_d = d;
                    }
                    break;
                }
                seen[rem] = step;
            }
        }

        cout << best_d << " " << best_len << "\n";
    }
}
