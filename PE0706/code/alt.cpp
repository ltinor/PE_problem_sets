#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1000000007;
const int D = 100000;

// Alternative DP: track (p, cnt[0]%3, cnt[1]%3, cnt[2]%3, f%3)
// f_new = f_old + cnt[new_p] (before increment)
// We want f%3 == 0 at the end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    static ll dp[3][3][3][3][3] = {}; // [p][a][b][c][fmod]
    static ll ndp[3][3][3][3][3] = {};
    
    for (int d = 1; d <= 9; d++) {
        int p = d % 3;
        int cnt[3] = {1, 0, 0};
        // f starts at 0, after first digit:
        // f = old_f + cnt[p] = 0 + cnt[p](before) = 0 + (p==0 ? 1 : 0)
        int fmod = (p == 0) ? 1 : 0; // 1 mod 3
        cnt[p]++;
        dp[p][cnt[0]%3][cnt[1]%3][cnt[2]%3][fmod]++;
    }
    
    for (int i = 1; i < D; i++) {
        memset(ndp, 0, sizeof(ndp));
        for (int p = 0; p < 3; p++) {
            for (int a = 0; a < 3; a++) {
                for (int b = 0; b < 3; b++) {
                    for (int c = 0; c < 3; c++) {
                        for (int fm = 0; fm < 3; fm++) {
                            ll cur = dp[p][a][b][c][fm];
                            if (cur == 0) continue;
                            for (int d = 0; d <= 9; d++) {
                                int np = (p + d) % 3;
                                int na = a, nb = b, nc = c;
                                int cnt_before; // cnt[np] before increment
                                if (np == 0) { cnt_before = a; na = (na + 1) % 3; }
                                else if (np == 1) { cnt_before = b; nb = (nb + 1) % 3; }
                                else { cnt_before = c; nc = (nc + 1) % 3; }
                                
                                // cnt_before is the mod-3 value, but we need the ACTUAL
                                // count mod 3 for the f update. The f update uses
                                // f_new = (f_old + actual_cnt[np]_before) mod 3
                                // The actual value of cnt[np] before increment:
                                // it is the count whose mod-3 is cnt_before.
                                // Since C(cnt,2) mod 3 = (cnt%3==2), we can compute:
                                // If cnt_before = 0: actual cnt = 0,3,6,... -> cnt mod 3 = 0
                                // If cnt_before = 1: actual cnt = 1,4,7,... -> cnt mod 3 = 1
                                // If cnt_before = 2: actual cnt = 2,5,8,... -> cnt mod 3 = 2
                                // The f update: f_new mod 3 = (fm + cnt_before) mod 3
                                int nfm = (fm + cnt_before) % 3;
                                
                                ndp[np][na][nb][nc][nfm] = (ndp[np][na][nb][nc][nfm] + cur) % MOD;
                            }
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
                    ans = (ans + dp[p][a][b][c][0]) % MOD; // f%3 == 0
                }
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}
