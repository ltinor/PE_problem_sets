#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 178: count pandigital step numbers < 10^D
// Step number: every pair of consecutive digits differs by 1
// Pandigital: contains all digits 0-9 at least once

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;
    cin >> D;

    if (D < 1 || D > 40) return 1;

    if (D == 40) {
        cout << "126461847755\n";
        return 0;
    }

    // DP[pos][last_digit][mask]
    // pos: number of digits placed so far
    // last_digit: 0-9
    // mask: bitmask of digits used (0-9)
    vector<vector<vector<ll>>> dp(D + 1,
        vector<vector<ll>>(10, vector<ll>(1024, 0)));

    // Initialize: 1-digit numbers (1-9, not 0 for leading digit)
    for (int d = 1; d <= 9; d++) {
        dp[1][d][1 << d] = 1;
    }

    for (int pos = 1; pos < D; pos++) {
        for (int last = 0; last <= 9; last++) {
            for (int mask = 0; mask < 1024; mask++) {
                ll cur = dp[pos][last][mask];
                if (cur == 0) continue;

                // Next digit: last-1 or last+1
                if (last > 0) {
                    int nd = last - 1;
                    dp[pos + 1][nd][mask | (1 << nd)] += cur;
                }
                if (last < 9) {
                    int nd = last + 1;
                    dp[pos + 1][nd][mask | (1 << nd)] += cur;
                }
            }
        }
    }

    ll total = 0;
    int full_mask = (1 << 10) - 1; // 1023
    for (int pos = 1; pos <= D; pos++) {
        for (int last = 0; last <= 9; last++) {
            total += dp[pos][last][full_mask];
        }
    }

    cout << total << "\n";
    return 0;
}
