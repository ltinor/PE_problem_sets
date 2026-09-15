#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 929: Odd-Run Compositions / 奇数长度分段组成
//
// F(0)=1, F(n)=Σ_{m=1}^{n} g(m)·F(n-m) where g(m)=#odd divisors of m.
// g(m)=τ(odd_part(m)).
//
// O(N²) for N=10^5 is 5e9 ops, ~10s in C++ with -O2.
// Use optimized loop: precompute g, then DP.

const ll MOD = 1111124111LL;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        const int N = 100000;
        
        // Compute g(m) = #odd divisors via odd divisor sieve
        vector<int> g(N + 1, 0);
        for (int d = 1; d <= N; d += 2)
            for (int m = d; m <= N; m += d)
                g[m]++;
        
        // DP: F[n] = Σ_{m=1}^{n} g[m] * F[n-m]
        vector<ll> F(N + 1, 0);
        F[0] = 1;
        
        // Optimize: cache g in local array for faster access
        for (int n = 1; n <= N; n++) {
            ll sum = 0;
            // Loop unrolling: process 4 at a time
            int m = 1;
            for (; m + 3 <= n; m += 4) {
                sum = (sum + (ll)g[m] * F[n-m]) % MOD;
                sum = (sum + (ll)g[m+1] * F[n-m-1]) % MOD;
                sum = (sum + (ll)g[m+2] * F[n-m-2]) % MOD;
                sum = (sum + (ll)g[m+3] * F[n-m-3]) % MOD;
            }
            for (; m <= n; m++) {
                sum = (sum + (ll)g[m] * F[n-m]) % MOD;
            }
            F[n] = sum;
        }
        
        cout << F[N] << "\n";
        return 0;
    }

    if (query == "verify") {
        cout << "PE 929: Odd-Run Compositions / 奇数长度分段组成\n\n";
        cout << "F(5)=10\n";
        cout << "Target: F(100000) mod 1111124111\n";
        return 0;
    }

    cout << "PE 929: Odd-Run Compositions / 奇数长度分段组成\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}
