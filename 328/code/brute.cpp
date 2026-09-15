// PE 328 - Lowest-cost Search (Brute Force)
// O(n^3) DP for small n verification
// Checks all possible k for each n, recomputing right subproblem costs

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    if (N <= 0) { cout << "0\n"; return 0; }
    
    vector<ll> C(N + 1, 0);
    vector<int> D(N + 1, 0);
    
    C[0] = 0; D[0] = 0;
    if (N >= 1) { C[1] = 0; D[1] = 0; }
    if (N >= 2) { C[2] = 1; D[2] = 1; }
    
    for (int n = 3; n <= N; n++) {
        ll best = 1LL << 60;
        int best_d = 0;
        
        for (int k = 1; k <= n; k++) {
            ll left = k + (k > 1 ? C[k-1] : 0);
            
            int m = n - k;
            ll right;
            int rd;
            if (m <= 1) {
                right = k;
                rd = (m == 0 ? 0 : 0);  // immediately known
            } else {
                right = (ll)k * (D[m] + 1) + C[m];
                rd = 1 + D[m];
            }
            
            ll worst = max({(ll)k, left, right});
            int wd = 1;
            if (worst == left && k > 1) wd = 1 + D[k-1];
            else if (worst == right && m > 1) wd = rd;
            
            if (worst < best || (worst == best && wd < best_d)) {
                best = worst;
                best_d = wd;
            }
        }
        C[n] = best;
        D[n] = best_d;
    }
    
    ll total = 0;
    for (int n = 1; n <= N; n++) total += C[n];
    cout << total << "\n";
    
    return 0;
}
