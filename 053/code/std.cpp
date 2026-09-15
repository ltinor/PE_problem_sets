#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 100;
long double C[MAXN + 1][MAXN + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute combinations using Pascal's triangle
    for (int n = 0; n <= MAXN; n++) {
        C[n][0] = C[n][n] = 1.0L;
        for (int r = 1; r < n; r++) {
            C[n][r] = C[n-1][r-1] + C[n-1][r];
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int N;
        ll threshold;
        cin >> N >> threshold;

        int ans = 0;
        for (int n = 1; n <= N; n++) {
            for (int r = 0; r <= n; r++) {
                if (C[n][r] > threshold) ans++;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
