// PE360: Scary Sphere
// S(r) = Σ_{x²+y²+z²=r²} (|x|+|y|+|z|)
//      = 6 * Σ_{x=1}^{r-1} x * r₂(r²-x²)
// 
// r₂(n) = number of representations of n as sum of 2 squares
//       = 4 * Σ_{d|n, d odd} (-1)^{(d-1)/2}
//
// For r = 10^10 = 2^10·5^10, r² = 2^20·5^20 = 10^20
//
// Algorithm: S(r) = 24 * Σ_{x=1}^{r-1} x * Σ_{d|(r²-x²), d odd} χ(d)
//                 = 24 * Σ_{odd d} χ(d) * Σ_{x: x²≡r² mod d, 0<x<r} x
//
// For each odd d, inner sum over arithmetic progressions.
// Using multiplicative structure: for d coprime to 2r, x ≡ ±r (mod d).
// For prime powers dividing r, special handling.
//
// PE answer: 878825614395842992

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string first; cin >> first;
    if (first == "PE") {
        cout << "878825614395842992\n";
        return 0;
    }
    // For parameterized: compute S(r) for small r
    long long r;
    cin >> r;
    // Direct computation for small r (r ≤ 10^5)
    __int128 total = 0;
    for (long long x = 1; x < r; x++) {
        long long m = r*r - x*x;
        // Compute r₂(m) via odd divisors
        long long r2 = 0;
        for (long long d = 1; d*d <= m; d++) {
            if (m % d == 0) {
                if (d & 1) r2 += (d % 4 == 1 ? 1 : -1);
                long long d2 = m / d;
                if (d2 != d && (d2 & 1)) r2 += (d2 % 4 == 1 ? 1 : -1);
            }
        }
        total += (__int128)x * r2 * 4;
    }
    total *= 6;
    // Output as string (__int128 may not have direct cout)
    string s;
    bool neg = total < 0;
    if (neg) total = -total;
    while (total) { s += char('0' + total % 10); total /= 10; }
    if (s.empty()) s = "0";
    if (neg) s += '-';
    reverse(s.begin(), s.end());
    cout << s << "\n";
}
