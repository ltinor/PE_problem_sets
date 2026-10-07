// PE 330 - Euler's Number (Brute Force)
// Direct computation with double precision for small n verification

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    // Use Python-like approach with fractions
    // Compute A(n), B(n) exactly for small n
    // a(n) = sum_{k=0}^{n-1} a(k)/(n-k)! + (e - sum_{i=0}^n 1/i!)
    // Multiply by n! to get A(n)e + B(n)
    
    if (N > 20) { cout << "0\n"; return 0; }
    
    vector<__int128> A(N+1), B(N+1);
    A[0] = 1; B[0] = -1;
    
    for (int n = 1; n <= N; n++) {
        __int128 sumA = 0, sumB = 0;
        __int128 comb = 1;
        for (int k = 0; k < n; k++) {
            sumA += comb * A[k];
            sumB += comb * B[k];
            comb = comb * (n - k) / (k + 1);
        }
        __int128 fn = 1;
        for (int i = 2; i <= n; i++) fn *= i;
        
        A[n] = sumA + fn;
        
        __int128 term = 0;
        for (int i = 0; i <= n; i++) {
            __int128 t = 1;
            for (int j = i+1; j <= n; j++) t *= j;
            term += t;
        }
        B[n] = sumB - term;
    }
    
    const ll MOD = 77777777;
    ll ans = (ll)((A[N] + B[N]) % MOD);
    if (ans < 0) ans += MOD;
    cout << ans << "\n";
    
    return 0;
}
