#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

int N, L; // L = 1 << N (sequence length)
vector<int> seq;      // the binary sequence
vector<bool> seen;    // which N-bit patterns have been used
ull total_sum = 0;

// Convert the sequence to its numeric encoding
ull encode() {
    ull val = 0;
    for (int i = 0; i < L; i++) {
        val = (val << 1) | seq[i];
    }
    return val;
}

// DFS: pos is the next position to fill (pos >= N)
void dfs(int pos, int last_pattern) {
    if (pos == L) {
        // Check all N-1 wrapping windows are unseen and distinct
        bool valid = true;
        for (int w = 1; w < N; w++) {
            int win = 0;
            // bits L-N+w to L-1 (from end)
            for (int i = L - N + w; i < L; i++)
                win = (win << 1) | seq[i];
            // bits 0 to w-1 (from beginning)
            for (int i = 0; i < w; i++)
                win = (win << 1) | seq[i];
            if (seen[win]) { valid = false; break; }
        }
        if (valid) {
            total_sum += encode();
        }
        return;
    }
    
    // The new pattern will be: (last_pattern << 1) & mask | new_bit
    int mask = (1 << N) - 1;
    
    for (int bit = 0; bit < 2; bit++) {
        int new_pattern = ((last_pattern << 1) & mask) | bit;
        if (!seen[new_pattern]) {
            seen[new_pattern] = true;
            seq[pos] = bit;
            dfs(pos + 1, new_pattern);
            seen[new_pattern] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    L = 1 << N;
    
    seq.assign(L, 0);
    seen.assign(1 << N, false);
    
    // First N bits are all zeros
    seen[0] = true;
    // Last N-1 bits must be zeros for circular condition
    // So seq[L-(N-1)] through seq[L-1] must be 0
    // We'll let DFS figure this out naturally
    
    dfs(N, 0);
    
    cout << total_sum << "\n";
    return 0;
}
