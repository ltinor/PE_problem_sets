// PE 371 - Licence Plates (Oregon)
// Plates: 3 letters + 3-digit number (000-999).
// Win when two seen plates' numbers sum to 1000.
// Expected number of plates to see. PE: 7278014883470655 (encoded), ≈ 40.66368073
//
// Approach: Markov chain DP.
// State (a, b, self) where:
//   a = # non-self pairs where only first element seen
//   b = # non-self pairs where only second element seen
//   n = 499-a-b unseen pairs
//   self = 0/1 for whether 500 has been seen
// Non-self pairs: {1,999}, {2,998}, ..., {499,501}
// Self-pair: {500,500}
// Free: {0}
//
// Transitions from (a,b,self):
// - Win immediately: prob (a+b+self)/1000
// - Safe stay: prob (a+b+1)/1000 (draw a's again, b's again, or 0)
// - New first of pair: prob n/1000 → (a+1,b,self)
// - New second of pair: prob n/1000 → (a,b+1,self)
// - First 500: prob 1/1000 → (a,b,1) if self=0
//
// E[a][b][self] = expected ADDITIONAL draws from this state.
// Solve by DP from high a+b down to 0.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int PAIRS = 499; // non-self pairs
    const int N = 1000;

    // E[a][b][self]
    // Use vector of vectors indexed by a+b and then by 'a'
    // Total states: (PAIRS+1)*(PAIRS+2)/2 * 2 ≈ 250K
    // Store as map or 2D array indexed by (a, total = a+b)
    
    // We'll use a 2D array: E[a][total][self]
    // total ranges from 0 to PAIRS, a from 0 to total
    static double E[500][500][2];
    
    // Initialize all to 0
    memset(E, 0, sizeof(E));
    
    // Process total = a+b from PAIRS down to 0
    for (int total = PAIRS; total >= 0; total--) {
        int n = PAIRS - total;
        
        for (int a = 0; a <= total; a++) {
            int b = total - a;
            
            for (int self = 1; self >= 0; self--) {
                // E[a][b][self] satisfies:
                // E*(1 - (a+b+1)/N) = 1 + n/N*(E[a+1][b][self] + E[a][b+1][self])
                //                        + [self==0]/N * E[a][b][1]
                // denominator: 1 - (a+b+1)/N = (N - a - b - 1)/N
                
                double num = 1.0;
                
                // New first
                if (n > 0) num += (double)n / N * E[a+1][total+1][self];
                
                // New second
                if (n > 0) num += (double)n / N * E[a][total+1][self];
                
                // First 500
                if (self == 0) num += 1.0 / N * E[a][total][1];
                
                double denom = (double)(N - a - b - 1) / N;
                E[a][total][self] = num / denom;
            }
        }
    }
    
    double expected = E[0][0][0];
    
    // Output with 8 decimal places
    cout << fixed << setprecision(8) << expected << "\n";
    
    return 0;
}
