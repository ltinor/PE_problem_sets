#include<bits/stdc++.h>
using namespace std;

int mygcd(int a, int b) {
    while (b) { int t = b; b = a % b; a = t; }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    vector<int> cnt(M + 1, 0);

    // Generate primitive Pythagorean triples
    for (int m = 2; m * m <= M; m++) {
        for (int n = 1; n < m; n++) {
            if ((m - n) % 2 == 0) continue;
            if (mygcd(m, n) != 1) continue;

            int a = m * m - n * n;
            int b = 2 * m * n;
            int c = m * m + n * n;
            int p = a + b + c;

            for (int k = 1; k * p <= M; k++) {
                cnt[k * p]++;
            }
        }
    }

    int ans = 0;
    for (int L = 1; L <= M; L++) {
        if (cnt[L] == 1) ans++;
    }

    cout << ans << "\n";
    return 0;
}
