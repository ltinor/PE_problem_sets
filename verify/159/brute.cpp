#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: same DP approach, for verification

int dr(ll n) {
    if (n == 0) return 0;
    return 1 + (n - 1) % 9;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> mdrs(N + 1, 0);
    ll total = 0;

    for (int i = 2; i <= N; i++) {
        int best = dr(i);
        for (int d = 2; d * d <= i; d++) {
            if (i % d == 0) {
                int d2 = i / d;
                best = max(best, dr(d) + mdrs[d2]);
                best = max(best, dr(d2) + mdrs[d]);
            }
        }
        mdrs[i] = best;
        total += best;
    }

    cout << total << "\n";
    return 0;
}
