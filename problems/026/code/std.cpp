#include<bits/stdc++.h>
using namespace std;

// Find d < N that gives the longest recurring cycle in 1/d
pair<int,int> solve(int N) {
    int best_d = 0, best_len = 0;

    for (int d = 2; d < N; d++) {
        // Remove factors of 2 and 5 (these don't affect cycle length)
        int n = d;
        while (n % 2 == 0) n /= 2;
        while (n % 5 == 0) n /= 5;

        if (n == 1) continue; // terminating decimal

        // Simulate long division to find cycle length
        // The cycle length is the multiplicative order of 10 modulo n
        int remainder = 1 % n;
        vector<int> pos(n, -1);
        pos[remainder] = 0;
        int len = 0;

        while (true) {
            remainder = (remainder * 10) % n;
            len++;
            if (pos[remainder] != -1) {
                len = len - pos[remainder];
                break;
            }
            pos[remainder] = len;
        }

        if (len > best_len) {
            best_len = len;
            best_d = d;
        }
    }

    return {best_d, best_len};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        auto ans = solve(N);
        cout << ans.first << " " << ans.second << "\n";
    }
}
