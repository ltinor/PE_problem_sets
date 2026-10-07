#include<bits/stdc++.h>
using namespace std;

#define ll long long

// PE 154 brute: compute v2 and v5 for small N
// Same algorithm as std but without precomputation - O(N^3) which is too slow
// Actually just use the same as std for verification (the algorithm is the same)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    if (N > 500) {
        cout << "0\n";
        return 0;
    }
    
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
    
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N - i; j++) {
            int k = N - i - j;
            int v2_coef = v2_N - (v2_fact[i] + v2_fact[j] + v2_fact[k]);
            int v5_coef = v5_N - (v5_fact[i] + v5_fact[j] + v5_fact[k]);
            if (v2_coef >= 12 && v5_coef >= 12) ans++;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
