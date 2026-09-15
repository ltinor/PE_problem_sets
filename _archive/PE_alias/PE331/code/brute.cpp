#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE331 brute: BFS over all 2^(N*N) states for small N

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    ll lo = (ll)(N-1)*(N-1);
    ll hi = (ll)N*N;
    
    // Build initial state as bitmask
    int init = 0;
    int n2 = N*N;
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            ll d2 = (ll)x*x + (ll)y*y;
            if (d2 >= lo && d2 < hi) {
                init |= (1 << (x * N + y));
            }
        }
    }
    
    if (init == 0) {
        cout << "0\n";
        return 0;
    }
    
    // Precompute effect of each move
    vector<int> move_effect(n2, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int mask = 0;
            for (int r = 0; r < N; r++) {
                for (int c = 0; c < N; c++) {
                    if (r == i || c == j) {
                        mask |= (1 << (r * N + c));
                    }
                }
            }
            move_effect[i * N + j] = mask;
        }
    }
    
    // BFS
    int total_states = 1 << n2;
    vector<int> dist(total_states, -1);
    queue<int> q;
    
    dist[init] = 0;
    q.push(init);
    
    while (!q.empty()) {
        int state = q.front(); q.pop();
        
        if (state == 0) {
            cout << dist[state] << "\n";
            return 0;
        }
        
        for (int m = 0; m < n2; m++) {
            int nxt = state ^ move_effect[m];
            if (dist[nxt] == -1) {
                dist[nxt] = dist[state] + 1;
                q.push(nxt);
            }
        }
    }
    
    // Unreachable
    cout << "0\n";
    return 0;
}
