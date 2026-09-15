#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: enumerate all colorings for very small m,n
// Limit: m*n ≤ 6 for manageable enumeration

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll T;
    cin >> T;
    
    ll ans = 0;
    
    for (ll m = 2; m <= 4; m++) {
        for (ll n = 1; m * n <= 6; n++) {
            ll mn = m * n;
            
            // Generate all arrangements via backtracking
            vector<int> arr(mn);
            vector<int> cnt(m, 0);
            set<string> seen;
            
            function<void(int)> dfs = [&](int pos) {
                if (pos == mn) {
                    // Check if each color appears exactly n times
                    bool ok = true;
                    for (int i = 0; i < m; i++) if (cnt[i] != n) { ok = false; break; }
                    if (!ok) return;
                    
                    // Find canonical representation (minimal among rotations)
                    string best(mn, ' ');
                    for (int rot = 0; rot < mn; rot++) {
                        string s;
                        for (int i = 0; i < mn; i++)
                            s += (char)('0' + arr[(rot + i) % mn]);
                        if (best[0] == ' ' || s < best) best = s;
                    }
                    seen.insert(best);
                    return;
                }
                for (int c = 0; c < m; c++) {
                    if (cnt[c] < n) {
                        arr[pos] = c;
                        cnt[c]++;
                        dfs(pos + 1);
                        cnt[c]--;
                    }
                }
            };
            dfs(0);
            
            ll val = seen.size();
            if (val <= T) ans += val;
        }
    }
    
    cout << ans << "\n";
}
