#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 100000007LL;

// All valid centaur non-attacking constraints precomputed
// vertical_ok[s1][s2] = true if s1 in top block doesn't attack s2 in bottom block
// horiz_ok[s1][s2] = true if s1 doesn't attack s2 in block to the right (same row)  
// diag_ok[s1][s2] = true if s1 doesn't attack s2 in block diagonally down-right

bool attacks(int s1, int s2, int dr, int dc) {
    int r1 = s1 >> 1, c1 = s1 & 1;
    int r2 = s2 >> 1, c2 = s2 & 1;
    int adr = abs(2*dr + r2 - r1), adc = abs(2*dc + c2 - c1);
    if (adr <= 1 && adc <= 1 && (adr > 0 || adc > 0)) return true;
    if ((adr == 1 && adc == 2) || (adr == 2 && adc == 1)) return true;
    return false;
}

bool horiz_ok[4][4], vert_ok[4][4], diag_ok[4][4], diag2_ok[4][4];

void precompute() {
    for (int s1 = 0; s1 < 4; s1++) {
        for (int s2 = 0; s2 < 4; s2++) {
            horiz_ok[s1][s2] = !attacks(s1, s2, 0, 1);
            vert_ok[s1][s2] = !attacks(s1, s2, 1, 0);
            diag_ok[s1][s2] = !attacks(s1, s2, 1, 1);
            diag2_ok[s1][s2] = !attacks(s1, s2, 1, -1);
        }
    }
}

// DFA transitions for a row (row_self_ok):
// 0→{0,1,3}, 1→{1}, 2→{1,2,3}, 3→{3}
// Encoding: a row is represented by its starting state and the position of the "change"
// Actually, let's encode a row as a sequence of states using the DFA.
// The number of valid rows of length n is 4n.

// For the DP, we need to know, for each column c, what state the top and bottom rows have.
// The compatibility between two rows depends on all column pairs.

// Since valid rows are very constrained (DFA), let's directly enumerate 
// the valid row states and precompute the transfer matrix.

// Generate all valid row states for a given n
vector<int> gen_rows(int n) {
    vector<int> rows;
    // Generate based on starting state
    
    // Start 0: sequence is some number of 0s, then optionally 1s or 3s
    for (int split = 0; split <= n; split++) {
        // split = number of initial 0s
        // After 0s: can transition to 1 or 3
        // If transition to 1: rest is all 1s
        // If transition to 3: rest is all 3s
        // Also: can stay all 0s (split=n)
        
        // All 0s (split=n, no transition)
        if (split == n) {
            int h = 0;
            rows.push_back(h);
            continue;
        }
        
        // Transition to 1 at position split
        {
            int h = 0;
            for (int i = 0; i < n; i++) {
                int state = (i < split) ? 0 : 1;
                h = h * 4 + state;
            }
            rows.push_back(h);
        }
        
        // Transition to 3 at position split
        {
            int h = 0;
            for (int i = 0; i < n; i++) {
                int state = (i < split) ? 0 : 3;
                h = h * 4 + state;
            }
            rows.push_back(h);
        }
    }
    
    // Start 1: all 1s
    {
        int h = 0;
        for (int i = 0; i < n; i++) h = h * 4 + 1;
        rows.push_back(h);
    }
    
    // Start 2: sequence is some number of 2s, then optionally 1s or 3s
    for (int split = 0; split <= n; split++) {
        if (split == n) {
            int h = 0;
            for (int i = 0; i < n; i++) h = h * 4 + 2;
            rows.push_back(h);
            continue;
        }
        
        // Transition to 1 at position split
        {
            int h = 0;
            for (int i = 0; i < n; i++) {
                int state = (i < split) ? 2 : 1;
                h = h * 4 + state;
            }
            rows.push_back(h);
        }
        
        // Transition to 3 at position split
        {
            int h = 0;
            for (int i = 0; i < n; i++) {
                int state = (i < split) ? 2 : 3;
                h = h * 4 + state;
            }
            rows.push_back(h);
        }
    }
    
    // Start 3: all 3s
    {
        int h = 0;
        for (int i = 0; i < n; i++) h = h * 4 + 3;
        rows.push_back(h);
    }
    
    // Deduplicate
    sort(rows.begin(), rows.end());
    rows.erase(unique(rows.begin(), rows.end()), rows.end());
    
    return rows;
}

// Check if two rows are vertically compatible
bool row_compat(int h1, int h2, int n) {
    vector<int> r1(n), r2(n);
    for (int i = n-1; i >= 0; i--) { r1[i] = h1 % 4; h1 /= 4; }
    for (int i = n-1; i >= 0; i--) { r2[i] = h2 % 4; h2 /= 4; }
    
    for (int c = 0; c < n; c++) {
        // Vertical
        if (!vert_ok[r1[c]][r2[c]]) return false;
        // Diagonal: c with c+1 (down-right)
        if (c+1 < n && !diag_ok[r1[c]][r2[c+1]]) return false;
        // Diagonal: c+1 with c (down-left)
        if (c+1 < n && !diag2_ok[r1[c+1]][r2[c]]) return false;
    }
    return true;
}

ll C_n(int n) {
    auto rows = gen_rows(n);
    int V = rows.size();
    
    // Build transfer matrix
    vector<vector<int>> compat(V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (row_compat(rows[i], rows[j], n)) {
                compat[i].push_back(j);
            }
        }
    }
    
    vector<ll> dp(V, 1);
    for (int r = 1; r < n; r++) {
        vector<ll> ndp(V, 0);
        for (int i = 0; i < V; i++) {
            if (dp[i] == 0) continue;
            for (int j : compat[i]) {
                ndp[j] += dp[i];
            }
        }
        dp.swap(ndp);
    }
    
    ll total = 0;
    for (ll v : dp) total += v;
    return total;
}

int main() {
    precompute();
    for (int n = 1; n <= 12; n++) {
        cout << "C(" << n << ") = " << C_n(n) << endl;
    }
    return 0;
}
