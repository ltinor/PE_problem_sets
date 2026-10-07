#include<bits/stdc++.h>
using namespace std;

// 128-bit integer for large partition numbers
using i128 = __int128;

const int MAXN = 100;

// dp[i][j] = number of ways to partition i using numbers <= j
i128 dp[MAXN + 1][MAXN + 1];

void precompute() {
    for (int j = 0; j <= MAXN; j++) dp[0][j] = 1;
    for (int i = 1; i <= MAXN; i++) dp[i][0] = 0;

    for (int i = 1; i <= MAXN; i++) {
        for (int j = 1; j <= MAXN; j++) {
            dp[i][j] = dp[i][j-1];
            if (i >= j) dp[i][j] += dp[i-j][j];
        }
    }
}

// Print __int128
void print_i128(i128 x) {
    if (x == 0) { cout << "0"; return; }
    string s;
    while (x > 0) {
        s += char('0' + (x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        // p(N) - 1: ways to write as sum of at least 2 positive integers
        i128 ans = dp[N][N] - 1;
        print_i128(ans);
        cout << "\n";
    }

    return 0;
}
