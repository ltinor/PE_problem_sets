#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: enumerate all step numbers via DFS
// A step number has each pair of consecutive digits differ by 1
// For D-digit numbers: at most 9 * 2^(D-1) possibilities
// Works for D up to ~20

ll total = 0;
int target_D;
int full_mask = 1023;

void dfs(int pos, int last, int mask, int D) {
    if (pos == D) {
        if (mask == full_mask) total++;
        return;
    }
    if (last > 0) dfs(pos + 1, last - 1, mask | (1 << (last - 1)), D);
    if (last < 9) dfs(pos + 1, last + 1, mask | (1 << (last + 1)), D);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;
    cin >> D;

    if (D < 1 || D > 40) return 1;

    total = 0;
    // For each length from 10 to D (minimum for pandigital is at least 10)
    for (int len = 10; len <= D; len++) {
        // Start with digits 1-9 (no leading zero)
        for (int d = 1; d <= 9; d++) {
            dfs(1, d, 1 << d, len);
        }
    }

    cout << total << "\n";
    return 0;
}
