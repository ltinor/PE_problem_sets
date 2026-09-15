#include <iostream>
#include <cstdint>
using namespace std;

int64_t ord(int64_t m) {
    if (m <= 1) return 0;
    int64_t phi = m, temp = m;
    for (int64_t p = 2; p * p <= temp; p++) {
        if (temp % p == 0) {
            phi = phi / p * (p - 1);
            while (temp % p == 0) temp /= p;
        }
    }
    if (temp > 1) phi = phi / temp * (temp - 1);
    int64_t order = phi;
    for (int64_t p = 2; p * p <= phi; p++) {
        if (phi % p == 0) {
            while (order % p == 0) {
                int64_t c = order / p, r = 1, b = 2 % m, e = c;
                while (e) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; }
                if (r == 1) order = c; else break;
            }
        }
    }
    return order;
}

int main() {
    // Try specific large values
    int64_t vals[] = {100000007, 1000000007, 999999937, 1000000009, 10000000019, 0};
    for (int i = 0; vals[i]; i++) {
        cout << "ord_2(" << vals[i] << ") = " << ord(vals[i]) << endl;
    }
    
    // Is 621073558 itself an order?
    cout << "\nord_2(621073558) would need 621073558 odd" << endl;
    
    // What odd m gives order ~621073558?
    // If ord_2(m) ≈ m/2, then m ≈ 1.2e9
    // Let's check some odd numbers near 1.2e9
    for (int64_t m = 1242147117; m <= 1242147117; m += 2) {
        int64_t o = ord(m);
        cout << "ord_2(" << m << ") = " << o << endl;
    }
    
    // Check small sums
    cout << "\nSum ord_2 for odd m <= 100: ";
    int64_t s = 0;
    for (int64_t m = 1; m <= 100; m += 2) s += ord(m);
    cout << s << endl;
    
    // S(N) = sum ord_2(2k-1) for k=1..N
    // S(109296) = 621084732
    // target = 621073558
    // Diff = 11174
    // Maybe the problem uses n starting from 4 not 2?
    int64_t s2 = 0;
    for (int64_t n = 4; n <= 109296; n += 2) {
        s2 += ord(n - 1);
    }
    cout << "S_start4(" << 109296 << ") = " << s2 << " diff=" << (621073558 - s2) << endl;
    
    // What if we sum for deck sizes that are powers of 2 only for particular N?
    
    return 0;
}
