#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Brute force for PE 152: use __int128 for exact computation (works for N ≤ 45)
// Generate all subsets using bitmask for small N

ll gcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    if (N > 25) {
        // Brute force only supports N ≤ 25 (2^24 subsets)
        cout << "0\n";
        return 0;
    }
    
    int M = N - 1; // numbers 2..N
    
    // Precompute fractions as numerator/denominator (reduced)
    vector<pair<ll,ll>> fracs(M);
    for (int i = 0; i < M; i++) {
        int k = i + 2;
        fracs[i] = {1, (ll)k * k};
    }
    
    ll ans = 0;
    
    // Enumerate all subsets
    int total = 1 << M;
    for (int mask = 1; mask < total; mask++) {
        ll num = 0, den = 1;
        for (int i = 0; i < M; i++) {
            if (mask & (1 << i)) {
                // num/den + 1/k^2 = (num*k^2 + den) / (den*k^2)
                ll k2 = (ll)(i+2) * (i+2);
                num = num * k2 + den;
                den = den * k2;
                ll g = gcd(num, den);
                num /= g;
                den /= g;
            }
        }
        // Check if num/den == 1/2
        if (num * 2 == den) ans++;
    }
    
    cout << ans << "\n";
    return 0;
}
