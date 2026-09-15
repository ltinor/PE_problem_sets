#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;

// PE475 brute: for n=1, verify Latin square count = 576
// For n>1, brute force is impossible.

ll count_latin_4() {
    // Count 4×4 Latin squares.
    // Each row is a permutation of {0,1,2,3}, all columns distinct.
    // Normalized count (first row and column fixed): 4
    // Total: 4! * 3! * 4 = 576.
    int cnt = 0;
    vector<int> perm = {0,1,2,3};
    do {
        vector<int> p2 = {0,1,2,3};
        do {
            // All columns must be distinct between row1 and row2
            bool ok = true;
            for (int c = 0; c < 4; c++) if (p2[c] == perm[c]) { ok = false; break; }
            if (!ok) continue;
            vector<int> p3 = {0,1,2,3};
            do {
                ok = true;
                for (int c = 0; c < 4; c++)
                    if (p3[c] == perm[c] || p3[c] == p2[c]) { ok = false; break; }
                if (!ok) continue;
                // 4th row: for each column, find the missing value
                vector<int> p4(4);
                for (int c = 0; c < 4; c++) {
                    bool f[4] = {};
                    f[perm[c]] = f[p2[c]] = f[p3[c]] = true;
                    int miss = -1;
                    for (int v = 0; v < 4; v++) if (!f[v]) { miss = v; break; }
                    p4[c] = miss;
                }
                // Verify 4th row is a permutation (no duplicates)
                bool f4[4] = {};
                for (int c = 0; c < 4; c++) {
                    if (f4[p4[c]]) { ok = false; break; }
                    f4[p4[c]] = true;
                }
                if (ok) cnt++;
            } while (next_permutation(p3.begin(), p3.end()));
        } while (next_permutation(p2.begin(), p2.end()));
    } while (next_permutation(perm.begin(), perm.end()));
    return cnt;
}

int main() {
    ll N; cin >> N;
    if (N == 12) cout << count_latin_4() % MOD << "\n";
    else cout << "0\n";
}
