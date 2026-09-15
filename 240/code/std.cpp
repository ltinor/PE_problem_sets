#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 240: Top Dice
// N dice, S-sided (1..S). Top K sum to T.
// Count number of ways.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, S, K, T;
    cin >> N >> S >> K >> T;

    // Precompute combinations C(n, k)
    vector<vector<__int128>> C(N + 1, vector<__int128>(N + 1, 0));
    for (int i = 0; i <= N; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i-1][j-1] + C[i-1][j];
    }

    // DP: dp[total][top][sum]
    // total = #dice assigned values >= current v
    // top = #dice in top K
    // sum = sum of top K dice
    const int MAX_SUM = K * S;
    vector<vector<vector<__int128>>> dp(N + 1,
        vector<vector<__int128>>(K + 1, vector<__int128>(MAX_SUM + 1, 0)));
    dp[0][0][0] = 1;

    for (int v = S; v >= 1; v--) {
        vector<vector<vector<__int128>>> ndp(N + 1,
            vector<vector<__int128>>(K + 1, vector<__int128>(MAX_SUM + 1, 0)));

        for (int total = 0; total <= N; total++) {
            for (int top = 0; top <= K; top++) {
                for (int sum = 0; sum <= MAX_SUM; sum++) {
                    if (dp[total][top][sum] == 0) continue;

                    // Add x dice of value v
                    int remain = N - total;
                    for (int x = 0; x <= remain; x++) {
                        int t = min(x, K - top); // how many go to top K
                        int ntop = top + t;
                        int nsum = sum + t * v;
                        int ntotal = total + x;

                        if (nsum > MAX_SUM) continue;

                        ndp[ntotal][ntop][nsum] += dp[total][top][sum] * C[remain][x];
                    }
                }
            }
        }
        dp = ndp;
    }

    // Answer
    __int128 ans = dp[N][K][T];

    // Convert __int128 to string for output
    if (ans == 0) {
        cout << "0\n";
    } else {
        string s;
        while (ans > 0) {
            s += (char)('0' + (int)(ans % 10));
            ans /= 10;
        }
        reverse(s.begin(), s.end());
        cout << s << "\n";
    }

    return 0;
}
