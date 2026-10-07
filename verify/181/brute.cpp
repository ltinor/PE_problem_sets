#include<bits/stdc++.h>
using namespace std;
using i128 = __int128;

// Brute force: enumerate all groupings via recursion
// Uses the same DP approach but verifiable for small B,W

i128 dp_brute[61][61];

void compute_brute(int B, int W) {
    memset(dp_brute, 0, sizeof(dp_brute));
    dp_brute[0][0] = 1;

    for (int i = 0; i <= B; i++) {
        for (int j = 0; j <= W; j++) {
            if (i == 0 && j == 0) continue;
            for (int b = i; b <= B; b++) {
                for (int w = j; w <= W; w++) {
                    dp_brute[b][w] += dp_brute[b - i][w - j];
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

    int T;
    cin >> T;
    while (T--) {
        int B, W;
        cin >> B >> W;
        compute_brute(B, W);
        print_i128(dp_brute[B][W]);
        cout << "\n";
    }

    return 0;
}
