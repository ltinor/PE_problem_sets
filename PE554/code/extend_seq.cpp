#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

bool attacks(int s1, int s2, int dr, int dc) {
    int r1 = s1 >> 1, c1 = s1 & 1;
    int r2 = s2 >> 1, c2 = s2 & 1;
    int adr = abs(2*dr + r2 - r1), adc = abs(2*dc + c2 - c1);
    if (adr <= 1 && adc <= 1 && (adr > 0 || adc > 0)) return true;
    if ((adr == 1 && adc == 2) || (adr == 2 && adc == 1)) return true;
    return false;
}

bool vert_ok[4][4], diag_ok[4][4], diag2_ok[4][4];

void precompute() {
    for (int s1 = 0; s1 < 4; s1++) {
        for (int s2 = 0; s2 < 4; s2++) {
            vert_ok[s1][s2] = !attacks(s1, s2, 1, 0);
            diag_ok[s1][s2] = !attacks(s1, s2, 1, 1);
            diag2_ok[s1][s2] = !attacks(s1, s2, 1, -1);
        }
    }
}

vector<ll> gen_rows(int n) {
    vector<ll> rows;
    // Start 0
    for (int split = 0; split <= n; split++) {
        if (split == n) { ll h=0; rows.push_back(h); continue; }
        { ll h=0; for(int i=0;i<n;i++) h=h*4+(i<split?0:1); rows.push_back(h); }
        { ll h=0; for(int i=0;i<n;i++) h=h*4+(i<split?0:3); rows.push_back(h); }
    }
    // Start 1
    { ll h=0; for(int i=0;i<n;i++) h=h*4+1; rows.push_back(h); }
    // Start 2
    for (int split = 0; split <= n; split++) {
        if (split == n) { ll h=0; for(int i=0;i<n;i++) h=h*4+2; rows.push_back(h); continue; }
        { ll h=0; for(int i=0;i<n;i++) h=h*4+(i<split?2:1); rows.push_back(h); }
        { ll h=0; for(int i=0;i<n;i++) h=h*4+(i<split?2:3); rows.push_back(h); }
    }
    // Start 3
    { ll h=0; for(int i=0;i<n;i++) h=h*4+3; rows.push_back(h); }
    sort(rows.begin(), rows.end());
    rows.erase(unique(rows.begin(), rows.end()), rows.end());
    return rows;
}

bool row_compat(ll h1, ll h2, int n) {
    vector<int> r1(n), r2(n);
    for (int i = n-1; i >= 0; i--) { r1[i] = h1 % 4; h1 /= 4; }
    for (int i = n-1; i >= 0; i--) { r2[i] = h2 % 4; h2 /= 4; }
    for (int c = 0; c < n; c++) {
        if (!vert_ok[r1[c]][r2[c]]) return false;
        if (c+1 < n && !diag_ok[r1[c]][r2[c+1]]) return false;
        if (c+1 < n && !diag2_ok[r1[c+1]][r2[c]]) return false;
    }
    return true;
}

i128 C_n(int n) {
    auto rows = gen_rows(n);
    int V = rows.size();
    vector<vector<int>> compat(V);
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if (row_compat(rows[i], rows[j], n))
                compat[i].push_back(j);
    
    vector<i128> dp(V, 1);
    for (int r = 1; r < n; r++) {
        vector<i128> ndp(V, 0);
        for (int i = 0; i < V; i++) {
            if (dp[i] == 0) continue;
            for (int j : compat[i]) ndp[j] += dp[i];
        }
        dp.swap(ndp);
    }
    i128 total = 0;
    for (auto v : dp) total += v;
    return total;
}

int main() {
    precompute();
    double prev_val = 0;
    for (int n = 1; n <= 30; n++) {
        i128 c = C_n(n);
        cout << "C(" << n << ") = " << (ll)c;
        if (n > 1) cout << "  ratio=" << fixed << setprecision(10) << (double)(i128)c / prev_val;
        cout << endl;
        prev_val = (double)(i128)c;
    }
    return 0;
}
