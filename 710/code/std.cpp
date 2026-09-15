#include <bits/stdc++.h>
using namespace std;
#define ll long long

// t(n) = P(n) - b(n)
// P(n) = 2^{floor(n/2)} mod 1e6
// b(n) = palindromic tuples with NO element = 2
// b(0) = 1
// b(n) = (n!=2) + b(n-2) + b(n-6) + b(n-8) + ...
// Let S(n) = sum_{k>=6 even, k<=n} b(n-k)
// S(n) = S(n-2) + b(n-6)
// b(n) = (n!=2) + b(n-2) + S(n)

const int MOD = 1000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // We need to find smallest n > 42 with t(n) % MOD == 0
    // t(n) grows exponentially, answer should be within a few thousand
    
    vector<int> b(500000, 0);
    b[0] = 1;
    
    vector<int> S(500000, 0); // S(n) = sum of b(n-6) + b(n-8) + ...
    
    int ans = -1;
    int p2 = 1; // powers of 2
    
    for (int n = 1; ans == -1; n++) {
        // Update S(n)
        S[n] = (n >= 2 ? S[n-2] : 0);
        if (n >= 6) S[n] = (S[n] + b[n-6]) % MOD;
        
        // Compute b(n)
        int val = (n != 2) ? 1 : 0;
        if (n >= 2) val = (val + b[n-2]) % MOD;
        val = (val + S[n]) % MOD;
        b[n] = val;
        
        // Update power of 2: p2 tracks 2^{floor(n/2)} mod MOD
        if (n % 2 == 1) {
            // n odd: power = (n-1)/2, same as previous even's power
            // p2 stays the same (already 2^{(n-1)/2})
        } else {
            // n even: power = n/2, one more than previous
            p2 = (p2 * 2) % MOD;
        }
        
        int t = (p2 - b[n] + MOD) % MOD;
        
        if (n > 42 && t == 0) {
            ans = n;
            break;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
