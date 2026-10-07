#include <bits/stdc++.h>
using namespace std;

// Brute force: BFS level by level
// At each level, generate all possible sums from current set

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    const int MAX_K = 200;
    vector<int> best(MAX_K + 1, INT_MAX);
    best[1] = 0;

    // BFS: states represented as bitmask of reached values
    // For small K, we can just use set of values
    using State = pair<int, vector<int>>; // (depth, sorted values)
    
    queue<pair<int, vector<int>>> q;
    q.push({0, {1}});
    
    while (!q.empty()) {
        auto [depth, chain] = q.front(); q.pop();
        int sz = chain.size();
        
        for (int i = sz - 1; i >= 0; i--) {
            for (int j = i; j >= 0; j--) {
                int nxt = chain[i] + chain[j];
                if (nxt <= chain.back()) continue;
                if (nxt > MAX_K) continue;
                if (depth + 1 > best[nxt]) continue;
                if (depth + 1 < best[nxt]) best[nxt] = depth + 1;
                
                vector<int> nchain = chain;
                nchain.push_back(nxt);
                q.push({depth + 1, nchain});
            }
        }
    }

    long long sum = 0;
    for (int k = 1; k <= K; k++) {
        sum += best[k];
    }
    cout << sum << "\n";
    return 0;
}
