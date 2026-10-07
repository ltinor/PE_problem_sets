#include <bits/stdc++.h>
using namespace std;

// Addition chain: BFS to find shortest chain to each k
// Start from {1}, each step pick two elements (can be same), add them
// Record first time each value is reached (depth = chain length)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    const int MAX_K = 200;
    vector<int> best(MAX_K + 1, INT_MAX);
    best[1] = 0; // m(1) = 0 (empty chain after 1)

    // BFS: queue of (current chain as bitmask + depth)
    // Use DFS with pruning instead
    // chain: sorted list of values in chain so far
    vector<int> chain = {1};
    
    function<void(int)> dfs = [&](int depth) {
        int last = chain.back();
        // Try all pairs including self
        for (int i = (int)chain.size() - 1; i >= 0; i--) {
            for (int j = i; j >= 0; j--) {
                int nxt = chain[i] + chain[j];
                if (nxt <= last) continue; // must be increasing
                if (nxt > MAX_K) continue;
                if (depth + 1 > best[nxt]) continue; // prune: worse path
                if (depth + 1 < best[nxt]) best[nxt] = depth + 1; // update only if better
                
                chain.push_back(nxt);
                dfs(depth + 1);
                chain.pop_back();
            }
        }
    };

    dfs(0);

    long long sum = 0;
    for (int k = 1; k <= K; k++) {
        sum += best[k];
    }
    cout << sum << "\n";
    return 0;
}
