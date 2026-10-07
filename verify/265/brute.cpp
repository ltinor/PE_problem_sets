#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

// Brute force: generate all 2^(2^N) binary sequences and check
// Only feasible for N=3

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    int L = 1 << N;
    
    ull total = 0;
    
    // For N <= 3, brute force over all possible sequences
    if (N <= 3) {
        ull max_val = 1ULL << L;
        for (ull bits = 0; bits < max_val; bits++) {
            // Check: first N bits must be 0 (encoding rule)
            if ((bits >> (L - N)) != 0) continue;
            
            // Extract all N-bit windows
            vector<int> windows;
            for (int i = 0; i < L; i++) {
                int w = 0;
                for (int j = 0; j < N; j++) {
                    int pos = (i + j) % L;
                    w = (w << 1) | ((bits >> (L - 1 - pos)) & 1);
                }
                windows.push_back(w);
            }
            
            // Check all windows distinct
            sort(windows.begin(), windows.end());
            bool ok = true;
            for (int i = 1; i < L; i++) {
                if (windows[i] == windows[i-1]) { ok = false; break; }
            }
            
            if (ok) total += bits;
        }
    } else {
        // For N > 3, use same DFS as std but simpler (for verification)
        // This is essentially the same algorithm
        vector<int> seq(L, 0);
        vector<bool> seen(1 << N, false);
        seen[0] = true;
        
        function<void(int,int)> dfs = [&](int pos, int last) {
            if (pos == L) {
                // Check all N-1 wrapping windows
                bool valid = true;
                for (int w = 1; w < N; w++) {
                    int win = 0;
                    for (int i = L - N + w; i < L; i++)
                        win = (win << 1) | seq[i];
                    for (int i = 0; i < w; i++)
                        win = (win << 1) | seq[i];
                    if (seen[win]) { valid = false; break; }
                }
                if (valid) {
                    ull val = 0;
                    for (int i = 0; i < L; i++) val = (val << 1) | seq[i];
                    total += val;
                }
                return;
            }
            int mask = (1 << N) - 1;
            for (int bit = 0; bit < 2; bit++) {
                int np = ((last << 1) & mask) | bit;
                if (!seen[np]) {
                    seen[np] = true;
                    seq[pos] = bit;
                    dfs(pos + 1, np);
                    seen[np] = false;
                }
            }
        };
        
        dfs(N, 0);
    }
    
    cout << total << "\n";
    return 0;
}
