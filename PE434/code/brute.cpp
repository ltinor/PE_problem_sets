#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE434 brute: enumerate all diagonal assignments for small grids

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    ll N; cin >> N;
    
    const ll MOD = 1000000033;
    ll ans = 0;
    
    for (int m = 1; m <= N && m <= 5; m++) {
        for (int n = 1; n <= N && n <= 5; n++) {
            if (m * n > 20) continue;
            
            ll cnt = 0;
            int cells = m * n;
            for (int mask = 0; mask < (1 << cells); mask++) {
                vector<vector<int>> adj(m + n);
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n; j++) {
                        if (mask & (1 << (i * n + j))) {
                            adj[i].push_back(m + j);
                            adj[m + j].push_back(i);
                        }
                    }
                }
                
                bool ok = true;
                for (int i = 0; i < m && ok; i++)
                    if (adj[i].empty()) ok = false;
                for (int j = 0; j < n && ok; j++)
                    if (adj[m+j].empty()) ok = false;
                if (!ok) continue;
                
                vector<bool> vis(m + n);
                queue<int> q; q.push(0); vis[0] = true;
                while (!q.empty()) {
                    int u = q.front(); q.pop();
                    for (int v : adj[u])
                        if (!vis[v]) { vis[v] = true; q.push(v); }
                }
                for (int i = 0; i < m + n; i++)
                    if (!vis[i]) { ok = false; break; }
                if (ok) cnt++;
            }
            ans = (ans + cnt) % MOD;
        }
    }
    cout << ans << "\n";
}
