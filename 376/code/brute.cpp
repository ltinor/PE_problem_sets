#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: enumerate all dice and all triples directly O(D^3)
// Works only for very small N

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    // Generate all dice
    vector<vector<int>> dice;
    vector<int> cur(6);
    function<void(int,int)> dfs = [&](int pos, int start) {
        if (pos == 6) {
            dice.push_back(cur);
            return;
        }
        for (int v = start; v <= N; v++) {
            cur[pos] = v;
            dfs(pos + 1, v);
        }
    };
    dfs(0, 1);
    
    int D = dice.size();
    // Direct: check all triples
    ll ans = 0;
    for (int a = 0; a < D; a++) {
        for (int b = 0; b < D; b++) {
            if (a == b) continue;
            // check a beats b
            int wins_ab = 0;
            for (int i = 0; i < 6; i++)
                for (int j = 0; j < 6; j++)
                    if (dice[a][i] > dice[b][j]) wins_ab++;
            if (wins_ab <= 18) continue;
            
            for (int c = 0; c < D; c++) {
                if (c == a || c == b) continue;
                // b beats c
                int wins_bc = 0;
                for (int i = 0; i < 6; i++)
                    for (int j = 0; j < 6; j++)
                        if (dice[b][i] > dice[c][j]) wins_bc++;
                if (wins_bc <= 18) continue;
                
                // c beats a
                int wins_ca = 0;
                for (int i = 0; i < 6; i++)
                    for (int j = 0; j < 6; j++)
                        if (dice[c][i] > dice[a][j]) wins_ca++;
                if (wins_ca > 18) ans++;
            }
        }
    }
    // Each set {A,B,C} counted 6 times (3! permutations)
    cout << ans / 6 << "\n";
    return 0;
}
