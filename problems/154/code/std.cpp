#include<bits/stdc++.h>
using namespace std;

#define ll long long

// PE 154: Pascal's Pyramid
// Count coefficients of (x+y+z)^N divisible by 10^12 = 2^12 * 5^12
// Trinomial coefficient = N!/(i!j!k!) where i+j+k=N
// Need v2 ≥ 12 and v5 ≥ 12
// Legendre: v_p(n!) = Σ floor(n/p^e)

// Precompute v2[n] and v5[n] for n up to N
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    // Precompute digit sums in base p for each n (Kummer's theorem)
    // v_p(n!) = (n - s_p(n)) / (p-1) where s_p is sum of digits in base p
    // But easier: just precompute v2[n!] and v5[n!] for n=0..N
    
    vector<int> v2_fact(N+1, 0), v5_fact(N+1, 0);
    for (int i = 1; i <= N; i++) {
        v2_fact[i] = v2_fact[i-1];
        int x = i;
        while (x % 2 == 0) { v2_fact[i]++; x /= 2; }
        
        v5_fact[i] = v5_fact[i-1];
        x = i;
        while (x % 5 == 0) { v5_fact[i]++; x /= 5; }
    }
    
    int v2_N = v2_fact[N];
    int v5_N = v5_fact[N];
    
    ll ans = 0;
    
    // Enumerate i, j such that i+j ≤ N, k = N-i-j
    for (int i = 0; i <= N; i++) {
        int v2_i = v2_fact[i];
        int v5_i = v5_fact[i];
        
        for (int j = 0; j <= N - i; j++) {
            int k = N - i - j;
            
            int v2_denom = v2_i + v2_fact[j] + v2_fact[k];
            int v5_denom = v5_i + v5_fact[j] + v5_fact[k];
            
            int v2_coef = v2_N - v2_denom;
            int v5_coef = v5_N - v5_denom;
            
            if (v2_coef >= 12 && v5_coef >= 12) {
                ans++;
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}
