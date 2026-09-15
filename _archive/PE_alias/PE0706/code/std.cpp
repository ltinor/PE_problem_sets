#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1000000007;
const int D = 100000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Use long long to avoid overflow during accumulation
    static ll dp[3][3][3][3] = {};
    static ll ndp[3][3][3][3] = {};
    
    for (int d = 1; d <= 9; d++) {
        int p = d % 3;
        int cnt[3] = {1, 0, 0};
        cnt[p]++;
        dp[p][cnt[0]%3][cnt[1]%3][cnt[2]%3]++;
    }
    
    for (int i = 1; i < D; i++) {
        memset(ndp, 0, sizeof(ndp));
        for (int p = 0; p < 3; p++) {
            for (int a = 0; a < 3; a++) {
                for (int b = 0; b < 3; b++) {
                    for (int c = 0; c < 3; c++) {
                        ll cur = dp[p][a][b][c];
                        if (cur == 0) continue;
                        for (int d = 0; d <= 9; d++) {
                            int np = (p + d) % 3;
                            int na = a, nb = b, nc = c;
                            if (np == 0) na = (na + 1) % 3;
                            else if (np == 1) nb = (nb + 1) % 3;
                            else nc = (nc + 1) % 3;
                            ndp[np][na][nb][nc] = (ndp[np][na][nb][nc] + cur) % MOD;
                        }
                    }
                }
            }
        }
        memcpy(dp, ndp, sizeof(dp));
    }
    
    ll ans = 0;
    for (int p = 0; p < 3; p++) {
        for (int a = 0; a < 3; a++) {
            for (int b = 0; b < 3; b++) {
                for (int c = 0; c < 3; c++) {
                    int cnt = (a == 2) + (b == 2) + (c == 2);
                    if (cnt % 3 == 0) {
                        ans = (ans + dp[p][a][b][c]) % MOD;
                    }
                }
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}
