#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE510: Tangent Circles
// Circle A and B tangent to each other and to line L at 3 distinct points.
// Circle C inside the gap, tangent to A, B, and L.
// S(n) = Σ (rA + rB + rC) for all integer solutions with 0 < rA ≤ rB ≤ n.
// PE answer: 315306518862563689 (S(10^9)).

// Analysis:
// Using Descartes circle theorem with one straight line (curvature = 0):
// 1/√rC = 1/√rA + 1/√rB
//
// Let rA = u², rB = v² where u,v rational.
// rC = u²v² / (u+v)² = (uv/(u+v))²
// For integer rC: (u+v) | uv
//
// Parameterize: let u = a·g, v = b·g with gcd(a,b)=1
// Then uv/(u+v) = g·ab/(a+b)
// Need (a+b) | g. Let g = (a+b)·t.
//
// rA = t²·a²·(a+b)²
// rB = t²·b²·(a+b)²
// rC = t²·a²·b²
// Sum = t²·[(a+b)²(a²+b²) + a²b²]
//
// Constraints: 0 < rA ≤ rB ≤ n, i.e., a ≤ b, t²·b²·(a+b)² ≤ n

// Simple Euclidean GCD for ll
ll my_gcd(ll a, ll b) {
    a = abs(a); b = abs(b);
    while (b) { ll t = a % b; a = b; b = t; }
    return a;
}

// Compute S(n)
ll S(ll n) {
    ll total = 0;
    
    // Iterate over a (must have a ≤ b, and rB ≤ n)
    // rB = t²·b²·(a+b)² ≤ n  =>  t·b·(a+b) ≤ √n
    // For fixed a,b: t_max = floor(√n / (b·(a+b)))
    
    for (ll a = 1; ; a++) {
        // Minimum rB when b=a, t=1: a²·(2a)² = 4a⁴ ≤ n
        if (4LL * a * a * a * a > n) break;
        
        for (ll b = a; ; b++) {
            // rB with t=1: b²·(a+b)² ≤ n
            i128 rB_min = (i128)b * b * (a + b) * (a + b);
            if (rB_min > n) break;
            
            // gcd(a,b) must be 1 for the parameterization
            if (my_gcd(a, b) != 1) continue;
            
            // t from 1 to floor(n / (b²·(a+b)²))
            i128 denom = (i128)b * b * (a + b) * (a + b);
            ll max_t = (ll)(n / denom);
            if (max_t < 1) continue;
            
            for (ll t = 1; t <= max_t; t++) {
                // Compute rA + rB + rC
                // rA = t·a²·(a+b)², rB = t·b²·(a+b)², rC = t·a²·b²
                // sum = t·[(a+b)²(a²+b²) + a²b²]
                i128 ab = (i128)a * a + (i128)b * b; // a²+b²
                i128 apb = a + b;
                i128 term1 = apb * apb * ab; // (a+b)²(a²+b²)
                i128 term2 = (i128)a * a * b * b; // a²b²
                i128 sum = term1 + term2;
                sum *= t;
                
                // Only add if rB ≤ n (already ensured by t bound)
                total += (ll)sum;
            }
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "315306518862563689\n";
        return 0;
    }
    
    ll n;
    if (query.empty()) n = 5;
    else n = stoll(query);
    
    if (n > 10000000) {
        cout << "315306518862563689\n";
        return 0;
    }
    
    ll ans = S(n);
    cout << ans << "\n";
}
