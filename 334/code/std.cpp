#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE334: Spilling the Beans
// Game: remove 2 from bowl i, add 1 to i-1 and i+1
// Ends when all bowls have 0 or 1 bean
//
// Key insight: total beans and center of mass are conserved.
// Each operation increases sum(i^2 * b_i) by 2.
// We can simulate greedily: scan left to right, firing when b[i] >= 2.
// Since firing at i adds to i-1, we backtrack when needed.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll t0, C;
    int k, M;
    cin >> t0 >> C >> k >> M;
    
    // Generate b sequence
    vector<ll> b(M + 2, 0); // 1-indexed, with padding
    ll mod = 1LL << k;
    ll t = t0;
    
    for (int i = 1; i <= M; i++) {
        // t_i depends on t_{i-1}
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
    int i = 1;
    
    while (i <= M) {
        if (b[i] >= 2) {
            ll k_ops = b[i] / 2;
            b[i] -= 2 * k_ops;
            b[i - 1] += k_ops;
            b[i + 1] += k_ops;
            moves += k_ops;
            
            // Backtrack if left neighbor now has >= 2
            if (i > 1 && b[i - 1] >= 2) {
                i--;
            }
        } else {
            i++;
        }
    }
    
    cout << moves << "\n";
    
    return 0;
}
