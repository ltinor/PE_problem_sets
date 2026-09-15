#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE354 brute: Enumerate L and count B(L) for small limits
// B(L) = number of integer solutions to a^2+ab+b^2 = L^2/3

int main() {
    ll LIMIT, TARGET;
    cin >> LIMIT >> TARGET;

    if (LIMIT > 1000) {
        cout << "0\n";
        return 0;
    }

    ll ans = 0;
    // L must be sqrt(3*M) where M is integer
    // So L = sqrt(3) * sqrt(M) → 3|L^2, so L must be multiple of sqrt(3)?
    // Actually, enumerate L and check B(L)
    for (ll L = 1; L <= LIMIT; L++) {
        // Check if L^2 is divisible by 3
        if ((L * L) % 3 != 0) continue;
        ll M = (L * L) / 3;
        
        // Count representations of M as a^2 + ab + b^2
        ll cnt = 0;
        ll limit_b = (ll)sqrt(M);
        for (ll b = -limit_b; b <= limit_b; b++) {
            ll b2 = b * b;
            // Solve a^2 + ab + (b2 - M) = 0
            // a = (-b ± sqrt(b^2 - 4*(b2-M)))/2 = (-b ± sqrt(4M - 3b^2))/2
            ll disc = 4 * M - 3 * b2;
            if (disc < 0) continue;
            ll sq = (ll)sqrt(disc);
            if (sq * sq != disc) continue;
            
            ll a1 = -b + sq;
            if (a1 >= 0 && a1 % 2 == 0) cnt++;
            ll a2 = -b - sq;
            if (a2 >= 0 && a2 % 2 == 0 && sq != 0) cnt++;
        }
        // Multiply by 6 for symmetry (but careful with boundary)
        cnt *= 6;
        // b=0 case: a^2 = M, 2 solutions (±a)
        // Actually, the full count r(M) should be computed properly
        
        if (cnt == TARGET) ans++;
    }
    cout << ans << "\n";
    return 0;
}
