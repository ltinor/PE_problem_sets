#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 218: Perfect right-angled triangles
// Original answer for C=10^16: 0 (ALL perfect triangles are super-perfect)
// Adapted: parameterized C (≤ 10^16), count perfect triangles with c ≤ C that are NOT super-perfect.
// Since all perfect triangles are super-perfect, answer is always 0.

ll mygcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

// Check if n is a perfect square
bool is_square(ll n) {
    ll r = (ll)sqrt((long double)n);
    while (r * r < n) r++;
    while (r * r > n) r--;
    return r * r == n;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    ll C;
    cin >> C;
    
    // PE 218: mathematically proven that all perfect right triangles are super-perfect.
    // The answer is always 0.
    // But we also enumerate to verify for smaller C.
    
    ll perfect_count = 0;
    ll super_perfect_count = 0;
    
    // Enumerate primitive triples (m, n) with c = m^2+n^2 ≤ sqrt(C)
    // since c = k^2, we have k^2 ≤ C → k ≤ sqrt(C)
    ll max_k = (ll)sqrt((long double)C);
    
    // For c to be a perfect square: c = m^2+n^2 = k^2 for some k
    // So (m, n, k) is a Pythagorean triple
    // Enumerate u>v>0 generating (m,n,k) where m = u^2-v^2, n = 2uv, k = u^2+v^2
    // Then cmax = k^2 = (u^2+v^2)^2 ≤ C → u^2+v^2 ≤ sqrt(C)
    for (ll u = 2; u * u <= max_k; u++) {
        for (ll v = 1; v < u; v++) {
            if ((u - v) % 2 == 0) continue; // need one even, one odd
            if (mygcd(u, v) != 1) continue;
            
            ll m1 = u * u - v * v;
            ll n1 = 2 * u * v;
            ll k = u * u + v * v;
            
            if (k > max_k) continue;
            
            ll c = k * k;
            if (c > C) continue;
            
            // Option 1: m = m1, n = n1
            {
                ll a = m1 * m1 - n1 * n1;
                if (a > 0) {
                    ll b = 2 * m1 * n1;
                    perfect_count++;
                    __int128 area = (__int128)a * b / 2;
                    if (area % 84 == 0) {
                        super_perfect_count++;
                    }
                }
            }
            
            // Option 2: m = n1, n = m1
            {
                ll a2 = n1 * n1 - m1 * m1;
                if (a2 > 0) {
                    ll b2 = 2 * n1 * m1;
                    perfect_count++;
                    __int128 area = (__int128)a2 * b2 / 2;
                    if (area % 84 == 0) {
                        super_perfect_count++;
                    }
                }
            }
        }
    }
    
    ll not_super = perfect_count - super_perfect_count;
    cout << not_super << "\n";
}
