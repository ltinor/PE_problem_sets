#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N; // max heap size

    // Compute Grundy numbers
    vector<int> g(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        // Find all reachable states
        vector<bool> seen(N + 2, false);
        for (int j = 1; j * j <= i; j++) {
            int sq = j * j;
            seen[g[i - sq]] = true;
        }
        int mex = 0;
        while (seen[mex]) mex++;
        g[i] = mex;
    }

    // Count losing positions: g[a] ^ g[b] ^ g[c] == 0, a ≤ b ≤ c
    // Enumerate a, b first, then a^b gives target c-Grundy
    ll ans = 0;

    // Count frequencies of Grundy values
    vector<int> freq(N + 1, 0);
    for (int i = 0; i <= N; i++) {
        freq[g[i]]++;
    }

    // Enumerate a and b, compute needed c-Grundy
    // For each (a,b) with a ≤ b ≤ N
    // Need g[c] = g[a] ^ g[b], and c ≥ b
    for (int a = 0; a <= N; a++) {
        for (int b = a; b <= N; b++) {
            int target = g[a] ^ g[b];
            // Count c in [b, N] with g[c] = target
            // We can precompute prefix sums per Grundy value
        }
    }

    // Use prefix sums for efficiency
    int max_g = *max_element(g.begin(), g.end());
    vector<vector<int>> pref(max_g + 1, vector<int>(N + 2, 0));
    for (int v = 0; v <= max_g; v++) {
        for (int i = 0; i <= N; i++) {
            pref[v][i + 1] = pref[v][i] + (g[i] == v ? 1 : 0);
        }
    }

    for (int a = 0; a <= N; a++) {
        for (int b = a; b <= N; b++) {
            int target = g[a] ^ g[b];
            if (target > max_g) continue;
            // c must be in [b, N] with g[c] = target
            ans += pref[target][N + 1] - pref[target][b];
        }
    }

    cout << ans << "\n";
    return 0;
}
