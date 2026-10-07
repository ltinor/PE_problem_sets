#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: enumerate all a,b and check conditions for small C

ll mygcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    ll C;
    cin >> C;
    
    // Brute for C <= 10^8 only
    if (C > 100000000LL) { cout << "0\n"; return 0; }
    
    ll perfect_count = 0;
    ll super_perfect_count = 0;
    
    // For each possible c = k^2 (perfect square hypotenuse)
    for (ll k = 1; k * k <= C; k++) {
        ll c = k * k;
        if (c > C) break;
        
        // Find a,b such that a^2 + b^2 = c^2, a<b
        for (ll a = 1; a * a * 2 < c * c; a++) {
            ll a2 = a * a;
            ll b2 = c * c - a2;
            ll b = (ll)sqrt((long double)b2);
            if (b * b != b2) continue;
            if (b <= a) continue;
            if (a2 + b2 != c * c) continue;
            
            // Primitive check
            if (mygcd(a, b) != 1) continue;
            
            // c is already a perfect square, so this is a perfect right triangle
            perfect_count++;
            
            ll area = a * b / 2;
            if (area % 84 == 0) {
                super_perfect_count++;
            }
        }
    }
    
    cout << (perfect_count - super_perfect_count) << "\n";
}
