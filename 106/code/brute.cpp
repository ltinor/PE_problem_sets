#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: enumerate all equal-size non-empty disjoint subset pairs
// and check if they need testing for equality (rule 1).

int n;
ll ans = 0;

// Check if sorted B and C of equal size need testing for rule 1.
// They don't need testing if all elements of B are less than
// corresponding elements of C (or vice versa).
bool needs_test(const vector<int>& B, const vector<int>& C) {
    // B and C are already sorted subsets of indices
    int k = B.size();
    // Check if B[i] < C[i] for all i
    bool all_less = true, all_greater = true;
    for (int i = 0; i < k; i++) {
        if (B[i] >= C[i]) all_less = false;
        if (B[i] <= C[i]) all_greater = false;
    }
    return !(all_less || all_greater);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // Enumerate all subsets via bitmasks
    int total = 1 << n;
    // For each unordered pair of disjoint equal-size subsets
    for (int maskB = 1; maskB < total; maskB++) {
        int szB = __builtin_popcount(maskB);
        // C must be disjoint from B and same size
        int avail = ((1 << n) - 1) ^ maskB;
        for (int maskC = maskB + 1; maskC < total; maskC++) {
            if (maskC & maskB) continue;
            int szC = __builtin_popcount(maskC);
            if (szC != szB) continue;
            // Build sorted lists
            vector<int> B, C;
            for (int i = 0; i < n; i++) {
                if (maskB & (1 << i)) B.push_back(i);
                if (maskC & (1 << i)) C.push_back(i);
            }
            if (needs_test(B, C)) ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}
