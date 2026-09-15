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
    int64_t total = 0;
    for (int64_t n = 2; n <= 200000; n += 2) {
        total += ord(n - 1);
        if (total >= target) {
            cout << "S(" << n << ") = " << total << endl;
            cout << "Diff: " << (total - target) << endl;
            break;
        }
    }
    // Also check in-shuffle
    total = 0;
    for (int64_t n = 2; n <= 200000; n += 2) {
        total += ord(n + 1);
        if (total >= target) {
            cout << "S_in(" << n << ") = " << total << endl;
            break;
        }
    }
    return 0;
}
