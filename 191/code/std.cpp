#include<bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // dp[i][late][absent]: after i days, lates used (0/1), consecutive absences (0/1/2)
    // i from 0..N, late=0..1, absent=0..2
    // dp[i][l][a] = number of strings of length i ending with 'a' consecutive absences, using 'l' lates
    vector<vector<vector<ll>>> dp(N+1, vector<vector<ll>>(2, vector<ll>(3, 0)));
    dp[0][0][0] = 1;

    for (int i = 0; i < N; i++) {
        for (int late = 0; late <= 1; late++) {
            for (int absent = 0; absent <= 2; absent++) {
                ll cur = dp[i][late][absent];
                if (cur == 0) continue;

                // On time (O): resets consecutive absences
                dp[i+1][late][0] += cur;

                // Late (L): only if we haven't been late yet
                if (late == 0) {
                    dp[i+1][1][0] += cur;
                }

                // Absent (A): increment consecutive absences if < 2
                if (absent < 2) {
                    dp[i+1][late][absent+1] += cur;
                }
            }
        }
    }

    ll ans = 0;
    for (int late = 0; late <= 1; late++) {
        for (int absent = 0; absent <= 2; absent++) {
            ans += dp[N][late][absent];
        }
    }

    cout << ans << "\n";
    return 0;
}
