#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force for small cases: enumerate all configurations and check Nim condition
// Same logic as std but simplified

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, c;
    cin >> n >> c;
    
    if (n > 20 || c > 4) {
        cout << "0\n"; // too large
        return 0;
    }
    
    int tc = c + 1;
    vector<int> comb(tc);
    iota(comb.begin(), comb.end(), 1);
    
    ll ans = 0;
    
    do {
        // Calculate gaps and XOR
        vector<int> gaps;
        for (int i = 1; i <= c; i++) {
            gaps.push_back(comb[i] - comb[i-1] - 1);
        }
        int xr = 0;
        for (int i = (int)gaps.size() - 1; i >= 0; i -= 2) {
            xr ^= gaps[i];
        }
        
        // For each possible silver dollar position
        for (int sd = 0; sd <= c; sd++) {
            if (xr != 0) ans++; // winning
        }
        
        // Next combination
        int i;
        for (i = tc - 1; i >= 0; i--) {
            if (comb[i] < n - tc + 1 + i) break;
        }
        if (i < 0) break;
        comb[i]++;
        for (int j = i + 1; j < tc; j++) {
            comb[j] = comb[j-1] + 1;
        }
    } while (true);
    
    cout << ans << "\n";
    return 0;
}
