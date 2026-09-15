#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE334 brute: simulate one operation at a time
// Always fire at the leftmost bowl with >= 2 beans

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll t0, C;
    int k, M;
    cin >> t0 >> C >> k >> M;
    
    vector<ll> b(M + 2, 0);
    ll mod = 1LL << k;
    ll t = t0;
    
    for (int i = 1; i <= M; i++) {
        if (i > 1) {
            if (t % 2 == 0) {
                t = t / 2;
            } else {
                t = (t / 2) ^ C;
            }
        }
        b[i] = (t % mod) + 1;
    }
    
    ll moves = 0;
    
    while (true) {
        // Find first bowl with >= 2 beans
        int pos = -1;
        for (int i = 1; i <= M; i++) {
            if (b[i] >= 2) {
                pos = i;
                break;
            }
        }
        if (pos == -1) {
            // Also check boundaries (b[0], b[M+1]) — they may have beans but don't need to be fired
            // Actually, we need to fire at boundaries too if beans flow there
            if (b[0] >= 2) pos = 0;
            else if (b[M+1] >= 2) pos = M+1;
        }
        if (pos == -1) break;
        
        b[pos] -= 2;
        if (pos > 0) b[pos-1] += 1;
        b[pos+1] += 1;
        moves++;
    }
    
    cout << moves << "\n";
    
    return 0;
}
