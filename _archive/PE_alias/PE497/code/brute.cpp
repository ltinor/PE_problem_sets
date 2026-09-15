#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for PE497: Monte Carlo simulation for small n

int main() {
    string query;
    getline(cin, query);
    ll n = stoll(query);
    
    if (n > 3) {
        cout << "0\n";
        return 0;
    }
    
    // Monte Carlo
    int trials = 200000;
    ll total_steps = 0;
    
    for (int t = 0; t < trials; t++) {
        // State: position of each disk (0,1,2)
        vector<int> pos(n, 0);
        int steps = 0;
        while (true) {
            // Check if all disks on peg 2
            bool done = true;
            for (int i = 0; i < n; i++) if (pos[i] != 2) { done = false; break; }
            if (done) break;
            
            // Find legal moves
            vector<pair<int,int>> moves; // (disk, to_peg)
            int top[3] = {n, n, n};
            for (int i = 0; i < n; i++) {
                if (i < top[pos[i]]) top[pos[i]] = i;
            }
            for (int from = 0; from < 3; from++) {
                if (top[from] == n) continue;
                int disk = top[from];
                for (int to = 0; to < 3; to++) {
                    if (from == to) continue;
                    if (top[to] > disk) {
                        moves.push_back({disk, to});
                    }
                }
            }
            // Random legal move
            auto [disk, to] = moves[rand() % moves.size()];
            pos[disk] = to;
            steps++;
        }
        total_steps += steps;
    }
    
    cout << (total_steps / trials) << "\n";
}
