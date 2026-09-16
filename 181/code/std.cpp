#include<bits/stdc++.h>
using namespace std;

using i128 = __int128;

const int MAX_B = 60;
const int MAX_W = 60;

i128 dp[MAX_B + 1][MAX_W + 1];

void precompute() {
    dp[0][0] = 1;

    // Process all group types (i, j) in lexicographic order
    // i = black, j = white, skip (0,0)
    for (int i = 0; i <= MAX_B; i++) {
        for (int j = 0; j <= MAX_W; j++) {
            if (i == 0 && j == 0) continue;
            // Unbounded knapsack: add 0 or more copies of this group type
            for (int b = i; b <= MAX_B; b++) {
                for (int w = j; w <= MAX_W; w++) {
                    dp[b][w] += dp[b - i][w - j];
                }
            }
        }
    }
}

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
        int B, W;
        cin >> B >> W;
        print_i128(dp[B][W]);
        cout << endl;
    }
    cout << "\n";

    return 0;
}
