#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Verify theory: for n ≡ 1 mod 4, triplets are exactly {k odd : k ⊆ n (bitwise)}
// For n ≡ 3 mod 4, no triplets

int main() {
    ll limit = 2000;
    
    for (ll n = 1; n <= limit; n += 2) {
        ll O = (n + 1) / 2;
        ll E = n / 2;
        
        // Count triplets using brute Lucas check
        ll brute_cnt = 0;
        for (ll k = 1; k <= n; k += 2) {
            bool f_odd = false;
            for (ll o = 1; o <= O && o <= k; o += 2) {
                ll e = k - o;
                if (e > E) continue;
                if ((o & ~O) == 0 && (e & ~E) == 0) {
                    f_odd = !f_odd;
                }
            }
            if (f_odd) brute_cnt++;
        }
        
        // Count using theory: if n≡1 mod 4, count = 2^{popcount(n)-1}; else 0
        ll theory_cnt = 0;
        if (n % 4 == 1) {
            theory_cnt = (1LL << (__builtin_popcountll(n) - 1));
        }
        
        if (brute_cnt != theory_cnt) {
            cout << "MISMATCH n=" << n << " brute=" << brute_cnt << " theory=" << theory_cnt << "\n";
        }
    }
    
    cout << "Verification done for n up to " << limit << "\n";
    return 0;
}
