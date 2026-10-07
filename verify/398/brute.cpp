#include<bits/stdc++.h>
using namespace std;
// Brute: Monte Carlo for E(n,m) - second shortest segment
int main() {
    int n, m; cin >> n >> m;
    int trials = 100000;
    double total = 0;
    srand(time(0));
    for (int t=0; t<trials; t++) {
        vector<int> cuts;
        // Pick m-1 distinct cut points from 1..n-1
        set<int> used;
        while ((int)used.size() < m-1) {
            used.insert(1 + rand()%(n-1));
        }
        for (int x : used) cuts.push_back(x);
        sort(cuts.begin(), cuts.end());
        // Compute segment lengths
        vector<int> segs;
        int prev = 0;
        for (int c : cuts) { segs.push_back(c-prev); prev = c; }
        segs.push_back(n-prev);
        sort(segs.begin(), segs.end());
        total += segs[1]; // second shortest
    }
    cout << fixed << setprecision(5) << total/trials << "\n";
}
