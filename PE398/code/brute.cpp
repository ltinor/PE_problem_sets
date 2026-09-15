#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// Brute: Monte Carlo estimation of E(n,m) — second shortest segment
// Choose m-1 distinct cut points uniformly from {1,...,n-1}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n, m; cin >> n >> m;
    
    if (m < 2) { cout << fixed << setprecision(5) << 0.0 << "\n"; return 0; }
    if (m == 2) {
        // Only one cut, two segments. E = expected shorter segment.
        // Cut at x ∈ [1,n-1], segments: x and n-x.
        // Second-shortest = min(x, n-x), expected value = n/4
        cout << fixed << setprecision(5) << n / 4.0 << "\n";
        return 0;
    }
    
    // Monte Carlo
    const int trials = 200000;
    double total = 0;
    vector<int> cuts(m-1);
    vector<int> segs(m);
    
    for (int t = 0; t < trials; t++) {
        // Reservoir sampling to pick m-1 distinct cuts from 1..n-1
        // Simple approach for small m, large n: use set
        set<int> used;
        while ((int)used.size() < m-1) {
            used.insert(1 + (rand() % (n-1)));
        }
        int idx = 0;
        for (int x : used) cuts[idx++] = x;
        sort(cuts.begin(), cuts.end());
        
        int prev = 0;
        for (int i = 0; i < m-1; i++) {
            segs[i] = cuts[i] - prev;
            prev = cuts[i];
        }
        segs[m-1] = n - prev;
        sort(segs.begin(), segs.end());
        total += segs[1]; // second shortest
    }
    cout << fixed << setprecision(5) << total / trials << "\n";
}
