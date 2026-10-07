#include<bits/stdc++.h>
using namespace std;

// PE 208: Brute force - enumerate all 2^n paths for small n

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n % 5 != 0 || n > 25) {
        cout << "0\n";
        return 0;
    }

    long long ans = 0;

    // Enumerate all 2^n turn sequences
    for (int mask = 0; mask < (1 << n); mask++) {
        int c[5] = {0};
        int facing = 0;

        for (int step = 0; step < n; step++) {
            int turn = (mask >> step) & 1; // 0=CW, 1=CCW
            if (turn == 0) { // CW
                int chord = (facing + 4) % 5;
                c[chord]++;
                facing = (facing + 4) % 5;
            } else { // CCW
                c[facing]++;
                facing = (facing + 1) % 5;
            }
        }

        int target = n / 5;
        if (c[0] == target && c[1] == target && c[2] == target && 
            c[3] == target && c[4] == target) {
            ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}
