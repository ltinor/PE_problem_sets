#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: compute Grundy and triple-nested loop (only for small N)
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> g(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        vector<bool> seen(N + 2, false);
        for (int j = 1; j * j <= i; j++) {
            seen[g[i - j * j]] = true;
        }
        int mex = 0;
        while (seen[mex]) mex++;
        g[i] = mex;
    }

    ll ans = 0;
    for (int a = 0; a <= N; a++) {
        for (int b = a; b <= N; b++) {
            for (int c = b; c <= N; c++) {
                if ((g[a] ^ g[b] ^ g[c]) == 0) {
                    ans++;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
