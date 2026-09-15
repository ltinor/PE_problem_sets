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

int64_t ipow(int64_t a, int64_t b) {
    int64_t r = 1;
    while (b) { if (b&1) r *= a; a *= a; b >>= 1; }
    return r;
}

int main() {
    int64_t target = 621073558;
    
    // Sum over powers of 2
    cout << "Powers of 2:" << endl;
    int64_t total = 0;
    for (int k = 1; k <= 30; k++) {
        int64_t n = ipow(2, k);
        if (n - 1 > 0) {
            total += ord(n - 1);
            cout << "k=" << k << " n=" << n << " ord=" << ord(n-1) << " sum=" << total << endl;
        }
    }
    
    // Sum over deck sizes where n-1 is prime
    cout << "\nDeck sizes where n-1 is prime (n even, n-1 prime, n<=2000):" << endl;
    total = 0;
    for (int64_t n = 4; n <= 200000; n += 2) {
        int64_t m = n - 1;
        bool is_prime = true;
        for (int64_t d = 3; d * d <= m; d += 2) {
            if (m % d == 0) { is_prime = false; break; }
        }
        if (is_prime && m >= 3) {
            total += ord(m);
            if (total >= target - 1000000 && total <= target + 1000000) {
                cout << "n=" << n << " total=" << total << endl;
            }
        }
    }
    
    return 0;
}
