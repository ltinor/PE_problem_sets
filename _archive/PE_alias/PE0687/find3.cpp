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
    int64_t target = 621073558;
    
    // Try minimum of in-shuffle and out-shuffle orders
    int64_t total = 0;
    for (int64_t n = 2; n <= 200000; n += 2) {
        int64_t o_in = ord(n + 1);
        int64_t o_out = ord(n - 1);
        total += (o_in < o_out) ? o_in : o_out;
        if (total >= target) {
            cout << "Min S(" << n << ") = " << total << " diff=" << (total-target) << endl;
            break;
        }
    }
    
    // Try sum of ord_2(p) for primes p?
    total = 0;
    for (int64_t p = 3; p <= 500000; p += 2) {
        // Simple primality check
        bool is_prime = true;
        for (int64_t d = 3; d * d <= p; d += 2) {
            if (p % d == 0) { is_prime = false; break; }
        }
        if (is_prime) {
            total += ord(p);
        }
    }
    cout << "Sum ord_2 over primes <= 200000: " << total << endl;
    
    return 0;
}
